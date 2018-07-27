#include "genericdp/valuation.h"

#include <ostream>

namespace genericdp {

std::ostream& operator<<(std::ostream& out, const Valuation& state) {
  return out << state.probability << "," << state.immediate_value << ","
             << state.future_value << "," << state.value;
}

}  // namespace genericdp
