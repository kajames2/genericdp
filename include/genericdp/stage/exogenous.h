#ifndef _GENERICDP_STAGE_EXOGENOUS_H_
#define _GENERICDP_STAGE_EXOGENOUS_H_

#include <memory>
#include <utility>

#include "genericdp/modify_strategy.h"
#include "genericdp/result.h"
#include "genericdp/stage.h"
#include "genericdp/state.h"

namespace genericdp {
namespace stage {

template <typename InState, typename OutDec>
class Exogenous : public Stage<InState, OutDec> {
 public:
  explicit Exogenous(
      std::shared_ptr<ModifyStrategy<InState, OutDec>> mod_strat);
  ResultSet<OutDec> Evaluate(State<InState, OutDec>& state) override;

 protected:
  std::shared_ptr<ModifyStrategy<InState, OutDec>> mod_strat_;
};

template <typename InState, typename OutDec>
Exogenous<InState, OutDec>::StageExogenous(
    std::shared_ptr<ModifyStrategy<InState, OutDec>> mod_strat)
    : Stage<InState, OutDec>(nullptr), mod_strat_(mod_strat) {}

template <typename InState, typename OutDec>
ResultSet<OutDec> Exogenous<InState, OutDec>::Evaluate(
    State<InState, OutDec>& state) {
  mod_strat_->Modify(state);
  return this->ProcessNext(state);
}

}  // namespace stage
}  // namespace genericdp
#endif  // _GENERICDP_STAGE_EXOGENOUS_H_
