#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

signals:
    void MonteCarloStarted( int num_sims,  double S,  double K, double r,  double v,  double T, bool type);
    void stopc();
public slots:
    void MonteCarloStart( int num_sims,  double S,  double K, double r,  double v,  double T, bool type);
    void stoc();
};

#endif // MYTHREAD_H
