#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "../../src/histogram.h"
#include "../../src/common.h"

int main(int argc, char ** argv)
{
  
  std::vector<double> data;
  std::ifstream ifs(argv[1]);
  std::string line;
  while (std::getline(ifs, line))
  {
    data.push_back(std::stod(line));
  }

  BS::histogram hist(data, 25, false);

  hist.print_vertical(std::cout);

  std::cout << "\n\n##########################\n\n";

  hist.print_tsv(std::cout);

  return 0;
}