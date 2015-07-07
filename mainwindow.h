#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "optioncontroller.h"

#include <QProgressBar>
#include <QThread>
#include <QDesktopWidget>

#include "methods/simpartsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void forminitilaise();
    void moveToCenter();
    ~MainWindow();
    void deletedata();

    FormParams* GetParams(bool *valid_params);
    void MethodCount();
    void MonteCarloRun(bool type);

    OptionController* Data;

public slots:
    void StopCount();
    void ShowResults();
    void OptionSolve();
    void progressSet(int progress);
    void GetResults(double put, double call);
    void ShowBar();
signals:
    void Stop();
    void MonteCarloStartCount( int num_sims,  double S,  double K, double r,  double v,  double T, bool type);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
