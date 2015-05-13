#ifndef FILEDECOMPRESSOR_H
#define FILEDECOMPRESSOR_H


#include <QString>
#include <QVector>
#include <QDebug>
#include <QImage>
#include <QFile>
#include <QFileDialog>
#include "symbol.h"

class FileDecompressor
{
public:
    FileDecompressor();
    ~FileDecompressor();
    void decompress();
private:
    void decodificate();
    void headerInterpreter();
    void generateFile();

    int height;
    int width;
    QString imagedata;
    QStringList header;
};

#endif // FILEDECOMPRESSOR_H
