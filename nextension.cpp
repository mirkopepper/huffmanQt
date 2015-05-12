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
    ui->nTextProbs->clear();
    ui->nTextSymbols->clear();
    ui->nTextSymbols->append("Symbols: ");
    ui->nTextProbs->append("Probabilities: ");
    ui->nTextSymbols->append(QString::number(orderNSymbols.size()));
    ui->nTextProbs->append("");
    for (int j = 0; j < orderNSymbols.size(); j++) {
        QString text;
        text.append("{");
        for (int i = 0; i < orderNSymbols.at(j).getColors().size(); i++) {
            if (i != 0) {
                text.append(", ");
            }
           text.append(orderNSymbols.at(j).getColors().at(i));
        }
        text.append("}");
        ui->nTextSymbols->append(text);
        ui->nTextProbs->append(QString::number(orderNSymbols.at(j).getProbability()));
    }
}
