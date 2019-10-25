#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <boost/program_options.hpp>

#include "../../src/histogram.h"
#include "../../src/describe.h"
#include "../../src/common.h"

namespace po = boost::program_options;

struct options_t
{
  uint32_t nbins;
  std::string instr;
  bool horizontal;
  uint64_t width;
};

void get_stats(const options_t& opt)
{

  std::vector<double> data;
  std::string line;

  std::shared_ptr<std::istream> stream;

  if (opt.instr == "stdin")
  {
    stream.reset(&std::cin, [](...) {});
  }
  else
  {
    stream.reset(new std::ifstream(opt.instr.c_str()));
    if (! stream->good())
    {
      throw std::runtime_error("Could not open file " + opt.instr + ". "
                               "Please check spelling/permissions.");
    }
  }

  // Read data
  while (std::getline(*stream, line))
  {
    data.push_back(std::stod(line));
  }

  BS::desc_stats<double> stats(data);

  std::cout << "\n##################################\n"
            << "####### General statistics #######\n"
            << "##################################\n\n";

  std::cout << "Min:" << '\t' << stats.min() << '\n';
  std::cout << "Max:" << '\t' << stats.max() << '\n';
  std::cout << "Mean:" << '\t' << stats.mean() << '\n';
  std::cout << "Median:" << '\t' << stats.median() << '\n';
  std::cout << "Q5:" << '\t' << stats.quantile(0.05) << '\n';
  std::cout << "Q10:" << '\t' << stats.quantile(0.10) << '\n';
  std::cout << "Q25:" << '\t' << stats.quantile(0.25) << '\n';
  std::cout << "Q75:" << '\t' << stats.quantile(0.75) << '\n';
  std::cout << "Q90:" << '\t' << stats.quantile(0.90) << '\n';
  std::cout << "Q95:" << '\t' << stats.quantile(0.95) << '\n';

  std::cout << "\n##################################\n"
            << "########### Histogram ############\n"
            << "##################################\n\n";

  BS::histogram<double> hist(stats, opt.nbins);

  if (opt.horizontal)
  {
    hist.print_horizontal(std::cout, opt.width);
  }
  else
  {
    hist.print_vertical(std::cout, opt.width);
  }
}

int main(int argc, char ** argv)
{

  options_t options;

  po::options_description umbrella("Simple summary stats on the command line");

  po::options_description opt("Options");
  opt.add_options()
  ("help,h", "Show this help message")
  ("bins,b", po::value<uint32_t>(&options.nbins)->default_value(30),
   "Number of histogram bins.")
  ("width,w", po::value<uint64_t>(&options.width)->default_value(40),
   "Histogram bar width/height")
  ("horizontal,H", po::bool_switch(&options.horizontal)->default_value(false),
   "Print horizontal histogram")
  ;

  po::options_description req("Input");
  req.add_options()
  ("input-source", po::value<std::string>(&options.instr)->default_value("stdin"),
   "Input. Either a file, 'stdin' or 'stderr'")
  ;

  po::positional_options_description pos;
  pos.add("input-source", 1);

  umbrella.add(opt).add(req);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
            .options(umbrella)
            .positional(pos)
            .run(),
            vm);

  try
  {
    po::notify(vm);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    std::cerr << umbrella << '\n';
    return 1;
  }

  if (vm.count("help"))
  {
    std::cout << umbrella << "\n";
    return 1;
  }

  try
  {
    get_stats(options);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
  }

  return 0;
}