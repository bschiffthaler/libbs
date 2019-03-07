#pragma once

#include <vector>
#include "histogram.h"

namespace BS {
/**
* @brief Generic descriptive statistics class for `double` values.
* 
* This class implements several descriptive stats for double values.
*/
class desc_stats {
public:
  /**
  * @brief Empty constructor
  */
  desc_stats();
  /**
  * @brief Constructor from a vector.
  * @param data A vector<double> containing the data.
  * @param sorted Indicates wether `data` is sorted.
  */
  desc_stats(std::vector<double>& data, bool sorted = false);
  /**
  * @brief Add a single data point.
  * @param data A double data point.
  *
  * Note that adding data will invalidate the sort order and the underlying data
  * structure will be sorted before returning any stats. It is always more 
  * efficient to call the getters once all data is added.
  */
  void add(double data);
  /**
  * @brief Retrieve the value at a given quantile.
  * @param q The quantile as a fraction, e.g.: `0.5` for Q50.
  * @return The value of the data at the given quantile. 
  */
  double quantile(const double q);
  /**
  * @brief Retrieve the sum of the data.
  * @return The sum of the data.
  */
  double sum() { _update(); return _sum; }
  /**
  * @brief Retrieve the min of the data.
  * @return The min of the data.
  */
  double min() { _update(); return _min; }
  /**
  * @brief Retrieve the max of the data.
  * @return The max of the data.
  */
  double max() { _update(); return _max; }
  /**
  * @brief Retrieve the mean of the data.
  * @return The mean of the data.
  */
  double mean() { _update(); return _sum / static_cast<double>(_data.size()); }
  /**
  * @brief Retrieve the median of the data.
  * @return The median of the data.
  */
  double median() { _update(); return quantile(0.5); }
  /**
  * @brief Retrieve the magnitude of the data.
  * @return The magnitude of the data.
  */
  uint64_t size() { return _data.size(); }
  friend class histogram;
private:
  std::vector<double> _data;
  double _max;
  double _min;
  bool _sorted;
  double _sum;
  void _update();
};
}