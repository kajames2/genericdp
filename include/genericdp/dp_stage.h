#ifndef _DP_STAGE_H_
#define _DP_STAGE_H_

#include "dp_result.h"

#include <memory>

namespace genericdp {

template <typename T> class DPStage {
public:
  DPStage(std::unique_ptr<DPStage> next_stage);
  void SetNextStage(std::unique_ptr<DPStage> next_stage) {
    next_stage_ = std::move(next_stage);
  }
  virtual std::unique_ptr<DPResult<T>> Evaluate(T *state) = 0;

protected:
  std::unique_ptr<DPResult<T>> ProcessNext(T *state);

private:
  std::unique_ptr<DPStage> next_stage_;
};

template <typename T>
DPStage<T>::DPStage(std::unique_ptr<DPStage> next_stage)
    : next_stage_(std::move(next_stage)) {}

template <typename T>
std::unique_ptr<DPResult<T>> DPStage<T>::ProcessNext(T *state) {
  if (!next_stage_) {
    return std::make_unique<DPResult<T>>(*state);
  }
  return next_stage_->Evaluate(state);
};

} // namespace genericdp
#endif // _DP_STAGE_H_
