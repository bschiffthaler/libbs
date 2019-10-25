#pragma once
#include <cmath>
#include <limits>

namespace BS {

template <typename T>
bool almost_eq(const T lhs, const T rhs)
{
  if (std::numeric_limits<T>::is_integer)
  {
    return lhs == rhs;
  }
  else
  {
    T diff = fabs(lhs - rhs);
    T greater = lhs > rhs ? lhs : rhs;
    if (diff <= fabs(greater * std::numeric_limits<T>::epsilon()))
      return true;
    else
      return false;
  }
}

template <typename T>
bool almost_lt_eq(const T lhs, const T rhs)
{
  if (almost_eq<T>(lhs, rhs))
    return true;
  else if (lhs < rhs)
    return true;
  else
    return false;
}

template <typename T>
bool almost_gt_eq(const T lhs, const T rhs)
{
  if (almost_eq<T>(lhs, rhs))
    return true;
  else if (lhs > rhs)
    return true;
  else
    return false;
}

/**
* @brief Helper function to cast uint64_t to double and divide
*/
template <typename T>
double div_as_double(T numerator, T denominator)
{
  return static_cast<double>(numerator) / static_cast<double>(denominator);
}


} // namespace BS