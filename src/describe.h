#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include "common.h"
#include "histogram.h"

namespace BS {
/**
* @brief Generic descriptive statistics class for `double` values.
* 
* This class implements several descriptive stats for double values.
*/
template <typename T>
class desc_stats {
public:
  /**
  * @brief Empty constructor
  */
  inline desc_stats();
  /**
  * @brief Constructor from a vector.
  * @param data A vector<double> containing the data.
  * @param sorted Indicates wether `data` is sorted.
  */
  inline desc_stats(std::vector<T>& data, bool sorted = false);
  /**
  * @brief Add a single data point.
  * @param data A double data point.
  *
  * Note that adding data will invalidate the sort order and the underlying data
  * structure will be sorted before returning any stats. It is always more 
  * efficient to call the getters once all data is added.
  */
  inline void add(T data);
  /**
  * @brief Retrieve the value at a given quantile.
  * @param q The quantile as a fraction, e.g.: `0.5` for Q50.
  * @return The value of the data at the given quantile. 
  */
  inline double quantile(const double q);
  /**
  * @brief Retrieve the sum of the data.
  * @return The sum of the data.
  */
  inline T sum() { _update(); return _sum; }
  /**
  * @brief Retrieve the min of the data.
  * @return The min of the data.
  */
  inline T min() { _update(); return _min; }
  /**
  * @brief Retrieve the max of the data.
  * @return The max of the data.
  */
  inline T max() { _update(); return _max; }
  /**
  * @brief Retrieve the mean of the data.
  * @return The mean of the data.
  */
  inline double mean() { _update(); return _sum / static_cast<double>(_data.size()); }
  /**
  * @brief Retrieve the median of the data.
  * @return The median of the data.
  */
  inline double median() { _update(); return quantile(0.5); }
  /**
  * @brief Retrieve the magnitude of the data.
  * @return The magnitude of the data.
  */
  inline uint64_t size() const { return _data.size(); }
  inline uint64_t count() const { return size(); }
  template <typename U> friend class histogram;
private:
  void _update();
  //
  std::vector<T> _data;
  T _max;
  T _min;
  bool _sorted;
  T _sum;
};

template <typename T>
desc_stats<T>::desc_stats() : _max(-std::numeric_limits<T>::infinity()),
  _min(std::numeric_limits<T>::infinity()), _sorted(false), _sum(0) {}

template <typename T>
desc_stats<T>::desc_stats(std::vector<T>& data, bool sorted) :
  _max(-std::numeric_limits<T>::infinity()),
  _min(std::numeric_limits<T>::infinity()), _sorted(false), _sum(0)
{
  if (data.size() == 0)
  {
    throw std::runtime_error("[BS::desc_stats::desc_stats] Data vector length 0");
  }
  if (sorted)
  {
    for (T& d : data)
    {
      _data.push_back(d);
      _sum += d;
    }
    _min = data[0];
    _max = data[data.size() - 1];
    _sorted = true;
  }
  else
  {
    for (T& d : data)
    {
      _data.push_back(d);
    }
    _update();
  }
}

template <typename T>
void desc_stats<T>::_update()
{
  if (! _sorted)
  {
    std::sort(_data.begin(), _data.end());
    _min = _data[0];
    _max = _data[_data.size() - 1];
    _sum = std::accumulate(_data.begin(), _data.end(), 0);
    _sorted = true;
  }
}

template <typename T>
void desc_stats<T>::add(T data)
{
  _data.push_back(data);
  if (_sorted)
  {
    _sorted = false;
  }
}

template <typename T>
double desc_stats<T>::quantile(const double q)
{
  if (q < 0 || q > 1)
  {
    throw std::runtime_error("[BS::desc_stats::quantile]\t Probability must be"
                             "between 0 and 1");
  }
  _update();
  // Some value sanity in extremities
  if (almost_eq<T>(q, 0))
  {
    return _data[0];
  }
  if (almost_eq<T>(q, 1))
  {
    return _data[_data.size() - 1];
  }
  // Get index of probablities
  double h = q * static_cast<double>(_data.size() - 1) + 1;
  uint64_t i0;
  if (q < 0)
  {
    return static_cast<double>(_data[0]);
  }
  else if (q > 1)
  {
    return static_cast<double>(_data[_data.size() - 1]);
  }
  else if (almost_eq<double>(h, std::floor(h)))
  {
    i0 = std::trunc(h) - 1;
    return static_cast<double>(_data[i0]);
  }
  else
  {
    i0 = std::trunc(h) - 1;
    double xh = static_cast<double>(_data[i0]);
    double xh1 = static_cast<double>(_data[i0 + 1]);
    return xh + (h - std::floor(h)) * (xh1 - xh);
  }
}

}