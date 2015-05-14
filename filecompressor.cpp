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

string compressmariano(string line){
        string result;
        char buffer = 0;
        int cant_digitos = 0;
        int i = 0;
        while(i<line.size()){

                cant_digitos++;
                char c = line[i];
                buffer = buffer << 1;
                if (c == '1'){
                        buffer = buffer | 1;
                }


                if (cant_digitos == 8){
                        result.push_back(buffer);
                        buffer = 0;
                        cant_digitos = 0;
                }
                i++;
        }
        if ((cant_digitos < 8) && (cant_digitos != 0)){
                buffer = buffer << (8 - cant_digitos);
                result.push_back(buffer);
        }
        return result;
}



void FileCompressor::generateFile(QString header, QVector<Symbol> codes, QVector<QString> image)
{
    QFileDialog dialog;
    QString filePath;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("HuffmanZip (*.hzip)");
    int result = dialog.exec();
    if (result) {
        filePath = dialog.selectedFiles().first();
        filePath.append(".hzip");
    }
    else
        filePath = "";

    header.append(" ");
    QStringList list = header.split(" ",QString::SkipEmptyParts);
    std::string headerstd1 = list.at(0).toStdString();
    std::string headerstd2 = list.at(1).toStdString();
    std::string headerstd3 = list.at(2).toStdString();


    std::ofstream binaryfile;
    binaryfile.open(filePath.toStdString().c_str(), std::ofstream::binary);

    binaryfile << headerstd1 << "\n" << headerstd2 << "\n" << headerstd3 << "\n";


    qDebug() << "IMAGE SIZE" << image.size();

    string bits;

    string solutiontest;

    char buffer = 0;
    int digits = 0;
    qDebug() << "HAY TANTOS CODES" << codes.size();
    for (int i = 0; i < image.size(); i++) {
        QString color = image.at(i);
        QString huffcode = codes.at(searchColor(codes, color)).getHuffmanCode();
        std::string huff = huffcode.toStdString();
        int n = huffcode.size();
        bits+=(huff);
        for (int e = 0; e < n; e++) {
            //bits.push_back(huff.at(e));
            buffer=(buffer<<1);
            if (huff.at(e) == '1') {
                buffer =(buffer | 1);
            }
            digits++;
            if (digits == 8) {
                solutiontest.push_back(buffer);
                binaryfile << buffer;
                buffer = 0;
                digits = 0;
            }
        }
    }
    if ((digits<8)&&(digits!=0)){
        buffer=(char) (buffer<<(8-digits));
        binaryfile << buffer;
        solutiontest.push_back(buffer);
    }
    binaryfile.close();

    qDebug() << "TAMAÑO DEL STRING DE CHARS " << solutiontest.size();
    qDebug() << "CANTIDAD DE BITS" << bits.size();
    string asddsa = compressmariano(bits);
    qDebug() << "TAMAÑO DE MARIANO "<< asddsa.size();
}

void FileCompressor::compress(QVector<Symbol> codes, QVector<QString> image, int height, int width)
{
    //calculo el header en un QString para agregar al archivo de salida
    QString header = calculateHeader(codes, height, width);

    //codifico segun huffman la imagen en un QString (a nivel bit)
    //genero el archivo de texto de salida
    generateFile(header, codes, image);
}
