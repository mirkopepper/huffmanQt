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
        QPair<QString, double> temporal;
        temporal.first = data.at(e).first;
        temporal.second = (double)(data.at(e).second)/total;
        probs.push_back(temporal);
    }
    qDebug() << probs;
}
