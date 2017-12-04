#ifndef _DP_TEMPLATE_H_
#define _DP_TEMPLATE_H_

#include "dp_stage.h"
#include "dp_storage.h"
#include "state_iterator.h"
#include "dp_result.h"
#include "value_strategy.h"

#include <exception>
#include <memory>
#include <vector>
#include <iostream>

namespace genericdp {
template <typename T> class DPTemplate {
public:
  DPTemplate(std::unique_ptr<DPStorage<T>> storage,
             std::vector<std::unique_ptr<DPStage<T>>> stages,
             std::shared_ptr<ValueStrategy<T>> calculator)
      : storage_(std::move(storage))
      , calculator_(calculator) {
    InitStages(std::move(stages));
  }

  const DPResult<T>& GetOptimalResult(const T &init_state);
  double GetOptimalValue(const T &init_state);
  void BottomUpTrain(StateIterator<T> &state_iterator);
  void TrainIfNecessary(const T &state);

protected:
  std::unique_ptr<const DPResult<T>> CalculateOptimal(const T &state);
  void InitStages(std::vector<std::unique_ptr<DPStage<T>>> stages);
  std::unique_ptr<DPStorage<T>> storage_;
  std::unique_ptr<DPStage<T>> stage_stack_;
  std::shared_ptr<ValueStrategy<T>> calculator_;

 private:
  class DPEndStage : public DPStage<T> {
   public:
    DPEndStage(DPTemplate* dp) : DPStage<T>(nullptr), dp_(dp) {}
    virtual std::unique_ptr<DPResult<T>> Evaluate(T *state) override {
      state->future_value = dp_->GetOptimalValue(*state);
      state->value = dp_->calculator_->CalculateValue(state->immediate_value, state->future_value);
      return std::make_unique<DPResult<T>>(*state);
    }
   private:
    DPTemplate* dp_;
  };
};

template <typename T>
void DPTemplate<T>::InitStages(std::vector<std::unique_ptr<DPStage<T>>> stages) {
  stage_stack_ = std::make_unique<DPEndStage>(this);
  for (auto it = stages.rbegin(); it != stages.rend(); ++it) {
    (*it)->SetNextStage(std::move(stage_stack_));
    stage_stack_ = std::move(*it);
  }
}

template <typename T>
void DPTemplate<T>::BottomUpTrain(StateIterator<T> &state_iterator) {
  do {
    Train(*state_iterator);
  } while (++state_iterator);
}

template <typename T>
const DPResult<T>& DPTemplate<T>::GetOptimalResult(const T &state) {
  TrainIfNecessary(state);
  return storage_->GetOptimalResult(state);
}

template <typename T>
double DPTemplate<T>::GetOptimalValue(const T &state) {
  if (storage_->IsTerminalState(state)) {
    return calculator_->CalculateTerminalValue(state);
  }
  TrainIfNecessary(state);
  return storage_->GetOptimalValue(state);
}

template <typename T>
void DPTemplate<T>::TrainIfNecessary(const T &state) {
  if (!storage_->IsStoredState(state)) {
    storage_->StoreOptimalResult(state, *(CalculateOptimal(state)));
  }
}

template <typename T>
std::unique_ptr<const DPResult<T>> DPTemplate<T>::CalculateOptimal(const T &state) {
  auto temp = std::make_unique<T>(state);
  temp->Reset();
  auto res = stage_stack_->Evaluate(temp.get());
  return std::move(res);
}

} // namespace genericdp
#endif // _DP_TEMPLATE_H_
