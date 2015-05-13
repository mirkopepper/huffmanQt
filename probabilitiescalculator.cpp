#include "probabilitiescalculator.h"

ProbabilitiesCalculator::ProbabilitiesCalculator()
{
}

QVector<Symbol> ProbabilitiesCalculator::calculate(const QVector< QPair<QString, int> > &colorCount, int total)
{
    for (int e = 0; e < colorCount.size(); e++) {
        QString first = colorCount.at(e).first;
        double second = (double)(colorCount.at(e).second)/total;
        probs.push_back(qMakePair(first, second));
    }
    this->backtrackNoRecursion(1);
    return this->symbols;
}

QVector< QPair<QString, double> > ProbabilitiesCalculator::getProbabilities()
{
    return probs;
}

void ProbabilitiesCalculator::backtrackNoRecursion(int n)
{
    QVector<Symbol> list;
    for (int j = 0; j < probs.size(); j++) {
        Symbol temporal;
        temporal.addColor(probs.at(j).first);
        temporal.setProbability(probs.at(j).second);
        list.append(temporal);
    }
    for (int i = 0; i < n-1; i++) {
        QVector<Symbol> tempList;
        for (int e = 0; e < list.size(); e++) {
            for (int c = 0; c < probs.size(); c++) {
                Symbol temp;
                temp.setColors(list.at(e).getColors());
                temp.addColor(probs.at(c).first);
                temp.setProbability(list.at(e).getProbability());
                temp.multiplyProbability(probs.at(c).second);
                tempList.append(temp);
            }
        }
        list.clear();
        list = tempList;
        tempList.clear();
    }
    this->symbols=list;
}

void ProbabilitiesCalculator::extend(int n, QVector<Symbol> &symbols)
{
    this->symbols.clear();
    this->backtrackNoRecursion(n);
    symbols = this->symbols;
}
