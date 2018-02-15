#ifndef _STAGE_EXOGENOUS_H_
#define _STAGE_EXOGENOUS_H_

#include "dp_result.h"
#include "stage.h"
#include "modify_strategy.h"

#include <memory>

namespace genericdp {

template <typename T> class StageExogenous : public Stage<T> {
public:
  StageExogenous(std::shared_ptr<ModifyStrategy<T>> mod_strat);
  virtual DPResult<T> Evaluate(DPState<T> *state) override;

protected:
  std::shared_ptr<ModifyStrategy<T>> mod_strat_;
};

template <typename T>
StageExogenous<T>::StageExogenous(
    std::shared_ptr<ModifyStrategy<T>> mod_strat)
    : Stage<T>(nullptr), mod_strat_(mod_strat) {}

template <typename T>
DPResult<T> StageExogenous<T>::Evaluate(DPState<T> *state) {
  mod_strat_->Modify(state);
  return this->ProcessNext(state);
}

} // namespace genericdp
#endif // _STAGE_EXOGENOUS_H_
