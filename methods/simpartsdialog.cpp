#include "simpartsdialog.h"
#include "ui_simpartsdialog.h"

SimPartsDialog::SimPartsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimPartsDialog)
{
    ui->setupUi(this);
    ui->label->setText("Number of simulated asset paths:");
    ui->lineEdit->setText("10000");
}

SimPartsDialog::~SimPartsDialog()
{
    delete ui;
}

int SimPartsDialog::getvalue()
{
    bool ok;
    int value = ui->lineEdit->text().toInt(&ok);
    if(ok)
    {
        return value;
    }
    else return -1;
}
