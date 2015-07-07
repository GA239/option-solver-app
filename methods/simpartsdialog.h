#ifndef SIMPARTSDIALOG_H
#define SIMPARTSDIALOG_H

#include <QDialog>

namespace Ui {
class SimPartsDialog;
}

class SimPartsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimPartsDialog(QWidget *parent = 0);
    ~SimPartsDialog();
    int getvalue();

private:
    Ui::SimPartsDialog *ui;
};

#endif // SIMPARTSDIALOG_H
