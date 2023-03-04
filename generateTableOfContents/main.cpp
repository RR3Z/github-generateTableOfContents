#include "header.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    string inputData;
    string outputFilePath = "./Result/result.html";
    QByteArray urlData;
    QStringList fileContent;
    QFile file(outputFilePath.data());
    QFileInfo fileInfo(outputFilePath.data());
    QDir dir = fileInfo.absoluteDir();

    // Запросить входные данные у пользователя...
    int argType = requestInputData(&inputData, argc, argv);

    // В зависимости от того, чем является переданный аргумент...
    switch (argType){
    // Если в качестве аргумента был передан URL-адрес...
    case 1:
        // Спарсить HTML-страницу по URL-адресу...
        parseByUrl(inputData, &urlData);

        // Сгенерировать заголовки HTML-страницы с учетом отступов...

        // Сохранить результат работы программы в файл...

        // Create the folder if it doesn't exist
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        // Create the file
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            file.write(urlData);
            file.close();
        }

        break;
    // Если в качестве аргумента был передан абсолютный путь...
    case 0:
        // Считать содержимое входного файла...
        readInputDataFromFile(inputData, &fileContent);

        // Сгенерировать заголовки HTML-страницы с учетом отступов...

        // Сохранить результат работы программы в файл...

        break;
    default:
        break;
    }

// Не забыть вернуть!!!!!!!!!!
//return app.exec();
}

int requestInputData(string *inputData, int argc, char *argv[])
{
    // Если с запуском программы был передан аргумент...
    if(argc >= 2){
        *inputData = argv[2];
    }
    // Иначе запросить входные данные...
    else{
        cout << "\nInput data: ";
        cin >> *inputData;
        cout << "\n";
    }

    // Если переданный аргумент является ссылкой...
    if(inputData->find("http://") != -1 || inputData->find("https://") != -1){
        // В качестве результата выполнении функции вернуть значение, означающее, что переданный аргумент является ссылкой
        return 1;
    }
    // Иначе проверить является ли аргумент абсолютным путем для входного файла...
    else{
        // Если форматом входного файла является "html"...
        if(inputData->find(".html", inputData->find_last_of('.') - 1) != -1){
            // Если существует входной файл с заданным именем по заданному пути...
            if(QFile::exists(inputData->data())){
                // В качестве результата выполнении функции вернуть значение, означающее, что переданный аргумент является абсолютным путем
                return 0;
            }
            // Иначе вывести соответствующую ошибку
            else{
                cout << "The input data file is specified incorrectly. The file may not exist.\n";
            }
        }
        // Иначе вывести соответствующую ошибку
        else{
            cout << "The format of the input file does not meet the requirements of the software.\n";
        }
    }
    // В качестве результата выполнении функции вернуть значение, означающее, что переданный аргумент некорректен
    return -1;
}

void readInputDataFromFile(string inputFilePath, QStringList *fileContent)
{
    QFile file(inputFilePath.data());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString content = in.readAll();
        *fileContent = content.split("\n");
        file.close();
    }
}

void parseByUrl(string inputUrl, QByteArray *urlData)
{
    QNetworkAccessManager manager;
    QUrl url(inputUrl.data());
    QNetworkReply *reply = manager.get(QNetworkRequest(url));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, [&]() {
        *urlData = reply->readAll();
        QCoreApplication::quit();
        loop.quit();
    });
    loop.exec();

}
