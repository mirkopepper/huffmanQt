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
    //std::string newFile;
    QString newFile;
    QString bits;
    char buffer = 0;
    //char buffer = 0;
    int digits = 0;
    for (int i = 0; i < image.size(); i++) {
        QString color = image.at(i);
        QString huffcode = codes.at(searchColor(codes, color)).getHuffmanCode();
        int n = huffcode.size();
        for (int e = 0; e < n; e++) {
            bits.append(huffcode.at(e));
            buffer=(char) (buffer<<1);
            if (huffcode.at(e) == '1') {
                buffer = (char) (buffer | 1);
            }
            else
                digits++;
            if (digits == 8) {
                newFile.push_back((char)(buffer));
                buffer = 0;
                digits = 0;
            }
        }
    }
    if ((digits<8)&&(digits!=0)){
        buffer=(char) (buffer<<(8-digits));
    }
    /*char16_t temp1 = newFile.at(0);
    char temp2 = newFile.at(0);
    qDebug() << "LOS ASCII SON";
    qDebug() << temp1 << int(temp1) << temp2 << int(temp2);*/

    //QString asd = QString::fromUtf8( newFile.data(), newFile.size() );
    //QString asd = newFile;
/*
    QChar temp3 = asd.at(0);
    qDebug() << "LOS ASCII SON";
    qDebug() << temp3 << (int)temp3.toLatin1() << endl;*/
    QString left = bits.left(32);
    qDebug() << left;
    //qDebug() << "NEWFILE TIENE LOS CARACTERES" << newFile.at(0) << newFile.at(1) << newFile.at(2);
    //qDebug() << (int)newFile.at(0);
    qDebug() << "NEWFILE TIENE LOS CARACTERES" << newFile.left(4);
    qDebug() << newFile.at(0).unicode() << endl;

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
        tempString.append(codes.at(i).getColors().at(0));
        tempString.append(codes.at(i).getHuffmanCode());


    }
    return tempString;
}



void FileCompressor::generateFile(QString header, QVector<Symbol> codes, QVector<QString> image)
{
    QFileDialog dialog;
    QString filePath;
    //dialog.getSaveFileName("HuffmanZip (*.hzip)")
    //dialog.getSaveFileName("","Save file", "", ".hzip");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("HuffmanZip (*.hzip)");
    int result = dialog.exec();
    if (result) {
        filePath = dialog.selectedFiles().first();
        filePath.append(".hzip");
    }
    else
        filePath = "";


    /*QFile outputFile(filePath);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);

    /* Point a QTextStream object at the file */
    /*QTextStream outStream(&outputFile);

    /* Write the line to the file */
    /*outStream << header << " ";

    /* Close the file */
    /*outputFile.close();*/
    std::string headerstd = header.toStdString();


    std::ofstream binaryfile;
    binaryfile.open(filePath.toStdString());




    binaryfile << headerstd << " ";
    QString bits;
    char buffer = 0;
    int digits = 0;
    for (int i = 0; i < image.size(); i++) {
        QString color = image.at(i);
        QString huffcode = codes.at(searchColor(codes, color)).getHuffmanCode();
        std::string huff = huffcode.toStdString();
        int n = huffcode.size();
        for (int e = 0; e < n; e++) {
            bits.push_back(huff.at(e));
            buffer=(buffer<<1);
            if (huff.at(e) == '1') {
                buffer =(buffer | 1);
            }
            else
                digits++;
            if (digits == 8) {
                binaryfile << buffer;
                buffer = 0;
                digits = 0;
            }
        }
        if ((digits<8)&&(digits!=0)){
            buffer=(char) (buffer<<(8-digits));
        }
    }
    qDebug() << bits.left(32);


    binaryfile.close();





}

void FileCompressor::compress(QVector<Symbol> codes, QVector<QString> image, int height, int width)
{
    //calculo el header en un QString para agregar al archivo de salida
    QString header = calculateHeader(codes, height, width);

    //codifico segun huffman la imagen en un QString (a nivel bit)
    //genero el archivo de texto de salida
    generateFile(header, codes, image);
}
