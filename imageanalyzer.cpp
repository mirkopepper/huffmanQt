#include "imageanalyzer.h"

ImageAnalyzer::ImageAnalyzer()
{
}

void ImageAnalyzer::start(QString filePath)
{
    qDebug() << filePath;
    if (image.load(filePath))
        qDebug() << "la abrio";
    if (image.allGray())
        qDebug() << "es greyscale";
    qDebug() << image.colorCount();
    qDebug() << image.size();
    QVector<QRgb> vector = image.colorTable();
    qDebug() << vector;



    QVector< QPair<unsigned, int> > colorCount;
    /*for (int i=0; i < vector.size(); i++) {
        QPair<int, int> temporal;
        temporal.first = vector.at(i);
        temporal.second = 0;
        colorCount.push_back(temporal);
    }*/


    for (int x=0; x < image.width(); x++) {
        for (int y=0; y < image.height(); y++) {
            unsigned value = image.pixel(x, y);
            int i = 0;
            bool listo = false;

            while (i < colorCount.size() && !listo){
                if (colorCount.at(i).first == value) {
                    QPair<unsigned, int> temp;
                    temp.first = value;
                    temp.second = colorCount.at(i).second+1;
                    colorCount.removeAt(i);
                    colorCount.push_back(temp);
                    listo = true;
                }
                else i++;
            }
            if (!listo) {
                QPair<unsigned, int> temporal;
                temporal.first = value;
                temporal.second = 1;
                colorCount.push_back(temporal);
            }
        }
    }

    qDebug() << colorCount;
}
