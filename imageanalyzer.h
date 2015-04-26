#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QString>
#include <QImage>

class ImageAnalyzer
{
public:
    ImageAnalyzer();
    void start(QString filePath);
private:
    QImage image;
};

#endif // IMAGEANALYZER_H
