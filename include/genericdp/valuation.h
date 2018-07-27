#ifndef _GENERICDP_VALUATION_H_
#define _GENERICDP_VALUATION_H_

#include <ostream>

namespace genericdp {

class Valuation {
 public:
  float probability = 1;
  float immediate_value = 0;
  float future_value = 0;
  float value = 0;
};

std::ostream& operator<<(std::ostream& out, const Valuation& state);

}  // namespace genericdp

#endif  // _GENERICDP_VALUATION_H_
