#include <histogram.h>
#include <common.h>
#include <stdexcept>
#include <limits>

namespace BS {

histogram::histogram(const double min, const double max, const uint32_t bins) :
_bins(bins), _max(max), _min(min)
{
  _counts.resize(_bins, 0);
  _create_breaks();
}

histogram::histogram(const std::vector<double>& data, const double min,
                     const double max, const uint32_t bins) :
_bins(bins), _max(max), _min(min)
{
  _counts.resize(_bins, 0);
  _create_breaks();
  for (auto& x : data)
    add(x);
}

histogram::histogram(const std::vector<double>& data, const uint32_t bins,
                     const bool sorted) :
_bins(bins), _max(- std::numeric_limits<double>::infinity()), 
_min(std::numeric_limits<double>::infinity())
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
}

void histogram::_create_breaks() 
{
  double diff = _max - _min;
  _breaks.push_back(_min);
  double nbins = static_cast<double>(_bins);
  double step = diff / nbins;
  for (uint32_t i = 1; i < _bins; i++) 
  {
    double di = static_cast<double>(i);
    _breaks.push_back(_min + step * di);
  }
}

uint32_t histogram::_bin(const double& x)
{
  auto ptr = std::lower_bound(_breaks.begin(), _breaks.end(), x, almost_lt_eq);
  uint32_t ind = std::distance(_breaks.begin(), ptr) - 1;
  return std::min(ind, _bins - 1);
}

void histogram::add(const double& x)
{
  if (! almost_lt_eq(x, _max))
    throw std::runtime_error("[BS::histogram::add] Trying to add value "
                             "greater than max in the histogram");
  if (! almost_gt_eq(x, _min))
    throw std::runtime_error("[BS::histogram::add] Trying to add value "
                             "less than min in the histogram");
  _counts[_bin(x)]++;
}

void histogram::unsafe_add(const double& x)
{
  _counts[_bin(x)]++;
}
} // namespace BS