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
    QVector<QString> tempSymbol;
    double tempProb = 1;
    backtrack(1, tempSymbol, tempProb);
    return this->symbols;
}

QVector< QPair<QString, double> > ProbabilitiesCalculator::getProbabilities()
{
    return probs;
}

void ProbabilitiesCalculator::backtrack(int n, QVector<QString> newSymbol, double newProb)
{
    if (n == 1) {
        for (int i=0; i < probs.size(); i++) {
            newSymbol.append(probs.at(i).first);
            newProb = newProb * (probs.at(i).second);

            //creating new Symbol
            Symbol newNode;
            newNode.setColors(newSymbol);
            newNode.setProbability(newProb);
            symbols.append(newNode);

            newSymbol.removeLast();
            newProb = newProb / (probs.at(i).second);
        }
    }
    else {
        for (int i=0; i < probs.size(); i++) {
            newSymbol.append(probs.at(i).first);
            newProb = newProb * (probs.at(i).second);
            backtrack(n-1, newSymbol, newProb);
            newSymbol.removeLast();
            newProb = newProb / (probs.at(i).second);
        }
    }
}


void ProbabilitiesCalculator::backtrackNoRecursion(int n)
{
    QVector<Symbol> list;
    //COPY
    for (int j = 0; j < probs.size(); j++) {
        Symbol temporal;
        temporal.addColor(probs.at(j).first);
        temporal.setProbability(probs.at(j).second);
        list.append(temporal);
    }

    qDebug() << "VA A EMPEZAR --------------------------";
    for (int i = 0; i < list.size(); i++) {
        qDebug() << list.at(i).getColors();
        qDebug() << "PROBABILITY" << list.at(i).getProbability();
    }
    for (int i = 0; i < n-1; i++) { // 2 VECES POR EJEMPLO PARA N=3
        QVector<Symbol> tempList;
        for (int e = 0; e < list.size(); e++) { //PARA CADA ELEMENTO DE LA LISTA (16, 256, etc)
            for (int c = 0; c < probs.size(); c++) { //COMBINAR CON CADA COLOR (16)
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
    this->symbols=list;/*
    for (int j = 0; j < list.size(); j++) {
        Symbol temporal;
        temporal.setColors(list.at(j).getColors());
        temporal.setProbability(list.at(j).getProbability());
        this->symbols.append(temporal);
    }*/



}

void ProbabilitiesCalculator::extend(int n, QVector<Symbol> &symbols)
{
    this->symbols.clear();
    /*QVector<QString> tempSymbol;
    double tempProb = 1;
    backtrack(n, tempSymbol, tempProb);*/
    backtrackNoRecursion(n);
    symbols = this->symbols;
}
