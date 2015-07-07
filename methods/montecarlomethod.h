#ifndef MONTECARLOMETHOD_H
#define MONTECARLOMETHOD_H

#include <algorithm>    // Needed for the "max" function
#include <cmath>

#include <QVector>
#include <QObject>
#include <QApplication>

#include <QMutex>

class MonteCarloMethod : public QObject
{
    Q_OBJECT
public:
    explicit MonteCarloMethod(QObject *parent = 0);
    double gaussian_box_muller();

    double monte_carlo_call_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T);
    double monte_carlo_put_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T);

    double monte_carlo_call_price_American(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T);
    double monte_carlo_put_price_American(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T);

    bool stop;
    QMutex mutex;
signals:
    void progressChanged(int progress);
    void SendResults(double put, double call);
    void done();

public slots:
    void StartMonteCarloCount(int num_sims, double S, double K, const double r, double v, double T, bool type);
    void stopcc();
};

#endif // MONTECARLOMETHOD_H
