#ifndef _SIMPLE_MODIFY_STRATEGY_H_
#define _SIMPLE_MODIFY_STRATEGY_H_

#include "simple_dp_state.h"
#include "modify_strategy.h"

namespace genericdptest {

class SimpleModifyStrategy : public genericdp::ModifyStrategy<SimpleDPState> {
 public:
  virtual void Modify(SimpleDPState* state) const override;
};

} // namespace genericdptest

#endif // _SIMPLE_MODIFY_STRATEGY_H_
