#ifndef _STAGE_STOCHASTIC_H_
#define _STAGE_STOCHASTIC_H_

#include "stage.h"
#include "dp_result.h"
#include "dp_state.h"
#include "dp_state_iterator_factory.h"

#include <memory>

namespace genericdp {

template <typename T> class StageStochastic : public Stage<T> {
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
  std::unique_ptr<DPResult<T>> out = std::make_unique<DPResult<T>>();
  do{
    if(it_ref->probability > 0) {
      out->AddResult((this->ProcessNext(&(*it_ref))).get());
    }
  } while (++it_ref);
  return out;
}

} // namespace genericdp
#endif // _STAGE_STOCHASTIC_H_
