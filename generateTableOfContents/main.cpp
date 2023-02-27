#include "header.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Объявить переменную, где хранится полный путь на входной файл
    string inputFilePath;

    // Запросить входные данные у пользователя...
    requestInputData(&inputFilePath, argc, argv);

    // Создать объект для входного файла
    QFile inputFile(inputFilePath.data());

    // Прочитать содержимое входного файла...


    // Сгенерировать заголовки HTML-страницы с учетом отступов...


    // Не забыть вернуть!!!!!!!!!!
    //return a.exec();
}

// Запросить входнные данные у пользователя
void requestInputData(string *inputFilePath, int argc, char *argv[])
{
    // Если был передан полный путь для входного файла...
    if(argc == 2){
        *inputFilePath = argv[2];
    }
    // Иначе запросить полный путь для входного файла...
    else{
        cout << "\nPath for input file: ";
        cin >> *inputFilePath;
        cout << "\n";
    }

    // Проверить формат входного файла...
    int dot = inputFilePath->find_last_of('.');
    while((inputFilePath->find(".html", dot - 1) == -1) || (inputFilePath->find(".txt", dot - 1) == -1) ){
        // Вывести сообщение об ошибке
        cout << "The format of the input file does not meet the requirements of the software.\n";

        // Вывести пользователю сообщение с просьбой ввести полный путь для входного файла
        cout << "\nPath for input file: ";
        cin >> *inputFilePath;
        cout << "\n";

        // Обновить позицию последней точки в строке
        dot = inputFilePath->find_last_of('.');
    }

    // Определить, существует ли входной файл с заданным именем по заданному пути...
    bool isInputFileExists = QFile::exists(inputFilePath->data());
    while(!isInputFileExists){
        // Вывести сообщение об ошибке
        cout << "The input data file is specified incorrectly. The file may not exist.";

        // Вывести пользователю сообщение с просьбой ввести полный путь для входного файла
        cout << "\nPath for input file: ";
        cin >> *inputFilePath;
        cout << "\n";

        // Обновить флаг
        isInputFileExists = QFile::exists(inputFilePath->data());
    }
}
