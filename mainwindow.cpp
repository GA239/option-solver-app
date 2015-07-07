#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("Option Solver App"));
    moveToCenter();
    forminitilaise();

    Data = NULL;

    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OptionSolve()));
    connect(this,SIGNAL(MonteCarloStartCount(int,  double,  double, double,  double,  double, bool)),
            this, SLOT(ShowBar()));

    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(StopCount()));

}
// на центр экрана
void MainWindow::moveToCenter()
{
    setFixedSize(450,330);
    QRect rect = frameGeometry();
    rect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(rect.topLeft());
}

MainWindow::~MainWindow()
{
    deletedata();
    delete ui;
}

void MainWindow::forminitilaise()
{
    ui->label->setText("Underlying");
    ui->label_2->setText("Strike");
    ui->label_3->setText("Risk-Free Rate");
    ui->label_4->setText("Volatility");
    ui->label_5->setText("Maturity");

    ui->lineEdit->setText("100");
    ui->lineEdit_2->setText("100");
    ui->lineEdit_3->setText("0.05");
    ui->lineEdit_4->setText("0.2");
    ui->lineEdit_5->setText("1");

    ui->label_6->setText("Call Price:");
    ui->label_7->setText("Put Price:");
    ui->label_8->setText("Method");

    QStringList values;
    values.append("Black-Scholes");
    values.append("Monte-Carlo  European");
    values.append("Monte-Carlo  American");

    ui->comboBox->addItems(values);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->hide();
    ui->pushButton_2->hide();
}

// передаём значение в progressBar
void MainWindow::progressSet(int progress)
{
    ui->progressBar->setValue(progress);
}

// осатновка расчётов
void MainWindow::StopCount()
{
   ui->pushButton_2->hide();
   ui->progressBar->hide();
   ui->pushButton->show();
   emit Stop();
}

void MainWindow::ShowBar()
{
    ui->pushButton_2->show();
    ui->progressBar->show();
    ui->pushButton->hide();
}

void MainWindow::GetResults(double put, double call)
{
    Data->call = call;
    Data->put = put;
    ShowResults();
}

void MainWindow::ShowResults()
{
    ui->lineEdit_6->setText(QString::number(Data->call, 'f', 8));
    ui->lineEdit_7->setText(QString::number(Data->put, 'f', 8));
    ui->progressBar->hide();
    ui->pushButton_2->hide();
    ui->pushButton->show();
}

// основной метод обеспечивающий начало расчёта стоимостей опциона
void MainWindow::OptionSolve()
{
    FormParams* Values;
    bool valid_values = true;
    Values = GetParams(&valid_values);

    if(valid_values)
    {
        deletedata();
        Data = new OptionController(Values);
        MethodCount();
    }
    delete Values;
}

// запускает алгоритм расчёта в соответствии с методом
void MainWindow::MethodCount()
{
    QString method = ui->comboBox->currentText();
    if(method == "Black-Scholes")
    {
        Data->Solve_with_BlackScholesAnalytic();
        ShowResults();
    }
    if(method == "Monte-Carlo  European")
    {
        MonteCarloRun(true);
    }
    if(method == "Monte-Carlo  American")
    {
        MonteCarloRun(false);
    }
}

// запускает алгоритм расчёта методом монте карло (true - Europ; false - American)
void MainWindow::MonteCarloRun(bool type)
{
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    SimPartsDialog  form(this);
    if (form.exec() == QDialog::Accepted)
    {
        Data->num_sims = form.getvalue();
        if(Data->num_sims > 0)
        {
            emit MonteCarloStartCount(Data->num_sims, Data->S, Data->K, Data->r, Data->v, Data->T,type);
        }
    }
}

void MainWindow::deletedata()
{
    if(Data != NULL)
    {
        delete Data;
        Data = NULL;
    }
}

void CheckStr(FormParams* str, bool* gl_check)
{
    if(str->Maturity <= 0)
    {
        *gl_check = false;
    }
    if(str->Risk_Free_Rate < 0)
    {
        *gl_check = false;
    }
    if(str->Strike < 0)
    {
        *gl_check = false;
    }
    if(str->Underlying < 0)
    {
        *gl_check = false;
    }
    if(str->Volatility < 0)
    {
        *gl_check = false;
    }
}
void CheckParams(bool parametr, bool* gl_check)
{
    if(!parametr)
    {
        *gl_check = false;
    }
}
FormParams* MainWindow::GetParams(bool* valid_params)
{
    FormParams* FP = new FormParams;
    bool ok;

    FP->Underlying = ui->lineEdit->text().toDouble(&ok);
    CheckParams(ok,valid_params);
    FP->Strike = ui->lineEdit_2->text().toDouble(&ok);
    CheckParams(ok,valid_params);
    FP->Risk_Free_Rate = ui->lineEdit_3->text().toDouble(&ok);
    CheckParams(ok,valid_params);
    FP->Volatility = ui->lineEdit_4->text().toDouble(&ok);
    CheckParams(ok,valid_params);
    FP->Maturity =  ui->lineEdit_5->text().toDouble(&ok);
    CheckParams(ok,valid_params);
    CheckStr(FP,valid_params);
    if(!*valid_params)
    {
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        QMessageBox::information(this, tr("ERROR"),tr("Invalid Values"));

    }
    else
    {
        return FP;
    }
    return NULL;
}
