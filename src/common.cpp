#include <limits>
#include <cmath>
#include <common.h>

namespace BS {

bool almost_lt_eq(const double lhs, const double rhs)
{
  if (almost_eq(lhs, rhs))
    return true;
  else if (lhs < rhs)
    return true;
  else
    return false;
}

bool almost_gt_eq(const double lhs, const double rhs)
{
  if (almost_eq(lhs, rhs))
    return true;
  else if (lhs > rhs)
    return true;
  else
    return false;
}

bool almost_eq(const double lhs, const double rhs)
{
  double diff = fabs(lhs - rhs);
  double greater = lhs > rhs ? lhs : rhs;
  if (diff <= greater * std::numeric_limits<double>::epsilon())
    return true;
  else
    return false;
}

}