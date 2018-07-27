#ifndef _GENERICDP_STAGE_END_H_
#define _GENERICDP_STAGE_END_H_

#include "genericdp/dp.h"
#include "genericdp/result_set.h"
#include "genericdp/stage.h"
#include "genericdp/state.h"
#include "genericdp/value_strategy.h"

namespace genericdp {
namespace stage {

template <typename InState, typename OutDec>
class DP;

template <typename InState, typename OutDec>
class End : public Stage<InState, OutDec> {
 public:
  End(DP<InState, OutDec>* dp, const ValueStrategy<InState>* calculator);
  ResultSet<OutDec> Evaluate(State<InState, OutDec>& state) override;

 private:
  DP<InState, OutDec>* dp_;
  const ValueStrategy<InState>* calculator_;
};

template <typename InState, typename OutDec>
End<InState, OutDec>::StageEnd(DP<InState, OutDec>* dp,
                               const ValueStrategy<InState>* calculator)
    : Stage<InState, OutDec>(nullptr), dp_(dp), calculator_(calculator) {}

template <typename InState, typename OutDec>
ResultSet<OutDec> End<InState, OutDec>::Evaluate(
    State<InState, OutDec>& state) {
  float future_value = dp_->GetOptimalValue(domain);
  float value =
      calculator_->CalculateValue(state.immediate_value, future_value);
  return ResultSet<OutDec>(Result<OutDec>{state.probability,
                                          state.immediate_value, future_value,
                                          value, state.state});
}

}  // namespace stage
}  // namespace genericdp
#endif  // _GENERICDP_STAGE_END_H_
