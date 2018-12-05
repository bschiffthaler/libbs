#include <simple_sample.h>
#include <aux.h>
#include <random>
#include <algorithm>

namespace BS
{

simple_sample::simple_sample(uint64_t N, uint64_t n) :
  _cur(0), _N(N), _n(n)
{
  _samp_v.reserve(n);
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dis(0, N - 1);
  for (uint64_t i = 0; i < n; i++)
  {
    _samp_v.push_back(dis(mt));
  }
  std::sort(_samp_v.begin(), _samp_v.end());
}

uint64_t simple_sample::next()
{
  return _samp_v[_cur++];
}

}
