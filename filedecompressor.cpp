#include "filedecompressor.h"
#include <QMap>
#include <QBuffer>

FileDecompressor::FileDecompressor()
{

}

FileDecompressor::~FileDecompressor()
{

}

void FileDecompressor::decompress()
{
    //Opens HZIP file
    qDebug() << endl << endl;
    QString filePath;
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("HuffmanZip (*.hzip)");
    int result = dialog.exec();
    if (result)
        filePath = dialog.selectedFiles().first();
    else
        filePath = "";
    //Now we need to separate HEADER from DATA

    /*QFile inputFile(filePath);
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

    /* Check it opened OK */
    /*if(!inputFile.isOpen()){
        qDebug() << "- Error, unable to open" << filePath << "for input";
    }

    /* Point a QTextStream object at the file */
    /*QTextStream inStream(&inputFile);

    /* Write the line to the file */
    /*qDebug() << "????????????????????????????????";
    QString text = inStream.readAll();

    /* Close the file */
    /*inputFile.close();*/

    std::ifstream inputFile;
    inputFile.open(filePath.toStdString());

    std::string width;
    getline(inputFile, width);
    std::string height;
    getline(inputFile, height);
    std::string huffmancodes;
    getline(inputFile, huffmancodes);
    std::string data;
    getline(inputFile, data);
    inputFile.close();

    this->width = atoi(width.c_str());
    this->height = atoi(height.c_str());
    qDebug() << this->width << this->height << endl;
    QString mixedcodes = QString::fromUtf8( huffmancodes.data(), huffmancodes.size() );

    QStringList newHeader = mixedcodes.split("#");

    this->header = newHeader;
    this->imagedata = data;
    QString asd = decodificate();
    //this->headerInterpreter();
    //Tendria que quedar asi los bits que me da decodificar
    //QString bits = decodificate();
    //QString bits = "1010111000010110101101011101010010101010010011110";
    //this->generateFile(bits);*/
}

QString FileDecompressor::decodificate()
{
    QString image;

    /*for (int i = 0; i < this->imagedata.size(); i++) {
        char mander = this->imagedata.at(i);
        for (int e = 0; e < 8; e++) {
            bool value = ((mander >> e) & 1);
            if (value)
                image.append("1");
            else image.append("0");
        }
    }*/


    qDebug() << this->imagedata.at(0) << this->imagedata.at(1);
    for (int i = 0; i < this->imagedata.size(); i++) {
        char mander = this->imagedata.at(i);
        char mask = 1 << 7;//desplaza el 1, 7 lugares a la izq (32768)
        for(int e = 0; e<8; e++){
            qDebug() << (mander & mask);
            if((mander & mask)==mask) //si el 1º bit de num es 1
                image.append("1");
            else
                image.append("0");
            mander = (char) (mander << 1);
        }
    }

    qDebug() << image.left(32);



    /*QString file = this->imagedata.toUtf8();
    qDebug() << "EL FILE TIENE LOS CARACTERES " << file.left(4);
    std::string filestring = file.toStdString();
    qDebug() << "EL FILE TIENE LOS CARACTERES " << filestring.at(0) << filestring.at(1) << filestring.at(2);
    char temp = filestring.at(0);
    qDebug() << "EL PRIMER CHAR SIN DECODIFICAR ES" <<temp;
    QChar temp2 = file.at(0);
    qDebug() << "EL PRIMER QCHAR SIN CODIFICAR ES" <<temp2;
    qDebug() << "EL UNICODE: " << temp2.unicode();
    QChar temp3 = file.at(1);
    qDebug() << "EL PRIMER QCHAR SIN CODIFICAR ES" <<temp3;
    qDebug() << "EL UNICODE: " << temp3.unicode();


    QString image;

    for (int i = 0; i < file.size(); i++) {

        char mander = (char)filestring.at(i);
        for (int e = 0; e < 8; e++) {
            bool value = ((mander >> e) & 1);
            if (value)
                image.append("1");
            else image.append("0");
        }
    }
    qDebug() << image.left(32);*/
    //QString image;
    return image;
}

void FileDecompressor::headerInterpreter()
{
    QStringList::iterator it;
    for(it=this->header.begin(); it!=this->header.end(); it++)
    {
        this->codes.insert(it->mid(6), it->mid(0,6).prepend("#"));
    }
}

void FileDecompressor::generateFile(QString bits)
{
    QString aux;
    QVector<QColor> colors;
    QString::iterator it;
    for(it=bits.begin(); it!=bits.end(); it++)
    {
        aux += *it;
        if(this->codes.contains(aux))
        {
            colors.push_back(QColor(this->codes.find(aux).value()));
            aux.clear();
        }
    }
    qDebug() << colors;
    QImage img;
    QByteArray ba;
    QBuffer buffer(&ba);
    //Esto va a tardar por la resolucion de la imagen, no es que se colgo el programa
    int k = 0;
    for(int i=0; i<this->height; i++)
    {
        for(int j=0; j<this->width; j++)
        {
            //Por cada pixel asigno un valor del Map. Deberia haber la misma cantidad de pixeles que tamaño del map.
            img.setPixel(i,j,colors.at(k).rgb());
            k++;
        }

    }
    //Tengo que ver como guardar la imagen
    img.save(&buffer, "PNG");
}

