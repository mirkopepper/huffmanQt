#ifndef PROBABILITIESCALCULATOR_H
#define PROBABILITIESCALCULATOR_H

#include <QVector>
#include <QPair>
#include <QDebug>

class ProbabilitiesCalculator
{
public:
    ProbabilitiesCalculator();
    void calculate(const QVector<int> &data);
private:
    QVector<double> probs;

};

#endif // PROBABILITIESCALCULATOR_H
