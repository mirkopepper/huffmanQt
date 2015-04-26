#include "probabilitiescalculator.h"

ProbabilitiesCalculator::ProbabilitiesCalculator()
{
}

void ProbabilitiesCalculator::calculate(const QVector<int> &data)
{
    double total = 0;
    for (int i = 0; i < data.size(); i++) {
        total += data.at(i);
    }
    for (int e = 0; e < data.size(); e++) {
        probs.push_back((double)(data.at(e))/total);
    }
    qDebug() << probs;
}
