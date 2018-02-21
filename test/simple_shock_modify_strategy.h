#ifndef _SIMPLE_SHOCK_MODIFY_STRATEGY_H_
#define _SIMPLE_SHOCK_MODIFY_STRATEGY_H_

#include "genericdp/dp_state.h"
#include "genericdp/modify_strategy.h"
#include "simple_state.h"

namespace genericdptest {

class SimpleShockModifyStrategy
    : public genericdp::ModifyStrategy<SimpleState> {
 public:
  SimpleShockModifyStrategy(int cash_shock, double prob);
  virtual void Modify(genericdp::DPState<SimpleState>* state) const override;

 private:
  int cash_shock_;
  double prob_;
};

}  // namespace genericdptest

#endif  // _SIMPLE_MODIFY_STRATEGY_H_
