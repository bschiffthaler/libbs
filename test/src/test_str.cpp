#include <string>
#include <iostream>
#include "../../src/str_manip.h"

int main(int argc, char const ** argv)
{
  std::string chandrian("Cyphus bears the blue flame. "
                        "Stercus is in thrall of iron. "
                        "Ferule chill and dark of eye. "
                        "Usnea lives in nothing but decay. "
                        "Grey Dalcenti never speaks. "
                        "Pale Alenta brings the blight. "
                        "Last there is the lord of seven: "
                        "Hated. Hopeless. Sleepless. Sane. "
                        "Alaxel bears the         shadow's      hame.");

  if (BS::str_startswith(chandrian, "Kvothe"))
  {
    return __LINE__;
  }

  if (! BS::str_startswith(chandrian, "Cyphus"))
  {
    return __LINE__;
  }

  if (BS::str_endswith(chandrian, "Denna"))
  {
    return __LINE__;
  }

  if (! BS::str_endswith(chandrian, "hame."))
  {
    return __LINE__;
  }

  std::vector<std::string> words = BS::str_split(chandrian, ' ');
  if (! (words[0] == "Cyphus") ||
      ! (words[2] == "the") ||
      ! (words[4] == "flame.") ||
      ! (words[words.size() - 1] == "hame."))
  {
    return __LINE__;
  }

  std::vector<std::string> words2 = BS::str_split_np(chandrian);
  if (! (words2[words2.size() - 2] == "shadow's"))
  {
    return __LINE__;
  }

  return 0;
}