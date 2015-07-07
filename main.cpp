#include <QApplication>
#include <QThread>

#include "methods/montecarlomethod.h"
#include "mythread.h"
#include "mainwindow.h"

double rt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //����� ��� ����������� (������) �������� ������� �����-�����
    MonteCarloMethod Solver;

    // �����, � ������� ����� ����������� �������
    MyThread worker;

    // ��������� ���������� �������� � �����
    Solver.moveToThread(&worker);

    // ���������� ���������� � ��������� � �������� ����
    QObject::connect(&Solver, SIGNAL(progressChanged(int)), &w, SLOT(progressSet(int)));
    // ���������� �������� �����������
    QObject::connect(&Solver, SIGNAL(SendResults(double,double)), &w, SLOT(GetResults(double,double)));

    // ����� ���������� ������ ���������� - ����� ������ �����������
    QObject::connect(&Solver, SIGNAL(done()), &worker, SLOT(quit()));

    // ������������ ���������� ������ �� ������� ������ Stop
    QObject::connect(&w, SIGNAL(Stop()), &worker, SLOT(stoc()));
    QObject::connect(&worker, SIGNAL(stopc()), &Solver, SLOT(stopcc()));

    // ��������� ������ �������� � �������� ������
    QObject::connect(&w, SIGNAL(MonteCarloStartCount(int,  double,  double, double,  double,  double, bool)),
                     &worker, SLOT(MonteCarloStart(int,  double,  double, double,  double,  double, bool)));
    QObject::connect(&worker, SIGNAL(MonteCarloStarted(int,  double,  double, double,  double,  double, bool)),
                     &Solver, SLOT(StartMonteCarloCount(int,  double,  double, double,  double,  double, bool)));

    return a.exec();
}
