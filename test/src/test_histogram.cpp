#include <vector>
#include <iostream>

#include "../../src/histogram.h"
#include "../../src/common.h"

int main(int argc, char ** argv)
{
  
  std::vector<double> data {0, 0.05, 0.1, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.40,
    0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1};
  BS::histogram hist(data, 0, 1, 10);

  try
  {
    for (uint32_t i = 0; i < hist.bins(); i++)
    {
      if (i != hist.bins() - 1)
      {
        if (hist.counts()[i] != 2) return 1;
      }
      else
      {
        if (hist.counts()[i] != 3) return 1;
      }
    }
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  try  // Should fail
  {
    hist.add(2);
    return 1;
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  try  // Should fail
  {
    hist.add(-1);
    return 1;
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}