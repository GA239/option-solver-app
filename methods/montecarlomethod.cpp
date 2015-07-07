#include "montecarlomethod.h"

MonteCarloMethod::MonteCarloMethod(QObject *parent) :
    QObject(parent)
{
    stop = false;
}

// ���������� ������
void MonteCarloMethod::stopcc()
{
      stop = true;
}

// ���������� ������������ ������� ������ b ��� ���������� 0 ���� ������ ����
double maximum(QVector<double> b)
{
    double _max = 0;
    if(b.size() != 0)
    {
        _max = b[0];
        for ( int i = 0; i < b.size(); i++)
        {
            if (_max < b[i])
            {
                _max = b[i];
            }
        }
    }
    return _max;
}


// ������� ���������� ��������� Box- Muller , ������������ ��� ���������
// ����������� ��������� ����� - ����������x ��� vtnjlf �����-�����/
/// <random> ����������, ������� ����� ���� ������������ ������ ���� �������
double MonteCarloMethod::gaussian_box_muller()
{
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  // ��������� ���� ����������� ��������� �������
  // ���� ������� �� "��������� ����������"
  // ������ �������
  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

// ������ ������ ������� ����� ������������ ���� ������� �����-�����
double MonteCarloMethod::monte_carlo_call_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
{
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<num_sims; i++)
  {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
    payoff_sum += std::max(S_cur - K, 0.0);
  }
  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ������ ������ ������� ������� ������������ ���� ������� �����-�����
double MonteCarloMethod::monte_carlo_put_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
{
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<num_sims; i++)
  {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
    payoff_sum += std::max(K - S_cur, 0.0);
  }
  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ������ ������ ������� ����� ������������� ���� ������� �����-�����
double MonteCarloMethod::monte_carlo_call_price_American(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
{
  double step = T/num_sims;
  double m = 0.02;
  double t = 0;
  double q = 0;
  q += m;
  int progress = 0;
  QVector<double> pricies;

  while(t <= T)
  {
      if (stop)
      {
        break;
      }
      QApplication::processEvents();
      t += step;
      if(t > q)
      {
          progress++;
          q += m;
          emit progressChanged(progress);
      }
      double prise = monte_carlo_call_price(num_sims, S, K, r, v, t);
      pricies.push_back(prise);
  }
  return maximum(pricies);
}

// ������ ������ ������� ������� ������������� ���� ������� �����-�����
double MonteCarloMethod::monte_carlo_put_price_American(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
{
  double step = T/num_sims;
  double m = 0.02;
  double t = 0;
  double q = 0;
  q += m;
  int progress = 50;
  QVector<double> pricies;

  while(t <= T)
  {
      if (stop)
      {
        // ��������� �� ����������
        break;
      }
      //������������ ��������� ������� ��������� � ����������� �����.
      QApplication::processEvents();
      t += step;
      if(t > q)
      {
          // �������� �������� �� progress bar
          progress++;
          q += m;
          emit progressChanged(progress);
      }
      double prise = monte_carlo_put_price(num_sims, S, K, r, v, t);
      pricies.push_back(prise);
  }
  return maximum(pricies);
}

// �������� ����, �������������� ������ ������� ��������� ��������.
void MonteCarloMethod::StartMonteCarloCount(int num_sims, double S, double K, const double r, double v, double T, bool type)
{
    double call = 0;
    double put = 0;
    stop = false;
    if(type)
    {
        emit progressChanged(0);
        call = monte_carlo_call_price(num_sims, S, K, r, v, T);
        // ��������� ���������� � ���������
        emit progressChanged(50);
        put = monte_carlo_put_price(num_sims, S, K, r, v, T);
    }
    else
    {
        emit progressChanged(0);
        call = monte_carlo_call_price_American(num_sims, S, K, r, v, T);
        // ��������� ���������� � ���������
        put = monte_carlo_put_price_American(num_sims, S, K, r, v, T);
    }
    if(!stop)
    {
        emit SendResults(put,call);
    }
    emit done();
}
