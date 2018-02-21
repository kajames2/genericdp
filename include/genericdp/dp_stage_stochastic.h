#ifndef _GENERICDP_STAGE_STOCHASTIC_H_
#define _GENERICDP_STAGE_STOCHASTIC_H_

#include <memory>
#include <utility>

#include "genericdp/dp_result.h"
#include "genericdp/dp_state.h"
#include "genericdp/dp_state_iterator_factory.h"
#include "genericdp/stage.h"

namespace genericdp {

template <typename T>
class StageStochastic : public Stage<T> {
 public:
  explicit StageStochastic(std::unique_ptr<DPStateIteratorFactory<T>> fact_);
  DPResult<T> Evaluate(DPState<T> *state) override;

 private:
  std::unique_ptr<DPStateIteratorFactory<T>> fact_;
};

template <typename T>
StageStochastic<T>::StageStochastic(
    std::unique_ptr<DPStateIteratorFactory<T>> fact)
    : Stage<T>(nullptr), fact_(std::move(fact)) {}

template <typename T>
DPResult<T> StageStochastic<T>::Evaluate(DPState<T> *state) {
  auto it_ptr = fact_->GetIterator(*state);
  DPStateIterator<T> &it_ref = *it_ptr;
  std::unique_ptr<DPResult<T>> out = std::make_unique<DPResult<T>>();
  do {
    if (it_ref->probability > 0) {
      out->AddResult((this->ProcessNext(&(*it_ref))).get());
    }
  } while (++it_ref);
  return out;
}

}  // namespace genericdp
#endif  // _GENERICDP_STAGE_STOCHASTIC_H_
