#include "imageanalyzer.h"

ImageAnalyzer::ImageAnalyzer()
{
}

void ImageAnalyzer::start(QString filePath)
{

    if (image.load(filePath)) {
        QVector< QPair<unsigned, int> > colorCount;
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
        for (int i=1; i <= colorCount.size(); i++) {
            QPair<unsigned, int> temp;
            temp.first = i;
            temp.second = colorCount.at(i-1).second;
            data.push_back(temp);
        }
    }
}

QVector< QPair<int, int> > ImageAnalyzer::getData()
{
    return data;
}
