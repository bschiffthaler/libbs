#pragma once

#include <string>
#include <vector>
/**
* Root namespace
*/
namespace BS {
/**
* @brief Test if string starts with a pattern
* 
* @param str The string to test
* @param pattern The pattern to test
* @return `true` if `str` starts with `pattern`, `false` otherwise
*/
bool str_startswith(std::string const & str,
                    std::string const & pattern);

/**
* @brief Test if string ends with a pattern
* 
* @param str The string to test
* @param pattern The pattern to test
* @return `true` if `str` starts with `pattern`, `false` otherwise
*/
bool str_endswith(std::string const & str,
                  std::string const & pattern);

/**
* @brief Split a string into a vector of substrings by a character
* 
* @param str The string to split
* @param pattern The pattern to split by
* @return A vector of strings delimited by `pattern`
*/
std::vector<std::string> str_split(std::string const & str,
                                   char const & pattern);

/**
* @brief Split a string into a vector of substrings by any non-printing
* character
* 
* @param str The string to split
* @return A vector of strings delimited by non-printing charcters
*/
std::vector<std::string> str_split_np(std::string const & str);

}