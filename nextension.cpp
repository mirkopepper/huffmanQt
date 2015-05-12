#include "nextension.h"
#include "ui_nextension.h"

NExtension::NExtension(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NExtension)
{
    ui->setupUi(this);
}

NExtension::~NExtension()
{
    delete ui;
}

void NExtension::loadData(QVector<Symbol> orderNSymbols)
{
    ui->nSolutionTable->setColumnCount(0);
    for (int j = 0; j < orderNSymbols.size(); j++) {
        ui->nSolutionTable->insertColumn(j);
        QString orderNSymbolstring;
        orderNSymbolstring.append("{");
        for (int i = 0; i < orderNSymbols.at(j).getColors().size(); i++) {
            if (i != 0) {
                orderNSymbolstring.append(", ");
            }
            orderNSymbolstring.append(orderNSymbols.at(j).getColors().at(i));
        }
        orderNSymbolstring.append("}");

        QTableWidgetItem *item = new QTableWidgetItem(orderNSymbolstring);
        ui->nSolutionTable->setItem(0, j,item);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(orderNSymbols.at(j).getProbability()));
        ui->nSolutionTable->setItem(1, j, item2);
    }
}
