#ifndef _GENERICDP_STAGE_H_
#define _GENERICDP_STAGE_H_

#include <memory>
#include <utility>

#include "genericdp/result_set.h"
#include "genericdp/state.h"

namespace genericdp {

template <typename InState, typename OutDec>
class Stage {
 public:
  explicit Stage(std::unique_ptr<Stage> next_stage);
  void SetNextStage(std::unique_ptr<Stage> next_stage) {
    next_stage_ = std::move(next_stage);
  }
  virtual ResultSet<OutDec> Evaluate(State<InState, OutDec>& state) = 0;
  virtual ~Stage() {}

 protected:
  ResultSet<OutDec> ProcessNext(State<InState, OutDec>& state);

 private:
  std::unique_ptr<Stage> next_stage_;
};

template <typename InState, typename OutDec>
Stage<InState, OutDec>::Stage(std::unique_ptr<Stage> next_stage)
    : next_stage_(std::move(next_stage)) {}

template <typename InState, typename OutDec>
ResultSet<OutDec> Stage<InState, OutDec>::ProcessNext(
    State<InState, OutDec>& state) {
  if (!next_stage_) {
    return ResultSet<OutDec>();
  }
  return next_stage_->Evaluate(state);
}

}  // namespace genericdp
#endif  // _GENERICDP_STAGE_H_
