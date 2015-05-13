#include "filecompressor.h"

FileCompressor::FileCompressor()
{

}

FileCompressor::~FileCompressor()
{

}

int searchColor(QVector<Symbol> codes, QString color)
{
    int i = 0;
    int sol;
    bool found = false;
    while (i < codes.size() && !found) {
        if (codes.at(i).getColors().at(0) == color) {
            sol = i;
            found = true;
        }
        i++;
    }
    return sol;
}

QString FileCompressor::codificate(QVector<Symbol> codes, QVector<QString> image)
{
    QString newFile;
    char buffer = 0;
    int digits = 0;
    for (int i = 0; i < image.size(); i++) {
        QString color = image.at(i);
        QString huffcode = codes.at(searchColor(codes, color)).getHuffmanCode();
        int n = huffcode.size();
        for (int i = 0; i < n; i++) {
            buffer=buffer<<1;
            if (huffcode.at(i) == '1') {
                buffer = buffer | 1;
            }
            else
                digits++;
            if (digits == 8) {
                newFile.push_back(buffer);
                buffer = 0;
                digits = 0;
            }
        }
    }
    return newFile;

}

QString FileCompressor::calculateHeader(QVector<Symbol> codes, int height, int width)
{
    QString tempString;
    tempString.append(QString::number(width));
    tempString.append(" ");
    tempString.append(QString::number(height));
    tempString.append(" ");
    for (int i = 0; i < codes.size(); i++) {
        tempString.append(codes.at(i).getHuffmanCode());
        tempString.append(codes.at(i).getColors().at(0));

    }
    tempString.append(" ");
    return tempString;
}

void FileCompressor::compress(QVector<Symbol> codes, QVector<QString> image, int height, int width)
{
    //calculo el header en un QString para agregar al archivo de salida
    QString header = calculateHeader(codes, height, width);
    qDebug() << header;
    //codifico segun huffman la imagen en un QString (a nivel bit)
    QString compressed = codificate(codes, image);
    qDebug() << compressed;
    //genero el archivo de texto de salida
}
