#ifndef _STAGE_H_
#define _STAGE_H_

#include "dp_result.h"

#include <memory>

namespace genericdp {

template <typename T> class Stage {
public:
  Stage(std::unique_ptr<Stage> next_stage);
  void SetNextStage(std::unique_ptr<Stage> next_stage) {
    next_stage_ = std::move(next_stage);
  }
  virtual DPResult<T> Evaluate(DPState<T> *state) = 0;

protected:
  DPResult<T> ProcessNext(DPState<T> *state);

private:
  std::unique_ptr<Stage> next_stage_;
};

template <typename T>
Stage<T>::Stage(std::unique_ptr<Stage> next_stage)
    : next_stage_(std::move(next_stage)) {}

template <typename T>
DPResult<T> Stage<T>::ProcessNext(DPState<T> *state) {
  if (!next_stage_) {
    return DPResult<T>(*state);
  }
  return next_stage_->Evaluate(state);
};

} // namespace genericdp
#endif // _STAGE_H_
