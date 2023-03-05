#include "header.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    string inputDataPath;
    QString outputFilePath = app.applicationDirPath() + "/Result/result.html";
    QByteArray inputDataByUrl;
    QStringList inputData;

    // Запросить входные данные у пользователя...
    int argType = requestInputData(&inputDataPath, argc, argv);

    // Если в качестве аргумента был передан URL-адрес...
    if(argType == 1){
        // Спарсить HTML-страницу по URL-адресу...
        parseByUrl(inputDataPath, &inputDataByUrl);

        // Конвертация QByteArray в QStringList (для дальнейшей корректной работы программы)
        QString tmpStr = QString::fromUtf8(inputDataByUrl.constData(), inputDataByUrl.length());
        inputData = tmpStr.split('\n', Qt::SkipEmptyParts);
    }
    // Если в качестве аргумента был передан абсолютный путь...
    if(argType == 0){
        // Считать содержимое входного файла...
        if(readInputDataFromFile(inputDataPath, &inputData) == 0){
            return app.exec();
        }
    }

    // Сгенерировать заголовки HTML-страницы с учетом отступов...


    // Сохранить результат работы программы в файл...
    saveToFile(outputFilePath, &inputData);

    return app.exec();
}

int requestInputData(string *inputDataPath, int argc, char *argv[])
{
    // Если с запуском программы был передан аргумент...
    if(argc >= 2){
        *inputDataPath = argv[2];
    }
    // Иначе запросить входные данные...
    else{
        cout << "\nInput data: ";
        cin >> *inputDataPath;
        cout << "\n";
    }

    // Если переданный аргумент является ссылкой...
    if(inputDataPath->find("http://") != -1 || inputDataPath->find("https://") != -1){
        // В качестве результата выполнении функции вернуть значение, означающее, что переданный аргумент является ссылкой
        return 1;
    }
    // Иначе проверить является ли аргумент абсолютным путем для входного файла...
    else{
        // Если форматом входного файла является "html"...
        if(inputDataPath->find(".html", inputDataPath->find_last_of('.') - 1) != -1){
            // Если существует входной файл с заданным именем по заданному пути...
            if(QFile::exists(inputDataPath->data())){
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

int readInputDataFromFile(string inputFilePath, QStringList *inputData)
{
    // Если файл удалось открыть...
    QFile inputFile(inputFilePath.data());
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        // Сохранить все данные из файла в массив...
        QTextStream in(&inputFile);
        QString inputFileData = in.readAll();
        *inputData = inputFileData.split("\n");
        inputFile.close();
        return 1;
    }
    // Иначе вывести соответствующую ошибку
    else{
        cout<<"The file could not be opened at the specified path";
        return 0;
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

void saveToFile(QString outputFilePath, QStringList *outputData)
{
    QFile file(outputFilePath);
    QFileInfo fileInfo(outputFilePath);
    QDir dir = fileInfo.absoluteDir();

    // Создать папку, указанную в абсолютном пути, если таковой не существует
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Cохранить в файл данные
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        foreach(const QString& str, *outputData){
            out << str << "\n";
        }
    }

    file.close();
}
