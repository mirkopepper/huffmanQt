#ifndef FILEDECOMPRESSOR_H
#define FILEDECOMPRESSOR_H


#include <QString>
#include <QVector>
#include <QDebug>
#include <QImage>
#include <QFile>
#include <QFileDialog>
#include <QMap>
#include "symbol.h"
#include <iostream>
#include <fstream>
using namespace std;


class FileDecompressor
{
public:
    FileDecompressor();
    ~FileDecompressor();
    void decompress();
private:
    void decodificate(std::string);
    void headerInterpreter();
    void generateFile();
    int height;
    int width;
    QString imagedata;
    QStringList header;
    QMap<QString, QString> codes;
};

#endif // FILEDECOMPRESSOR_H
