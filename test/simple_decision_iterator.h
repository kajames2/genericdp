#ifndef _SIMPLE_DECISION_ITERATOR_H_
#define _SIMPLE_DECISION_ITERATOR_H_

#include "dp_state_iterator.h"
#include "simple_dp_state.h"

#include <iterator>
#include <memory>

namespace genericdptest {
class SimpleDecisionIterator
    : public genericdp::DPStateIterator<SimpleDPState> {
public:
  SimpleDecisionIterator(const SimpleDPState &state);

protected:
  virtual void NextTemplate() override;
};
} // namespace genericdptest
#endif // _SIMPLE_DECISION_ITERATOR_H_
