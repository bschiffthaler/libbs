#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "common.h"
#include "describe.h"

namespace BS {
desc_stats::desc_stats() : _max(-std::numeric_limits<double>::infinity()),
  _min(std::numeric_limits<double>::infinity()), _sorted(false), _sum(0) {}

desc_stats::desc_stats(std::vector<double>& data, bool sorted) :
  _max(-std::numeric_limits<double>::infinity()),
  _min(std::numeric_limits<double>::infinity()), _sorted(false), _sum(0)
{
  if (data.size() == 0)
  {
    throw std::runtime_error("[BS::desc_stats::desc_stats] Data vector length 0");
  }
  if (sorted)
  {
    for (double& d : data)
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
    for (double& d : data)
    {
      _data.push_back(d);
    }
    _update();
  }
}

void desc_stats::_update()
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

void desc_stats::add(double data)
{
  _data.push_back(data);
  if (_sorted)
  {
    _sorted = false;
  }
}

double desc_stats::quantile(const double q)
{
  if (q < 0 || q > 1)
  {
    throw std::runtime_error("[BS::desc_stats::quantile]\t Probability must be"
                             "between 0 and 1");
  }
  _update();
  // Some value sanity in extremities
  if (almost_eq(q, 0))
  {
    return _data[0];
  }
  if (almost_eq(q, 1))
  {
    return _data[_data.size() - 1];
  }
  // Get index of probablities
  double prob = q * static_cast<double>(_data.size());
  uint64_t index;
  if (q < 0)
  {
    index = 0;
  }
  else
  {
    index = static_cast<uint64_t>(prob);
    if (index > _data.size())
    {
      index = _data.size();
    }
  }
  return _data[index];
}

} // namespace BS