#include <cmath>
#include "aux.h"
#include "vitter_a.h"
#include "vitter_d.h"

namespace BS {

vitter_d::vitter_d(uint64_t N, uint64_t n) :
  _N(N), _n(n), _current(0), _S(0), _init_va(false)
{
  if (n > N)
    throw std::runtime_error("Cannot sample more than population without "
                             "replacement");

  _V_prime = exp(log(global_uniform_unit_db()) / static_cast<double>(_n));
  _quant1 = N - n + 1;
  _quant2 = div_as_double(_quant1, N);
  _threshold = n * VITTER_ALPHA_INV;
}

void vitter_d::update_variables()
{
  _N = _N - _S - 1;
  --_n;
  _quant1 = _quant1 - _S;
  _quant2 = div_as_double(_quant1, _N);
  _threshold -= VITTER_ALPHA_INV;
}

uint64_t vitter_d::gen_skip()
{
  if (_n == 0)
  {
    throw std::runtime_error("[vitter_d::gen_skip] Tried to generate skip for "
                             "n = 0");
  }
  else if (_n > 1 && _threshold < _N)
  {
    while (true)
    {
      double X;
      uint64_t bottom;
      uint64_t limit;
      uint64_t top;
      // Step D2
      while (true)
      {
        X = static_cast<double>(_N) * (1.0 - _V_prime);
        _S = X;
        if (_S < _quant1)
          break;
        else
          _V_prime = exp(log(global_uniform_unit_db()) / 
                         static_cast<double>(_n));
      }
      double y = global_uniform_unit_db() / _quant2;
      // Step D3
      double lhs = exp(log(y) / static_cast<double>(_n - 1));
      double rhs = div_as_double((_quant1 - _S), _quant1) *
                   static_cast<double>(_N) / (static_cast<double>(_N) - X);
      if (lhs <= rhs)
      {
        _V_prime = lhs / rhs;
        update_variables();
        return _S;
      }
      // Step D4
      if ((_n - 1) > _S)
      {
        bottom = _N - _n;
        limit = _N - _S;
      }
      else
      {
        bottom = _N - _S - 1;
        limit = _quant1;
      }
      for (top = _N - 1; top > limit; --top)
      {
        y *= div_as_double(top, bottom);
        --bottom;
      }
      if (exp(log(y) / static_cast<double>(_n - 1)) <=
          static_cast<double>(_N) / (static_cast<double>(_N) - X))
      {
        _V_prime = exp(log(global_uniform_unit_db()) /
                       static_cast<double>(_n - 1));
        update_variables();
        return _S;
      }
      _V_prime = exp(log(global_uniform_unit_db()) / static_cast<double>(_n));
    }
  }
  // If we're not at the last element, we finish off the sampling using
  // method A
  else if (_n > 1)
  {
    if (! _init_va)
    {
      _va = vitter_a(_N, _n);
      _init_va = true;
    }
    _S = _va.gen_skip();
    _n = _va._n;
    _N = _va._N;
    return _S;
  }
  else // (_n == 1)
  {
    _S = (static_cast<double>(_N) * _V_prime);
    update_variables();
    return _S;
  }
}

uint64_t vitter_d::next()
{
  uint64_t ret = _current + gen_skip();
  _current = ret + 1;
  return ret;
}

} // Namespace BS