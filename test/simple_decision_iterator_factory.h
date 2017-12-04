#ifndef _SIMPLE_DECISION_ITERATOR_FACTORY_H_
#define _SIMPLE_DECISION_ITERATOR_FACTORY_H_

#include "dp_state_iterator_factory.h"
#include "simple_decision_iterator.h"

#include <memory>

namespace genericdptest {
class SimpleDecisionIteratorFactory
    : public genericdp::DPStateIteratorFactory<SimpleDPState> {
public:
  SimpleDecisionIteratorFactory() {}
  virtual std::unique_ptr<genericdp::DPStateIterator<SimpleDPState>>
  GetIterator(const SimpleDPState &input) const override {
    return std::make_unique<SimpleDecisionIterator>(input);
  }
};
} // namespace genericdptest
#endif // _SIMPLE_DECISION_ITERATOR_FACTORY_H_
