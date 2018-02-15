#ifndef _SIMPLE_MODIFY_STRATEGY_H_
#define _SIMPLE_MODIFY_STRATEGY_H_

#include "dp_state.h"
#include "simple_state.h"
#include "modify_strategy.h"

namespace genericdptest {

class SimpleModifyStrategy : public genericdp::ModifyStrategy<SimpleState> {
 public:
  virtual void Modify(genericdp::DPState<SimpleState>* state) const override;
};

} // namespace genericdptest

#endif // _SIMPLE_MODIFY_STRATEGY_H_
