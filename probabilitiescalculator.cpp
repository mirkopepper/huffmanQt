#include "probabilitiescalculator.h"

ProbabilitiesCalculator::ProbabilitiesCalculator()
{
}

void ProbabilitiesCalculator::calculate(const QVector< QPair<QString, int> > &data, int total)
{
    for (int e = 0; e < data.size(); e++) {
        QString first = data.at(e).first;
        double second = (double)(data.at(e).second)/total;
        probs.push_back(qMakePair(first, second));
    }
}

QVector< QPair<QString, double> > ProbabilitiesCalculator::getProbabilities()
{
    return probs;
}
