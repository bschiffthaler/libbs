#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "../../src/describe.h"
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

  BS::desc_stats stats(data);

  std::cout << "Min:" << '\t' << stats.min() << '\n';
  std::cout << "Max:" << '\t' << stats.max() << '\n';
  std::cout << "Mean:" << '\t' << stats.mean() << '\n';
  std::cout << "Median:" << '\t' << stats.median() << '\n';
  std::cout << "Q0:" << '\t' << stats.quantile(0) << '\n';
  std::cout << "Q10:" << '\t' << stats.quantile(0.10) << '\n';
  std::cout << "Q25:" << '\t' << stats.quantile(0.25) << '\n';
  std::cout << "Q75:" << '\t' << stats.quantile(0.75) << '\n';
  std::cout << "Q90:" << '\t' << stats.quantile(0.90) << '\n';
  std::cout << "Q100:" << '\t' << stats.quantile(1) << '\n';


  return 0;
}