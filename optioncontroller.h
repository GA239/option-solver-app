#ifndef OPTIONCONTROLLER_H
#define OPTIONCONTROLLER_H

#include "methods/blackscholesanalytic.h"
typedef struct
{
    double Underlying;
    double Strike;
    double Risk_Free_Rate;
    double Volatility;
    double Maturity;

} FormParams;

class OptionController
{
public:
    OptionController(FormParams *params);

    double S;    // Option price
    double K;    // Strike price
    double r;    // Risk-free rate (5%)
    double v;    // Volatility of the underlying (20%)
    double T;    // One year until expiry

    int num_sims;// Number of simulated asset paths

    double call; // call price
    double put;  // put price

    void Solve_with_BlackScholesAnalytic();

};

#endif // OPTIONCONTROLLER_H
