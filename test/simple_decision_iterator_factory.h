#ifndef _SIMPLE_DECISION_ITERATOR_FACTORY_H_
#define _SIMPLE_DECISION_ITERATOR_FACTORY_H_

#include <memory>

#include "genericdp/dp_state.h"
#include "genericdp/dp_state_iterator_factory.h"
#include "test/simple_decision_iterator.h"

namespace genericdptest {
class SimpleDecisionIteratorFactory
    : public genericdp::DPStateIteratorFactory<SimpleState> {
 public:
  SimpleDecisionIteratorFactory() {}
  std::unique_ptr<genericdp::DPStateIterator<SimpleState>> GetIterator(
      const genericdp::DPState<SimpleState> &input) const override {
    return std::make_unique<SimpleDecisionIterator>(input);
  }
};
}  // namespace genericdptest
#endif  // _SIMPLE_DECISION_ITERATOR_FACTORY_H_
