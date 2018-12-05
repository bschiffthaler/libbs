#pragma once
#include <vector>
#include <cstdint>
#include <random>
#include <algorithm>

namespace BS 
{
/**
* @brief Simple class for oversampling with replacement.
*
* Sample generated are stored in a basic sorted vector
*/
template <typename T>
class simple_sample {
public:
  /**
  * @brief Empty constructor.
  */
  simple_sample(){}
  /**
  * @brief Basic constructor.
  * @param N The population size
  * @param n The sample size
  */
  simple_sample(T N, T n);
  /**
  * @brief Get the next sample
  * @return The next sample (in order)
  */
  T next();
  /**
  * @brief Check if all data has been sampled
  * @return `true` if all data has beend sampled, `false` otherwise
  */
  bool end() {return _cur == (_n - 1); }
private:
  std::vector<T> _samp_v;
  T _N;
  T _n;
  T _cur;
};

template <typename T>
simple_sample<T>::simple_sample(T N, T n) :
  _cur(0), _N(N), _n(n)
{
  _samp_v.reserve(n);
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dis(0, N - 1);
  for (T i = 0; i < n; i++)
  {
    _samp_v.push_back(dis(mt));
  }
  std::sort(_samp_v.begin(), _samp_v.end());
}

template <typename T>
T simple_sample<T>::next()
{
  return _samp_v[_cur++];
}

}