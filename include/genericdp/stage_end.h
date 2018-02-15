#ifndef _STAGE_END_H_
#define _STAGE_END_H_

#include "dp.h"
#include "dp_result.h"
#include "stage.h"
#include "value_strategy.h"

namespace genericdp {

template <typename T> class DP;
template <typename T> class StageEnd : public Stage<T> {
public:
  StageEnd(DP<T> *dp, ValueStrategy<T> *calculator)
      : Stage<T>(nullptr), dp_(dp), calculator_(calculator) {}
  virtual DPResult<T> Evaluate(DPState<T> *state) override {
    state->future_value = dp_->GetOptimalValue(state->domain);
    state->value = calculator_->CalculateValue(state->immediate_value,
                                               state->future_value);
    return DPResult<T>(*state);
  }

private:
  DP<T> *dp_;
  ValueStrategy<T> *calculator_;
};
} // namespace genericdp;

#endif // _STAGE_END_H_
