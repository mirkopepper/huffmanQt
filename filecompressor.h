#ifndef FILECOMPRESSOR_H
#define FILECOMPRESSOR_H

#include <QString>
#include <QVector>
#include <QDebug>
#include <QImage>
#include <QFile>
#include <QFileDialog>
#include "symbol.h"
#include <iostream>
#include <fstream>
using namespace std;

class FileCompressor
{
public:
    FileCompressor();
    void compress(QVector<Symbol> codes, QVector<QString> image, int height, int width);
    ~FileCompressor();
private:
    QString calculateHeader(QVector<Symbol> codes, int height, int width);
    void generateFile(QString header, QVector<Symbol> codes, QVector<QString> image);
};

#endif // FILECOMPRESSOR_H
