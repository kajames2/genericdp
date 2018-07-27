#ifndef _GENERICDP_DP_H_
#define _GENERICDP_DP_H_

#include <exception>
#include <memory>
#include <utility>
#include <vector>

#include "genericdp/result_set.h"
#include "genericdp/stage.h"
#include "genericdp/stage/end.h"
#include "genericdp/state.h"
#include "genericdp/storage.h"
#include "genericdp/value_strategy.h"

namespace genericdp {
template <typename InState, typename OutDec>
class DP {
 public:
  DP(std::unique_ptr<Storage<InState, OutDec>> storage,
     std::vector<std::unique_ptr<Stage<T>>> stages,
     std::shared_ptr<ValueStrategy<InState>> calculator);

  const ResultSet<OutDec>& GetOptimalResult(const InState& init_state);
  double GetOptimalValue(const InState& init_state);
  void Train(const InState& state);
  void TrainIfNecessary(const InState& state);

 private:
  const Result<OutDec> CalculateOptimal(const InState& state);
  void InitStages(std::vector<std::unique_ptr<Stage<InState, OutDec>>> stages);
  std::unique_ptr<Storage<InState, OutDec>> storage_;
  std::unique_ptr<Stage<InState, OutDec>> stage_stack_;
  std::shared_ptr<ValueStrategy<InState>> calculator_;
};

template <typename InState, typename OutDec>
DP<InState, OutDec>::DP(
    std::unique_ptr<Storage<InState, OutDec>> storage,
    std::vector<std::unique_ptr<Stage<InState, OutDec>>> stages,
    std::shared_ptr<ValueStrategy<InState, OutDec>> calculator)
    : storage_(std::move(storage)), calculator_(calculator) {
  InitStages(std::move(stages));
}

template <typename InState, typename OutDec>
void DP<InState, OutDec>::InitStages(
    std::vector<std::unique_ptr<Stage<InState, OutDec>>> stages) {
  stage_stack_ =
      std::make_unique<StageEnd<InState, OutDec>>(this, calculator_.get());
  for (auto it = stages.rbegin(); it != stages.rend(); ++it) {
    (*it)->SetNextStage(std::move(stage_stack_));
    stage_stack_ = std::move(*it);
  }
}

template <typename InState, typename OutDec>
const DPResult<InState, OutDec>& DP<InState, OutDec>::GetOptimalResult(
    const InState& state) {
  TrainIfNecessary(state);
  return storage_->GetOptimalResult(state);
}

template <typename InState, typename OutDec>
double DP<InState, OutDec>::GetOptimalValue(const InState& state) {
  if (storage_->IsTerminalState(state)) {
    return calculator_->CalculateTerminalValue(state);
  }
  TrainIfNecessary(state);
  return storage_->GetOptimalValue(state);
}

template <typename InState, typename OutDec>
void DP<InState, OutDec>::TrainIfNecessary(const InState& state) {
  if (!storage_->IsStoredState(state)) {
    Train(state);
  }
}

template <typename InState, typename OutDec>
void DP<InState, OutDec>::Train(const InState& state) {
  storage_->StoreOptimalResult(state, CalculateOptimal(state));
  auto res = storage_->GetOptimalResult(state);
}

template <typename InState, typename OutDec>
const DPResult<InState, OutDec> DP<InState, OutDec>::CalculateOptimal(
    const InState& state) {
  State<InState, OutDec> temp = State<InState, OutDec>(state);
  return stage_stack_->Evaluate(&temp);
}

}  // namespace genericdp
#endif  // _GENERICDP_DP_H_
