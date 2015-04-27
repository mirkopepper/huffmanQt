#include "huffmanalgorithm.h"
#include <QVector>
#include <QDebug>
#include <QtMath>
#include <algorithm>

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
    QVector<Node> list = convert();
    while (list.size() != 1)
    {
        Node node1 = list.takeLast();
        node1.code = 0;
        Node node2 = list.takeLast();
        node2.code = 1;
        Node newNode;
        newNode.code = NULL;
        newNode.probability = node1.probability + node2.probability;
        *newNode.left = node1;
        *newNode.right = node2;
        insert(list, newNode);
    }
    generateCode(list.takeFirst(), "");

}

void HuffmanAlgorithm::insert(QVector<Node> list, Node n)
{
    bool found = false;
    QVector<Node>::iterator it = list.begin();
    while(it!=list.end() && !found)
    {
        if(it->probability < n.probability )
        {
            list.insert(it,1,n);
            found = true;
        }
        it++;
    }
}

void HuffmanAlgorithm::generateCode(Node n, QString huffcode)
{
    if (n.left != NULL) {
        huffcode.append(n.code);
        generateCode(*n.left, huffcode);
        generateCode(*n.right, huffcode);
    }
    else
        solution.push_back(qMakePair(n.symbol, huffcode));
}

QVector<Node> HuffmanAlgorithm::convert()
{
    QVector<Node> result;
    QVector< QPair<QString, double> >::iterator it;
    for(it=this->probabilities.begin(); it!=this->probabilities.end(); it++)
    {
        Node *aux = new Node;
        aux->symbol = it->first;
        aux->probability = it->second;
        aux->left = NULL;
        aux->right = NULL;
        result.push_back(*aux);
    }
    return result;
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
