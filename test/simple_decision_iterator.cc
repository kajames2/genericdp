#include "simple_decision_iterator.h"

namespace genericdptest {

SimpleDecisionIterator::SimpleDecisionIterator(const genericdp::DPState<SimpleState> &state)
    : genericdp::DPStateIterator<SimpleState>(state) {
  template_state_.domain.investment = 0;
  state_ = template_state_;
}

void SimpleDecisionIterator::NextTemplate() {
  template_state_.domain.investment++;
  template_state_.domain.cash--;
  template_state_.value = 10 * template_state_.domain.investment - (template_state_.domain.investment * template_state_.domain.investment); 
  if (template_state_.domain.cash < 0) {
    done_ = true;
  }
}
} // namespace genericdptests
