#ifndef _EXOGENOUS_DP_STAGE_H_
#define _EXOGENOUS_DP_STAGE_H_

#include "dp_result.h"
#include "dp_stage.h"
#include "modify_strategy.h"

#include <memory>

namespace genericdp {

template <typename T> class ExogenousDPStage : public DPStage<T> {
public:
  ExogenousDPStage(std::shared_ptr<ModifyStrategy<T>> mod_strat);
  virtual std::unique_ptr<DPResult<T>> Evaluate(T *state) override;

protected:
  std::shared_ptr<ModifyStrategy<T>> mod_strat_;
};

template <typename T>
ExogenousDPStage<T>::ExogenousDPStage(
    std::shared_ptr<ModifyStrategy<T>> mod_strat)
    : DPStage<T>(nullptr), mod_strat_(mod_strat) {}

template <typename T>
std::unique_ptr<DPResult<T>> ExogenousDPStage<T>::Evaluate(T *state) {
  mod_strat_->Modify(state);
  return this->ProcessNext(state);
}

} // namespace genericdp
#endif // _EXOGENOUS_DP_STAGE_H_
