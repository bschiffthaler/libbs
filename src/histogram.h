#pragma once

#include <algorithm>
#include <vector>
#include <limits>
#include <cstdint>
#include <ostream>
#include "describe.h"

namespace BS {

class desc_stats;

/**
* @brief Generic histogram class for `double` values.
* 
* This class implements a histogram class which counts doubles into equally
* spaced bins. It uses a binary search algorithm to bin data.  
*/
class histogram 
{
 public:
  /**
  * @brief Constructor only defining bounds and number of bins.
  * @param min The lower bound of the histogram data.
  * @param max The upper bound of the histogram data.
  * @param bins The number of bins.
  */
  histogram(const double min, const double max, const uint32_t bins);
  /**
  * @brief Constructor defining bounds and number of bins which also adds data.
  * @param data A vector of data to add.
  * @param min The lower bound of the histogram data.
  * @param max The upper bound of the histogram data.
  * @param bins The number of bins.
  */
  histogram(const std::vector<double>& data, const double min,
            const double max, const uint32_t bins);
  /**
  * @brief Constructor using data to calculate bounds and adds data

  * If the data input vector is not sorted, getting the bounds of the 
  * histogram will require a full pass over the vector so it's preferable to
  * use other constructors that define those bounds if possible.
  * @param data A vector of data to add.
  * @param bins The number of bins.
  * @param sorted Wether the data vector is sorted.
  */
  histogram(const std::vector<double>& data, const uint32_t bins,
            const bool sorted = false);
  /**
  * @brief Constructor using a BS::desc_stats object.
  * @param stats A BS::desc_stats to use.
  * @param bins The number of bins.
  */
  histogram(desc_stats& stats, const uint32_t bins);
  /**
  * @brief Add a new data point to the histogram with bounds checking.

  For slightly faster data insertion without bounds checking see `unsafe_add()`.
  * @param x The data point to add.
  * @see unsafe_add().
  */
  void add(const double& x);
  /**
  * @brief Add a new data point to the histogram without bounds checking.

  For safe data insertion with bounds checking see `add()`.
  * @param x The data point to add.
  * @see add().
  */
  void unsafe_add(const double& x);
  /**
  * @brief Get a reference to the histogram counts.
  * @return A const vector containing the counts for each bin.
  */
  const std::vector<uint64_t>& const_counts() const { return _counts; }
  /**
  * @brief Get a reference to the histogram breaks
  * @return A const vector containing the break points for each bin (the first)
  * "break point" is always the data minimum.
  */
  const std::vector<double>& const_breaks() const { return _breaks; }
  /**
  * @brief Get a reference to the number of bins.
  * @return A const value of the number of bins.
  */
  const uint32_t& const_bins() const { return _bins; }
  /**
  * @brief Get a reference to the data minimum.
  * @return A const value of the lower bound.
  */
  const double& const_min() const { return _min; }
  /**
  * @brief Get a reference to the data maximum.
  * @return A const value of the upper bound.
  */
  const double& const_max() const { return _max; }
  /**
  * @brief Get a copy of the histogram counts.
  * @return A vector containing the counts for each bin.
  */
  std::vector<uint64_t> counts() const { return _counts; }
  /**
  * @brief Get a copy of the histogram breaks
  * @return A vector containing the break points for each bin (the first)
  * "break point" is always the data minimum.
  */
  std::vector<double> breaks() const { return _breaks; }
  /**
  * @brief Get the number of bins.
  * @return The number of bins.
  */
  uint32_t bins() const { return _bins; }
  /**
  * @brief Get the data minimum.
  * @return The lower bound.
  */
  double min() const { return _min; }
  /**
  * @brief Get the data maximum.
  * @return The upper bound.
  */
  double max() const { return _max; }
  /**
  * @brief Print vertical representation of histogram.
  * @param out An output stream to print to.
  * @param width The maximum bar width to print.
  */
  void print_vertical(std::ostream& out, uint64_t width = 80) const;
   /**
  * @brief Print TAB separated histogram.
  * @param out An output stream to print to.
  */
  void print_tsv(std::ostream& out) const;
  private:
  uint32_t _bin(const double& x);
  uint32_t _bins;
  std::vector<double> _breaks;
  std::vector<uint64_t> _counts;
  void _create_breaks();
  double _max;
  double _min;
};

} // namespace BS