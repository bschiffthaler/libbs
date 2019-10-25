#include <vector>
#include <iostream>

#include "../../src/histogram.h"
#include "../../src/common.h"

int main(int argc, char ** argv)
{
  
  std::vector<double> data {0, 0.05, 0.1, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.40,
    0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1};
  BS::histogram<double> hist(data, 0, 1, 10);

  try
  {
    hist.print_horizontal(std::cerr, 10);
    std::cerr << "\n=======\n\n";
    hist.print_vertical(std::cerr, 40);
    for (uint32_t i = 0; i < hist.bins(); i++)
    {
      if (i == 1 || i == 9) 
      {
        if (hist.counts()[i] != 3) return __LINE__;
      }
      else
      {
        if (hist.counts()[i] != 2) return __LINE__;
      }
    }
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return __LINE__;
  }

  try  // Should fail
  {
    hist.add(2);
    return __LINE__;
  }
  catch(std::exception& e)
  {
  }

  try  // Should fail
  {
    hist.add(-1);
    return __LINE__;
  }
  catch(std::exception& e)
  {
  }

  std::vector<uint32_t> data2 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  BS::histogram<uint32_t> hist2(data2, 10);

  hist2.print_horizontal(std::cerr, 10);
  std::cerr << "\n=======\n\n";
  hist2.print_vertical(std::cerr, 40);

  return 0;
}