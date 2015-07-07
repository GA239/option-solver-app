#include "mythread.h"

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
}
// запуск расчётов
void MyThread::MonteCarloStart(int num_sims,  double S,  double K, double r,  double v,  double T, bool type)
{
    this->start();
    emit MonteCarloStarted(num_sims, S, K, r, v, T, type);
    emit this->started();
}
// остановка потока
void MyThread::stoc()
{
    emit stopc();
}
