#ifndef HEADER_H
#define HEADER_H
#endif // HEADER_H

#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>
using namespace std;

// Запросить данные у пользователя
void requestInputData(QString *inputFilePath, QString *outputFilePath, int argc, char *argv[]);
