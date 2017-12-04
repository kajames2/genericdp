#ifndef _DP_END_STAGE_H_
#define _DP_END_STAGE_H_

#include "dp_result.h"
#include "dp_stage.h"
#include "dp_template.h"
#include "value_strategy.h"

#include <memory>

namespace genericdp {

template <typename T> class DPEndStage : public DPStage<T> {
public:
  DPEndStage(DPTemplate<T>* dp,
             std::shared_ptr<ValueStrategy<T>> calculator);
  virtual std::unique_ptr<DPResult<T>>  Evaluate(T *state) override;

private:
  DPTemplate<T>* dp_;
  std::shared_ptr<ValueStrategy<T>> calculator_;
};

template <typename T>
DPEndStage<T>::DPEndStage(
    DPTemplate<T>* dp,
    std::shared_ptr<ValueStrategy<T>> calculator)
    : dp_(dp), calculator_(calculator) {}

template <typename T>
std::unique_ptr<DPResult<T>> DPEndStage<T>::Evaluate(T *state) {
  state->future_value = dp_->GetOptimalValue(state);
  state->value = calculator_->CalculateValue(state->immediate_value, state->future_value);
  return std::make_unique<DPResult<T>>(*state);
}

} // namespace genericdp
#endif // _DP_END_STAGE_DECORATOR_H_
