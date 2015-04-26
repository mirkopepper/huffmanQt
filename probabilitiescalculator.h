#ifndef PROBABILITIESCALCULATOR_H
#define PROBABILITIESCALCULATOR_H

#include <QVector>
#include <QPair>
#include <QDebug>

class ProbabilitiesCalculator
{
public:
    ProbabilitiesCalculator();
    void calculate(const QVector< QPair<QString, int> > &data);
private:
     QVector< QPair<QString, double> > probs;

};

#endif // PROBABILITIESCALCULATOR_H
