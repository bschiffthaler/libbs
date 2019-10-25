#include <random>
#include "aux.h"

namespace BS {

static std::random_device global_rd;
static std::mt19937 global_mt(global_rd());
static std::uniform_real_distribution<> global_open_unit_dis(LB(), UB());

double global_uniform_unit_db()
{
  return global_open_unit_dis(global_mt);
}

double local_uniform_unit_db()
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<> dis(LB(), UB());
  return dis(mt);
}

}