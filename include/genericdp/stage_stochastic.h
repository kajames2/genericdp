#ifndef _GENERICDP_STAGE_STOCHASTIC_H_
#define _GENERICDP_STAGE_STOCHASTIC_H_

#include <memory>

#include "genericdp/dp_result.h"
#include "genericdp/dp_state.h"
#include "genericdp/dp_state_iterator_factory.h"
#include "genericdp/stage.h"

namespace genericdp {

template <typename T>
class StageStochastic : public Stage<T> {
 public:
  StageStochastic(std::unique_ptr<DPStateIteratorFactory<T>> fact_);
  virtual DPResult<T> Evaluate(DPState<T> *state) override;

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
  DPResult<T> out;
  do {
    if (it_ref->probability > 0) {
      auto &&res = this->ProcessNext(&(*it_ref));
      out.AddResult(&res);
    }
  } while (++it_ref);
  return out;
}

}  // namespace genericdp
#endif  // _GENERICDP_STAGE_STOCHASTIC_H_
