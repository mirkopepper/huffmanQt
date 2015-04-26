#include "huffmanalgorithm.h"
#include <QVector>
#include <QDebug>
#include <QtMath>

HuffmanAlgorithm::HuffmanAlgorithm()
{

}

void HuffmanAlgorithm::setData(QVector< QPair<QString, double> > p)
{
    this->probabilities = p;
}

void HuffmanAlgorithm::run()
{
    this->sortProbabilities();
}

void HuffmanAlgorithm::sortProbabilities()
{
    qSort(probabilities.begin(), probabilities.end(), Comparator());
}

double HuffmanAlgorithm::getAverageLength()
{
    double sum = 0;
    QVector< QPair<double, QString> >::iterator it;
    for(it=this->codes.begin(); it!=this->codes.end(); it++)
    {
        QString code = it->second;
        sum+= it->first * qLn(1/ code.length()) /qLn(2);
    }
    return sum;
}

double HuffmanAlgorithm::getEntropy()
{
    double sum = 0;
    QVector< QPair<QString, double> >::iterator it;
    for(it=this->probabilities.begin(); it!=this->probabilities.end(); it++)
    {
        sum+= it->second * qLn(1/ it->second)/qLn(2);
    }

    return sum;
}

double HuffmanAlgorithm::getPerformance()
{
    return this->getEntropy()/this->getAverageLength();
}

QVector< QPair<double, QString> > HuffmanAlgorithm::getCodes()
{
    return this->codes;
}
