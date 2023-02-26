#include "header.h"

// Ввод и вывод данных из консоли для QString
QTextStream CIN(stdin, QIODevice::ReadOnly);
QTextStream COUT(stdout, QIODevice::WriteOnly);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Подключить русский язык для корректного вывода русского текста в консоль
    setlocale(LC_ALL, "Russian");

    // Объявить переменные, где хранятся полные пути на входной и выходной файлы
    QString inputFilePath;
    QString outputFilePath;

    // Запросить входные данные у пользователя...
    requestInputData(&inputFilePath, &outputFilePath, argc, argv);

    // Создать объекты для входного и выходного файлов
    QFile inputFile(inputFilePath.toUtf8().data());
    QFile outputFile(outputFilePath.toUtf8().data());

    // Прочитать содержимое входного файла...


    // Сгенерировать заголовки HTML-страницы с учетом отступов...


    // Не забыть вернуть!!!!!!!!!!
    //return a.exec();
}

// Запросить входнные данные у пользователя
void requestInputData(QString *inputFilePath, QString *outputFilePath, int argc, char *argv[])
{
    // В зависимости от кол-ва переданных аргументов...
    switch (argc) {
    // Если полные пути входного и выходного файлов не были передан...
    case 1:
        // Запросить у пользователя полный путь для входного файла
        cout << "Path for input file: ";
        CIN >> *inputFilePath;

        // Запросить у пользователя полный путь для выходного файла
        cout << "Path for output file: ";
        CIN >> *outputFilePath;
        cout << "\n";
        break;

    // Если был передан полный путь только для входного файла...
    case 2:
        *inputFilePath = argv[1];

        // Запросить у пользователя полный путь для выходного файла
        cout << "Path for output file: ";
        CIN >> *outputFilePath;
        cout << "\n";
        break;

    // Если полные пути входного и выходного файлов были переданы...
    case 3:
        *inputFilePath = argv[1];
        *outputFilePath = argv[2];
        break;
    }

    // Определить, существует ли входной файл с заданным именем по заданному пути...
    bool isInputFileExists = QFile::exists(inputFilePath->toUtf8().data());
    while(!isInputFileExists){
        // Вывести сообщение об ошибке
        cout << "The input data file is specified incorrectly. The file may not exist.";

        // Вывести пользователю сообщение с просьбой ввести полный путь для входного файла
        cout << "\nPath for input file: ";
        CIN >> *inputFilePath;
        cout << "\n";

        // Обновить флаг
        isInputFileExists = QFile::exists(inputFilePath->toUtf8().data());
    }
}
