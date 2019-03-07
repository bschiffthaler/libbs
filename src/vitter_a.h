#pragma once

#include <cstdint>

namespace BS {

/**
* @brief Vitter's  algorithm A for sequential random sampling.
* 
* This class implements algorithm A from Vitter (1984): "Faster methods for
* random sampling".
* @cite Vitter1984
*/
class vitter_a {
public:
  /**
  * @brief Empty constructor.
  */
  vitter_a(){}
  /**
  * @brief Basic constructor.
  *
  * This will instantiate the class for population size N and sample size n. The
  * sample size n has to be less than the population N.
  * @param N The size of the population
  * @param n The sample size
  */
  vitter_a(uint64_t N, uint64_t n);
  /**
  * @brief Get next sample.
  *
  * This method yields the sequentially next record to sample. This is a 0 based
  * index.
  * @return A 0-based index of the next record to sample.
  */
  uint64_t next();
  /**
  * @brief Check if all samples have been retrieved.
  *
  * This method will return `true` if all samples as defined by constructor
  * parameter `n` have been generated. 
  * @return `true` if all samples have been generated, `false` otherwise
  */
  bool end() {return _n == 0;}
  friend class vitter_d;
private:
  // Functions
  uint64_t gen_skip();
  // Data
  uint64_t _N;
  uint64_t _S;
  uint64_t _current;
  uint64_t _n;
  uint64_t _top;
};

} // Namespace BS