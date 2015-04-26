#include "imageanalyzer.h"

ImageAnalyzer::ImageAnalyzer()
{
}

void ImageAnalyzer::start(QString filePath)
{

    if (image.load(filePath)) {
        QVector< QPair<QString, int> > colorCount;
        for (int x=0; x < image.width(); x++) {
            for (int y=0; y < image.height(); y++) {
                QString value = ((QColor)image.pixel(x, y)).name();
                int i = 0;
                bool listo = false;

                while (i < colorCount.size() && !listo){
                    if (colorCount.at(i).first == value) {
                        QPair<QString, int> temp;
                        temp.first = value;
                        temp.second = colorCount.at(i).second+1;
                        colorCount.removeAt(i);
                        colorCount.push_back(temp);
                        listo = true;
                    }
                    else i++;
                }
                if (!listo) {
                    QPair<QString, int> temporal;
                    temporal.first = value;
                    temporal.second = 1;
                    colorCount.push_back(temporal);
                }
            }
        }
        data = colorCount;
        qDebug() << data;
    }
}

 QVector< QPair<QString, int> > ImageAnalyzer::getData()
{
    return data;
}
