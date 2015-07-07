#ifndef BLACKSCHOLESANALYTIC_H
#define BLACKSCHOLESANALYTIC_H

class BlackScholesAnalytic
{
public:
    BlackScholesAnalytic();

    double norm_pdf(const double& x);
    double norm_cdf(const double& x);

    double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T);

    double call_price(const double& S, const double& K, const double& r, const double& v, const double& T);
    double put_price(const double& S, const double& K, const double& r, const double& v, const double& T);

};

#endif // BLACKSCHOLESANALYTIC_H
