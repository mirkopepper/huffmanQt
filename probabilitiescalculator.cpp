#include "probabilitiescalculator.h"

ProbabilitiesCalculator::ProbabilitiesCalculator()
{
}

void ProbabilitiesCalculator::calculate(const QVector< QPair<QString, int> > &data)
{
    double total = 0;
    for (int i = 0; i < data.size(); i++) {
        total += data.at(i).second;
    }
    for (int e = 0; e < data.size(); e++) {
        QString first = data.at(e).first;
        double second = (double)(data.at(e).second)/total;
        probs.push_back(qMakePair(first, second));
    }
    qDebug() << probs;
}

QVector< QPair<QString, double> > ProbabilitiesCalculator::getProbabilities()
{
    return probs;
}
