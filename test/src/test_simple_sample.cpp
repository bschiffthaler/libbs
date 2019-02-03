#include <string>
#include "../../src/simple_sample.h"
#include <iostream>

int main(int argc, char ** argv)
{
  try
  {
    uint64_t N = std::stoul(argv[1]);
    uint64_t n = std::stoul(argv[2]);
    BS::simple_sample<uint32_t> ss(N, n);

    while (! ss.end())
    {
      uint64_t cur = ss.next();
      std::cerr << cur << '\n';
      if (cur >= N)
      {
        std::cerr << "Sample greater than population\n";
        return 1; // impossible
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}