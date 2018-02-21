#ifndef _SIMPLE_DECISION_ITERATOR_H_
#define _SIMPLE_DECISION_ITERATOR_H_

#include <iterator>
#include <memory>

#include "genericdp/dp_state.h"
#include "genericdp/dp_state_iterator.h"
#include "simple_state.h"

namespace genericdptest {
class SimpleDecisionIterator : public genericdp::DPStateIterator<SimpleState> {
 public:
  SimpleDecisionIterator(const genericdp::DPState<SimpleState> &state);

 protected:
  virtual void NextTemplate() override;
};
}  // namespace genericdptest
#endif  // _SIMPLE_DECISION_ITERATOR_H_
