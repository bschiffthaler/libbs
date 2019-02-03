#include <histogram.h>
#include <common.h>
#include <stdexcept>
#include <limits>
#include <string>
#include <aux.h>

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
  for (auto& x : data)
    add(x);
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
    throw std::runtime_error("[BS::histogram::add] Trying to add value " +
      std::to_string(x) + " greater than max " +
      std::to_string(_max) + " in the histogram");
  if (! almost_gt_eq(x, _min))
    throw std::runtime_error("[BS::histogram::add] Trying to add value "  +
      std::to_string(x) + " less than min " +
       std::to_string(_min) + " in the histogram");
  _counts[_bin(x)]++;
}

void histogram::unsafe_add(const double& x)
{
  _counts[_bin(x)]++;
}

void histogram::print_vertical(std::ostream& out, uint64_t width) const
{
  std::vector<std::string> axis;
  uint64_t sum_of_counts = 0;
  for (uint32_t i = 0; i < _bins; i++)
  {
    double ub = (i == (_bins - 1)) ? _max : _breaks[i + 1];
    double lb = _breaks[i];
    char rbr = (i == (_bins - 1)) ? ']' : ')';
    std::string ax;
    ax += '[';
    ax += std::to_string(lb);
    ax += std::string(", ");
    ax += std::to_string(ub);
    ax += rbr;
    axis.push_back(ax);
    sum_of_counts += _counts[i];
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
    double fraction = div_as_double(_counts[i], sum_of_counts);
    double height = static_cast<double>(width) * fraction;
    uint64_t bheight = height < 0 ? 0 : static_cast<uint64_t>(height); 

    for (uint64_t j = 0; j < bheight; j++)
    {
      out << '#';
    }
    out << ' ' << _counts[i] << '\n';
  }
}

void histogram::print_tsv(std::ostream& out) const
{
  for (uint32_t i = 0; i < _bins; i++)
  {
    double ub = (i == (_bins - 1)) ? _max : _breaks[i + 1];
    double lb = _breaks[i];
    out << lb << '\t' << ub << '\t' << _counts[i] << '\n';
  }
}

} // namespace BS