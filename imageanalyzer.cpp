#include "imageanalyzer.h"

ImageAnalyzer::ImageAnalyzer()
{
}

void ImageAnalyzer::start(QString filePath)
{

    if (image.load(filePath)) {
        this->height = image.height();
        this->width = image.width();
        QVector< QPair<QString, int> > colorCount;
        for (int x=0; x < this->width; x++) {
            for (int y=0; y < this->height; y++) {
                QString value = ((QColor)image.pixel(x, y)).name();
                int i = 0;
                bool counted = false;

                while (i < colorCount.size() && !counted){
                    if (colorCount.at(i).first == value) {
                        colorCount.replace(i, qMakePair(value, colorCount.at(i).second+1));
                        counted = true;
                    }
                    else i++;
                }
                if (!counted)
                    colorCount.push_back(qMakePair(value, 1));
            }
        }
        this->ColorCount = colorCount;
        this->totalPixels =  image.width()*image.height();
    }
    
}

QVector<QString> ImageAnalyzer::toVector()
{
    QVector<QString> pixels;
    for (int x=0; x < this->width; x++) {
        for (int y=0; y < this->height; y++) {
            QString value = ((QColor)image.pixel(x, y)).name();
            pixels.append(value);
        }
    }
    return pixels;
}

int ImageAnalyzer::getHeight() const
{
    return this->height;
}

int ImageAnalyzer::getWidth() const
{
    return this->width;
}

QVector< QPair<QString, int> > ImageAnalyzer::getColorCount()
{
    return this->ColorCount;
}

int ImageAnalyzer::getTotalPixels()
{
    return totalPixels;
}
