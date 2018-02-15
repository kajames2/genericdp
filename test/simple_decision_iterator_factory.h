#ifndef _SIMPLE_DECISION_ITERATOR_FACTORY_H_
#define _SIMPLE_DECISION_ITERATOR_FACTORY_H_

#include "dp_state_iterator_factory.h"
#include "simple_decision_iterator.h"
#include "dp_state.h"

#include <memory>

namespace genericdptest {
class SimpleDecisionIteratorFactory
    : public genericdp::DPStateIteratorFactory<SimpleState> {
public:
  SimpleDecisionIteratorFactory() {}
  virtual std::unique_ptr<genericdp::DPStateIterator<SimpleState>>
  GetIterator(const genericdp::DPState<SimpleState> &input) const override {
    return std::make_unique<SimpleDecisionIterator>(input);
  }
};
} // namespace genericdptest
#endif // _SIMPLE_DECISION_ITERATOR_FACTORY_H_
