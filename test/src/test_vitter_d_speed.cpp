#include "../../src/vitter_d.h"
#include <iostream>

int main(int argc, char ** argv)
{
  try
  {
    uint64_t N = std::stoul(argv[1]);
    uint64_t n = std::stoul(argv[2]);
    BS::vitter_d vd(N, n);

    while (! vd.end())
    {
      vd.next();
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return __LINE__;
  }
  return 0;
}