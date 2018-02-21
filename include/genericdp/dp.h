#ifndef _GENERICDP_DP_H_
#define _GENERICDP_DP_H_

#include <exception>
#include <memory>
#include <utility>
#include <vector>

#include "genericdp/dp_result.h"
#include "genericdp/dp_state.h"
#include "genericdp/dp_storage.h"
#include "genericdp/stage.h"
#include "genericdp/stage_end.h"
#include "genericdp/value_strategy.h"

namespace genericdp {
template <typename T>
class DP {
 public:
  DP(std::unique_ptr<DPStorage<T>> storage,
     std::vector<std::unique_ptr<Stage<T>>> stages,
     std::shared_ptr<ValueStrategy<T>> calculator)
      : storage_(std::move(storage)), calculator_(calculator) {
    InitStages(std::move(stages));
  }

  const DPResult<T> &GetOptimalResult(const T &init_state);
  double GetOptimalValue(const T &init_state);
  void Train(const T &state);
  void TrainIfNecessary(const T &state);

 private:
  const DPResult<T> CalculateOptimal(const T &state);
  void InitStages(std::vector<std::unique_ptr<Stage<T>>> stages);
  std::unique_ptr<DPStorage<T>> storage_;
  std::unique_ptr<Stage<T>> stage_stack_;
  std::shared_ptr<ValueStrategy<T>> calculator_;
};

template <typename T>
void DP<T>::InitStages(std::vector<std::unique_ptr<Stage<T>>> stages) {
  stage_stack_ = std::make_unique<StageEnd<T>>(this, calculator_.get());
  for (auto it = stages.rbegin(); it != stages.rend(); ++it) {
    (*it)->SetNextStage(std::move(stage_stack_));
    stage_stack_ = std::move(*it);
  }
}

template <typename T>
const DPResult<T> &DP<T>::GetOptimalResult(const T &state) {
  TrainIfNecessary(state);
  return storage_->GetOptimalResult(state);
}

template <typename T>
double DP<T>::GetOptimalValue(const T &state) {
  if (storage_->IsTerminalState(state)) {
    return calculator_->CalculateTerminalValue(state);
  }
  TrainIfNecessary(state);
  return storage_->GetOptimalValue(state);
}

template <typename T>
void DP<T>::TrainIfNecessary(const T &state) {
  if (!storage_->IsStoredState(state)) {
    Train(state);
  }
}

template <typename T>
void DP<T>::Train(const T &state) {
  storage_->StoreOptimalResult(state, CalculateOptimal(state));
  auto res = storage_->GetOptimalResult(state);
}

template <typename T>
const DPResult<T> DP<T>::CalculateOptimal(const T &state) {
  DPState<T> temp = DPState<T>(state);
  return stage_stack_->Evaluate(&temp);
}

}  // namespace genericdp
#endif  // _GENERICDP_DP_H_
