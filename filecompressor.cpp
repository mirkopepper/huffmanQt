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
    std::string newFile;
    QVector<QString> cacacaca;
    char16_t buffer = 0;
    int digits = 0;
    for (int i = 0; i < image.size(); i++) {
        QString color = image.at(i);
        QString huffcode = codes.at(searchColor(codes, color)).getHuffmanCode();
        cacacaca.append(huffcode);
        int n = huffcode.size();
        for (int i = 0; i < n; i++) {
            buffer=buffer<<1;
            if (huffcode.at(i) == '1') {
                buffer = buffer | 1;
            }
            else
                digits++;
            if (digits == 16) {
                newFile.push_back(buffer);
                buffer = 0;
                digits = 0;
            }
        }
    }
    char temp = newFile.at(0);
    qDebug() << "EL PRIMER CHAR SIN CODIFICAR ES" <<temp;

    QString asd = QString::fromUtf8( newFile.data(), newFile.size() );
    QChar temp2 = asd.at(0);
    qDebug() << "EL PRIMER QCHAR SIN CODIFICAR ES" <<temp2;
    qDebug() << "EL UNICODE: " << temp2.unicode();
    QChar temp3 = asd.at(1);
    qDebug() << "EL PRIMER QCHAR SIN CODIFICAR ES" <<temp3;
    qDebug() << "EL UNICODE: " << temp3.unicode();
    return asd;

}

QString FileCompressor::calculateHeader(QVector<Symbol> codes, int height, int width)
{
    QString tempString;
    tempString.append(QString::number(width));
    tempString.append(" ");
    tempString.append(QString::number(height));
    tempString.append(" ");
    for (int i = 0; i < codes.size(); i++) {
        tempString.append(codes.at(i).getColors().at(0));
        tempString.append(codes.at(i).getHuffmanCode());


    }
    return tempString;
}



void FileCompressor::generateFile(QString header, QString data)
{
    QFileDialog dialog;
    QString filePath;
    //dialog.getSaveFileName()
    //dialog.getSaveFileName("","Save file", "", ".hzip");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("HuffmanZip (*.hzip)");
    int result = dialog.exec();
    if (result)
        filePath = dialog.selectedFiles().first();
    else
        filePath = "";


    QFile outputFile(filePath);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);

    /* Point a QTextStream object at the file */
    QTextStream outStream(&outputFile);

    /* Write the line to the file */
    outStream << header << " " << data;

    /* Close the file */
    outputFile.close();
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
    generateFile(header, compressed);
}
