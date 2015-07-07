#include "optioncontroller.h"
#include <QProgressBar>
#include <QThread>

OptionController::OptionController(FormParams* params)
{
    S = params->Underlying;     // Option price
    K = params->Strike;         // Strike price
    r = params->Risk_Free_Rate; // Risk-free rate (5%)
    v = params->Volatility;     // Volatility of the underlying (20%)
    T = params->Maturity;       // One year until expiry

    num_sims = 10000;

    call = 0;
    put = 0;

}

void OptionController::Solve_with_BlackScholesAnalytic()
{
    BlackScholesAnalytic Solver;
    call = Solver.call_price(S, K, r, v, T);
    put = Solver.put_price(S, K, r, v, T);
}
