#include <string>
#include <unordered_set>
#include "../../src/vitter_d.h"
#include <iostream>

int main(int argc, char ** argv)
{
  try
  {
    uint64_t N = std::stoul(argv[1]);
    uint64_t n = std::stoul(argv[2]);
    BS::vitter_d vd(N, n);

    std::unordered_set<uint64_t> gens;

    while (! vd.end())
    {
      uint64_t cur = vd.next();
      std::cerr << cur << '\n';
      if (cur >= N)
      {
        std::cerr << "Sample greater than population\n";
        return 1; // impossible
      }
      if (gens.find(cur) != gens.end())
      {
        std::cerr << "Sample duplicate\n";
        return 1; // duplicate
      }
      gens.insert(cur);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}