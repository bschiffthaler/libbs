#pragma once

#include <algorithm>
#include <vector>
#include <limits>
#include <cstdint>
#include <ostream>
#include "describe.h"
#include "common.h"

namespace BS {

/**
* @brief Generic histogram class for `double` values.
* 
* This class implements a histogram class which counts doubles into equally
* spaced bins. It uses a binary search algorithm to bin data.  
*/
template <typename T>
class histogram 
{
 public:
  /**
  * @brief Constructor only defining bounds and number of bins.
  * @param min The lower bound of the histogram data.
  * @param max The upper bound of the histogram data.
  * @param bins The number of bins.
  */
  inline histogram(const T min, const T max, const uint32_t bins);
  /**
  * @brief Constructor defining bounds and number of bins which also adds data.
  * @param data A vector of data to add.
  * @param min The lower bound of the histogram data.
  * @param max The upper bound of the histogram data.
  * @param bins The number of bins.
  */
 inline histogram(const std::vector<T>& data, const T min,
            const T max, const uint32_t bins);
  /**
  * @brief Constructor using data to calculate bounds and adds data

  * If the data input vector is not sorted, getting the bounds of the 
  * histogram will require a full pass over the vector so it's preferable to
  * use other constructors that define those bounds if possible.
  * @param data A vector of data to add.
  * @param bins The number of bins.
  * @param sorted Wether the data vector is sorted.
  */
  inline histogram(const std::vector<T>& data, const uint32_t bins,
            const bool sorted = false);
  /**
  * @brief Constructor using a BS::desc_stats object.
  * @param stats A BS::desc_stats to use.
  * @param bins The number of bins.
  */
  inline histogram(desc_stats<T>& stats, const uint32_t bins);
  /**
  * @brief Add a new data point to the histogram with bounds checking.

  For slightly faster data insertion without bounds checking see `unsafe_add()`.
  * @param x The data point to add.
  * @see unsafe_add().
  */
  inline void add(const T& x);
  /**
  * @brief Add a new data point to the histogram without bounds checking.

  For safe data insertion with bounds checking see `add()`.
  * @param x The data point to add.
  * @see add().
  */
  inline void unsafe_add(const T& x);
  /**
  * @brief Get a reference to the histogram counts.
  * @return A const vector containing the counts for each bin.
  */
  inline const std::vector<uint64_t>& const_counts() const { return _counts; }
  /**
  * @brief Get a reference to the histogram breaks
  * @return A const vector containing the break points for each bin (the first)
  * "break point" is always the data minimum.
  */
  inline const std::vector<T>& const_breaks() const { return _breaks; }
  /**
  * @brief Get a reference to the number of bins.
  * @return A const value of the number of bins.
  */
  inline const uint32_t& const_bins() const { return _bins; }
  /**
  * @brief Get a reference to the data minimum.
  * @return A const value of the lower bound.
  */
  inline const T& const_min() const { return _min; }
  /**
  * @brief Get a reference to the data maximum.
  * @return A const value of the upper bound.
  */
  inline const T& const_max() const { return _max; }
  /**
  * @brief Get a copy of the histogram counts.
  * @return A vector containing the counts for each bin.
  */
  inline std::vector<uint64_t> counts() const { return _counts; }
  /**
  * @brief Get a copy of the histogram breaks
  * @return A vector containing the break points for each bin (the first)
  * "break point" is always the data minimum.
  */
  inline std::vector<T> breaks() const { return _breaks; }
  /**
  * @brief Get the number of bins.
  * @return The number of bins.
  */
  inline uint32_t bins() const { return _bins; }
  /**
  * @brief Get the data minimum.
  * @return The lower bound.
  */
  inline T min() const { return _min; }
  /**
  * @brief Get the data maximum.
  * @return The upper bound.
  */
  inline T max() const { return _max; }
  /**
  * @brief Print vertical representation of histogram.
  * @param out An output stream to print to.
  * @param width The maximum bar width to print.
  */
  inline void print_vertical(std::ostream& out, uint64_t width = 80) const;
   /**
  * @brief Print TAB separated histogram.
  * @param out An output stream to print to.
  */
  inline void print_tsv(std::ostream& out) const;
  inline void print_horizontal(std::ostream& out, uint64_t height = 30) const;
  private:
  uint32_t _bin(const T& x);
  void _create_breaks();
  //
  uint32_t _bins;
  std::vector<T> _breaks;
  std::vector<uint64_t> _counts;
  T _max;
  T _min;
};

template <typename T>
histogram<T>::histogram(const T min, const T max, const uint32_t bins) :
  _bins(bins), _max(max), _min(min)
{
  _counts.resize(_bins, 0);
  _create_breaks();
}

template <typename T>
histogram<T>::histogram(const std::vector<T>& data, const T min,
                     const T max, const uint32_t bins) :
  _bins(bins), _max(max), _min(min)
{
  _counts.resize(_bins, 0);
  _create_breaks();
  for (auto& x : data)
    add(x);
}

template <typename T>
histogram<T>::histogram(const std::vector<T>& data, const uint32_t bins,
                     const bool sorted) :
  _bins(bins), _max(- std::numeric_limits<T>::infinity()),
  _min(std::numeric_limits<T>::infinity())
{
  if (data.size() == 0)
    throw std::runtime_error("[BS::histogram::histogram] data vector is empty");
  if (sorted)
  {
    _min = data.at(0);
    _max = data.at(data.size() - 1);
  }
  else
  {
    for (const auto& x : data)
    {
      if (x < _min) _min = x;
      if (x > _max) _max = x;
    }
  }
  _counts.resize(_bins, 0);
  _create_breaks();
  for (auto& x : data)
    add(x);
}

template <typename T>
histogram<T>::histogram(desc_stats<T>& stats, const uint32_t bins) : _bins(bins)
{
  stats._update();
  _min = stats._data.at(0);
  _max = stats._data.at(stats._data.size() - 1);
  _counts.resize(_bins, 0);
  _create_breaks();
  for (auto& x : stats._data)
    add(x);
}

template <typename T>
void histogram<T>::_create_breaks()
{
  T diff = _max - _min;
  _breaks.push_back(_min);
  double nbins = static_cast<double>(_bins);
  double step = diff / nbins;
  for (uint32_t i = 1; i < _bins; i++)
  {
    double di = static_cast<double>(i);
    _breaks.push_back(_min + static_cast<T>(step * di));
  }
}

template <typename T>
uint32_t histogram<T>::_bin(const T& x)
{
  auto ptr = std::lower_bound(_breaks.begin(), _breaks.end(), x, almost_lt_eq<T>);
  uint32_t ind = std::distance(_breaks.begin(), ptr) - 1;
  return std::min(ind, _bins - 1);
}

template <typename T>
void histogram<T>::add(const T& x)
{
  if (! almost_lt_eq<T>(x, _max))
    throw std::runtime_error("[BS::histogram::add] Trying to add value " +
                             std::to_string(x) + " greater than max " +
                             std::to_string(_max) + " in the histogram");
  if (! almost_gt_eq<T>(x, _min))
    throw std::runtime_error("[BS::histogram::add] Trying to add value "  +
                             std::to_string(x) + " less than min " +
                             std::to_string(_min) + " in the histogram");
  _counts[_bin(x)]++;
}

template <typename T>
void histogram<T>::unsafe_add(const T& x)
{
  _counts[_bin(x)]++;
}

template <typename T>
void histogram<T>::print_vertical(std::ostream& out, uint64_t width) const
{
  std::vector<std::string> axis;
  uint64_t sum_of_counts = 0;
  uint64_t max_counts = 0;
  for (uint32_t i = 0; i < _bins; i++)
  {
    T ub = (i == (_bins - 1)) ? _max : _breaks[i + 1];
    T lb = _breaks[i];
    char rbr = (i == (_bins - 1)) ? ']' : ')';
    std::string ax;
    ax += '[';
    ax += std::to_string(lb);
    ax += std::string(", ");
    ax += std::to_string(ub);
    ax += rbr;
    axis.push_back(ax);
    sum_of_counts += _counts[i];
    if (_counts[i] > max_counts)
    {
      max_counts = _counts[i];
    }
  }
  uint64_t max_axis_len = 0;
  for (const auto& ax : axis)
  {
    if (ax.size() > max_axis_len)
    {
      max_axis_len = ax.size();
    }
  }
  for (uint32_t i = 0; i < _bins; i++)
  {
    uint64_t cur_axis_len = axis[i].size();
    for (uint64_t j = cur_axis_len; j < max_axis_len; j++)
    {
      out << ' ';
    }
    out << axis[i] << '\t';
    double fraction = div_as_double(_counts[i], max_counts);
    double height = static_cast<double>(width) * fraction;
    uint64_t bheight = height < 0 ? 0 : static_cast<uint64_t>(height);

    for (uint64_t j = 0; j < bheight; j++)
    {
      out << '#';
    }
    out << ' ' << _counts[i] << '\n';
  }
}

template <typename T>
void histogram<T>::print_tsv(std::ostream& out) const
{
  for (uint32_t i = 0; i < _bins; i++)
  {
    T ub = (i == (_bins - 1)) ? _max : _breaks[i + 1];
    T lb = _breaks[i];
    out << lb << '\t' << ub << '\t' << _counts[i] << '\n';
  }
}

template <typename T>
void histogram<T>::print_horizontal(std::ostream& out, uint64_t height) const
{
  std::vector<std::string> axis;
  uint64_t sum_of_counts = 0;
  uint64_t max_counts = 0;
  uint64_t min_counts = std::numeric_limits<uint64_t>::min();
  for (uint32_t i = 0; i < _bins; i++)
  {
    T ub = (i == (_bins - 1)) ? _max : _breaks[i + 1];
    T lb = _breaks[i];
    char rbr = (i == (_bins - 1)) ? ']' : ')';
    std::string ax;
    ax += '[';
    ax += std::to_string(lb);
    ax += std::string(", ");
    ax += std::to_string(ub);
    ax += rbr;
    axis.push_back(ax);
    sum_of_counts += _counts[i];
    if (_counts[i] > max_counts)
    {
      max_counts = _counts[i];
    }
    if (_counts[i] < min_counts)
    {
      min_counts = _counts[i];
    }
  }

  std::string min = std::to_string(min_counts);
  std::string max = std::to_string(max_counts);

  uint64_t minlen = min.size();
  uint64_t maxlen = max.size();
  uint64_t padding = minlen > maxlen ? minlen : maxlen;
  padding++;


  for (uint64_t i = 0; i < height; i++)
  {
    if (i == 0)
    {
      out << max;
      for (uint64_t p = 0; p < padding - maxlen; p++)
      {
        out << ' ';
      }
    }
    else if (i == height - 1)
    {
      out << min;
      for (uint64_t p = 0; p < padding - minlen; p++)
      {
        out << ' ';
      }
    }
    else
    {
      for (uint64_t p = 0; p < padding; p++)
      {
        out << ' ';
      }
    }
    out << "|";
    for (uint32_t j = 0; j < _bins; j++)
    {
      uint64_t cheight = height - i;
      double fraction = div_as_double(_counts[j], max_counts);
      double bar = static_cast<double>(height) * fraction;
      uint64_t bheight = bar < 0 ? 0 : static_cast<uint64_t>(bar);
      if (bheight >= cheight)
      {
        out << '#';
      }
      else
      {
        out << ' ';
      }
    }
    out << '\n';
  }
  for (uint64_t p = 0; p < padding + 1; p++)
  {
    out << ' ';
  }
  for (uint32_t j = 0; j < _bins; j++)
  {
    out << "=";
  }
  out << '\n';
  for (uint64_t p = 0; p < padding + 1; p++)
  {
    out << ' ';
  }
  out << '|';
  for (uint64_t p = 1; p < _bins - 1; p++)
  {
    out << ' ';
  }
  out << "|\n";
  for (uint64_t p = 0; p < padding + 1; p++)
  {
    out << ' ';
  }
  std::string lb = std::to_string(_min);
  std::string ub = std::to_string(_max);
  out << lb;

  for (uint64_t p = lb.size(); p < _bins - 1; p++)
  {
    out << ' ';
  }
  out << ub << '\n';

}

} // namespace BS