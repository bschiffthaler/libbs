#pragma once

#define VITTER_ALPHA 0.07
#define VITTER_ALPHA_INV 14

#include <random>
#include <limits>
#include <cmath>

namespace BS {

/** 
* @brief Lower bound of the open unit interval (0, 1).
*/
constexpr double LB()
{
  return 0 + std::numeric_limits<double>::epsilon();
}

/** 
* @brief Upper bound of the open unit interval (0, 1).
*/
constexpr double UB()
{
  return 1 - std::numeric_limits<double>::epsilon();
}
/**
* @brief Generate a random double in the open unit interval using global statically
* scoped instances.
*/
double global_uniform_unit_db();

/**
* @brief Generate a random double in the open unit interval using local scoping.
*/
double local_uniform_unit_db();

/**
* @brief Helper function to cast uint64_t to double and divide
*/
double div_as_double(uint64_t numerator, uint64_t denominator);


} // Namespace BS