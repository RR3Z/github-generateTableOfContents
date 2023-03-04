#ifndef HEADER_H
#define HEADER_H
#endif // HEADER_H

#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFileInfo>
#include <QDir>
using namespace std;

// Запросить данные у пользователя
int requestInputData(string *inputData, int argc, char *argv[]);

// Считать входные данные из файла
void readInputDataFromFile(string inputFilePath, QStringList *fileContent);

// Спарсить HTML-страницу по URL-адресу
void parseByUrl(string inputUrl, QByteArray *urlData);

void saveResultToFile(string outputFilePath);
