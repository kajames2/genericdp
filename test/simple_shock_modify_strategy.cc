#include "test/simple_shock_modify_strategy.h"

#include <algorithm>

#include "genericdp/dp_state.h"

namespace genericdptest {
SimpleShockModifyStrategy::SimpleShockModifyStrategy(int cash_shock,
                                                     double prob)
    : cash_shock_(cash_shock), prob_(prob) {}

void SimpleShockModifyStrategy::Modify(
    genericdp::DPState<SimpleState> *state) const {
  state->domain.cash = std::max(state->domain.cash + cash_shock_, 0);
  state->probability *= prob_;
}

}  // namespace genericdptest
