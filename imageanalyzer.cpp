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
                        colorCount.replace(i, qMakePair(value, colorCount.at(i).second+1));
                        listo = true;
                    }
                    else i++;
                }
                if (!listo)
                    colorCount.push_back(qMakePair(value, 1));
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
