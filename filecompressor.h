#ifndef FILECOMPRESSOR_H
#define FILECOMPRESSOR_H

#include <QString>
#include <QVector>
#include <QDebug>
#include <QImage>
#include "symbol.h"

class FileCompressor
{
public:
    FileCompressor();
    void compress(QVector<Symbol> codes, QVector<QString> image, int height, int width);
    ~FileCompressor();
private:
    void codificate();
    QString calculateHeader(QVector<Symbol> codes, int height, int width);
};

#endif // FILECOMPRESSOR_H
