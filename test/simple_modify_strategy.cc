#include "simple_modify_strategy.h"

#include <cmath>

namespace genericdptest {
void SimpleModifyStrategy::Modify(SimpleDPState *state) const {
  state->immediate_value = 1 - std::exp(-state->investment * 1.0);
  state->period += 1;
}

} // namespace genericdptest
