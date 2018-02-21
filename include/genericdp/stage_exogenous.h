#ifndef _GENERICDP_STAGE_EXOGENOUS_H_
#define _GENERICDP_STAGE_EXOGENOUS_H_

#include <memory>
#include <utility>

#include "genericdp/dp_result.h"
#include "genericdp/modify_strategy.h"
#include "genericdp/stage.h"

namespace genericdp {

template <typename T>
class StageExogenous : public Stage<T> {
 public:
  explicit StageExogenous(std::shared_ptr<ModifyStrategy<T>> mod_strat);
  DPResult<T> Evaluate(DPState<T> *state) override;

 protected:
  std::shared_ptr<ModifyStrategy<T>> mod_strat_;
};

template <typename T>
StageExogenous<T>::StageExogenous(std::shared_ptr<ModifyStrategy<T>> mod_strat)
    : Stage<T>(nullptr), mod_strat_(mod_strat) {}

template <typename T>
DPResult<T> StageExogenous<T>::Evaluate(DPState<T> *state) {
  mod_strat_->Modify(state);
  return this->ProcessNext(state);
}

}  // namespace genericdp
#endif  // _GENERICDP_STAGE_EXOGENOUS_H_
