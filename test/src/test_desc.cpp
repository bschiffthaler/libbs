#include <vector>
#include <iostream>

#include "../../src/describe.h"
#include "../../src/common.h"

int main(int argc, char ** argv)
{
  
  std::vector<double> data {0, 0.05, 0.1, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.40,
    0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1, 1};
  BS::desc_stats<double> desc(data);

  if (! BS::almost_eq<double>(desc.min(), 0))
  {
    return __LINE__;
  }
  if (! BS::almost_eq<double>(desc.max(), 1))
  {
    return __LINE__;
  }
  if (! BS::almost_eq<double>(desc.median(), 0.525))
  {
    std::cerr << desc.median() << '\n';
    return __LINE__;
  }

  desc.add(1);
  if (! BS::almost_eq<double>(desc.median(), 0.55))
  {
    std::cerr << desc.median() << '\n';
    return __LINE__;
  }

  std::cerr << desc.quantile(0.49) << '\n';

  return 0;
}