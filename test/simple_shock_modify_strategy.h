#ifndef _SIMPLE_SHOCK_MODIFY_STRATEGY_H_
#define _SIMPLE_SHOCK_MODIFY_STRATEGY_H_

#include "simple_dp_state.h"
#include "modify_strategy.h"

namespace genericdptest {

class SimpleShockModifyStrategy : public genericdp::ModifyStrategy<SimpleDPState> {
 public:
  SimpleShockModifyStrategy(int cash_shock, double prob);
  virtual void Modify(SimpleDPState* state) const override;
 private:
  int cash_shock_;
  double prob_;
};

} // namespace genericdptest

#endif // _SIMPLE_MODIFY_STRATEGY_H_
