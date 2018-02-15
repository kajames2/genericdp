#include "simple_modify_strategy.h"

#include "dp_state.h"
#include <cmath>

namespace genericdptest {
void SimpleModifyStrategy::Modify(genericdp::DPState<SimpleState> *state) const {
  state->immediate_value = 1 - std::exp(-state->domain.investment * 1.0);
  state->domain.period += 1;
}

} // namespace genericdptest
