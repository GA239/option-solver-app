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

    //класс для паралельных (тяжёлых) расчётов методом Монте-Карло
    MonteCarloMethod Solver;

    // Поток, в котором будут выполняться расчёты
    MyThread worker;

    // Переносим выполнение расчётов в поток
    Solver.moveToThread(&worker);

    // Подключить оповещения о прогрессе к прогресс бару
    QObject::connect(&Solver, SIGNAL(progressChanged(int)), &w, SLOT(progressSet(int)));
    // Подключить передачу результатов
    QObject::connect(&Solver, SIGNAL(SendResults(double,double)), &w, SLOT(GetResults(double,double)));

    // Когда выполнение работы закончится - поток должен завершиться
    QObject::connect(&Solver, SIGNAL(done()), &worker, SLOT(quit()));

    // Обеспечиваем прерывание потока по нажатию кнопки Stop
    QObject::connect(&w, SIGNAL(Stop()), &worker, SLOT(stoc()));
    QObject::connect(&worker, SIGNAL(stopc()), &Solver, SLOT(stopcc()));

    // соединяем начало расчётов с запуском потока
    QObject::connect(&w, SIGNAL(MonteCarloStartCount(int,  double,  double, double,  double,  double, bool)),
                     &worker, SLOT(MonteCarloStart(int,  double,  double, double,  double,  double, bool)));
    QObject::connect(&worker, SIGNAL(MonteCarloStarted(int,  double,  double, double,  double,  double, bool)),
                     &Solver, SLOT(StartMonteCarloCount(int,  double,  double, double,  double,  double, bool)));

    return a.exec();
}
