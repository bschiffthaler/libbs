#pragma once

#include <vector>

namespace BS {
/**
* @brief Generic descriptive statistics class for `double` values.
* 
* This class implements several descriptive stats for double values.
*/
class desc_stats {
public:
  desc_stats();
  desc_stats(std::vector<double>& data, bool sorted = false);
  void add(double data);
  double quantile(const double q);
  double sum() { return _sum; }
  double min() { return _min; }
  double max() { return _max; }
  double mean() { return _sum / static_cast<double>(_data.size()); }
  double median() { return quantile(0.5); }
private:
  void _update();
  bool _sorted;
  std::vector<double> _data;
  double _sum;
  double _min;
  double _max;
};
}