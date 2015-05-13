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
    void calculateHeader();
    void generateFile();
};

#endif // FILEDECOMPRESSOR_H
