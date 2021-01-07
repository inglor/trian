#include "Functions.hh"

#include <random>

using namespace std;

namespace trian {
float Random_Float_Between(float min, float max) {
  static random_device random;
  static default_random_engine random_engine(random());
  static uniform_real_distribution<> random_distribution(min, max);
  return random_distribution(random_engine);
}
}  // namespace trian