#include <cmath>
#include <stdexcept>
#include "aux.h"
#include "vitter_a.h"
#include "common.h"

namespace BS {

vitter_a::vitter_a(uint64_t N, uint64_t n) : 
  _N(N), _current(0), _n(n), _top(N - n) 
{
  if (n > N)
    throw std::runtime_error("Cannot sample more than population without "
                             "replacement");
}

uint64_t vitter_a::next()
{
  uint64_t ret = _current + gen_skip();
  _current = ret + 1;
  return ret;
}

uint64_t vitter_a::gen_skip()
{
  if (_n == 0)
    throw std::runtime_error("[vitter_a::gen_skip] Tried to generate skip for "
                             "n = 0");
  if (_n > 1)
  {
    // Step A1
    double V = global_uniform_unit_db();
    // Step A2
    uint64_t S = 0;
    double quot = div_as_double<uint64_t>(_top, _N);
    while (quot > V)
    {
      ++S;
      --_top;
      --_N;
      quot = quot * div_as_double<uint64_t>(_top, _N);
    }
    // Step A3
    --_N;
    --_n;
    _S = S;
    return _S;
  }
  else
  {
    _S = static_cast<double>(_N) * global_uniform_unit_db();
    --_n;
    return _S;
  }
}

} //Namespace BS