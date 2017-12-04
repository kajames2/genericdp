#include "simple_decision_iterator.h"

namespace genericdptest {

SimpleDecisionIterator::SimpleDecisionIterator(const SimpleDPState &state)
    : genericdp::DPStateIterator<SimpleDPState>(state) {
  template_state_.investment = 0;
}

void SimpleDecisionIterator::NextTemplate() {
  template_state_.investment++;
  template_state_.cash--;
  template_state_.value = 10 * template_state_.investment - (template_state_.investment * template_state_.investment); 
  if (template_state_.cash < 0) {
    done_ = true;
  }
}
} // namespace genericdptests
