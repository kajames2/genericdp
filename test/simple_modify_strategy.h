#ifndef _SIMPLE_MODIFY_STRATEGY_H_
#define _SIMPLE_MODIFY_STRATEGY_H_

#include "genericdp/dp_state.h"
#include "genericdp/modify_strategy.h"
#include "simple_state.h"

namespace genericdptest {

class SimpleModifyStrategy : public genericdp::ModifyStrategy<SimpleState> {
 public:
  virtual void Modify(genericdp::DPState<SimpleState>* state) const override;
};

}  // namespace genericdptest

#endif  // _SIMPLE_MODIFY_STRATEGY_H_
