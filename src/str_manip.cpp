#include <string>
#include <vector>
#include "str_manip.h"

namespace BS {

bool str_startswith(std::string const & str,
                    std::string const & pattern)
{
  if (pattern.size() == 0)
  {
    return true;
  }
  if (pattern.size() > str.size())
  {
    return false;
  }
  for (uint64_t i = 0; i < pattern.size(); i++)
  {
    if (pattern[i] != str[i])
    {
      return false;
    }
  }
  return true;
}

bool str_endswith(std::string const & str,
                  std::string const & pattern)
{
  if (pattern.size() == 0)
  {
    return true;
  }
  if (pattern.size() > str.size())
  {
    return false;
  }

  for (uint64_t i = pattern.size(), j = str.size(); i > 0; i--, j--)
  {
    if (pattern[i - 1] != str[j - 1])
    {
      return false;
    }
  }
  return true;
}

std::vector<std::string> str_split(std::string const & str,
                                   char const & pattern)
{
  std::vector<std::string> ret;
  std::string word;
  for (uint64_t i = 0; i < str.size(); i++)
  {
    char const & c = str[i];
    if (c == pattern)
    {
      ret.push_back(word);
      word = std::string();
    }
    else
    {
      word += c;
    }
    if (i == (str.size() - 1))
    {
      ret.push_back(word);
    }
  }
  return ret;
}

}