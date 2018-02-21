#ifndef _GENERICDP_STAGE_H_
#define _GENERICDP_STAGE_H_

#include <memory>
#include <utility>

#include "genericdp/dp_result.h"

namespace genericdp {

template <typename T>
class Stage {
 public:
  explicit Stage(std::unique_ptr<Stage> next_stage);
  void SetNextStage(std::unique_ptr<Stage> next_stage) {
    next_stage_ = std::move(next_stage);
  }
  virtual DPResult<T> Evaluate(DPState<T> *state) = 0;
  virtual ~Stage() {}

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
    return DPResult<T>(state);
  }
  return next_stage_->Evaluate(state);
}

}  // namespace genericdp
#endif  // _GENERICDP_STAGE_H_
