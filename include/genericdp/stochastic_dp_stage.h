#ifndef _STOCHASTIC_DP_STAGE_H_
#define _STOCHASTIC_DP_STAGE_H_

#include "dp_stage.h"
#include "dp_result.h"
#include "dp_state.h"
#include "dp_state_iterator_factory.h"

#include <memory>

namespace genericdp {

template <typename T> class StochasticDPStage : public DPStage<T> {
public:
  StochasticDPStage(std::unique_ptr<DPStateIteratorFactory<T>> fact_);
  virtual std::unique_ptr<DPResult<T>> Evaluate(T *state) override;

private:
  std::unique_ptr<DPStateIteratorFactory<T>> fact_;
};

template <typename T>
StochasticDPStage<T>::StochasticDPStage(
    std::unique_ptr<DPStateIteratorFactory<T>> fact)
    : DPStage<T>(nullptr), fact_(std::move(fact)) {}

template <typename T>
std::unique_ptr<DPResult<T>> StochasticDPStage<T>::Evaluate(T *state) {
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
#endif // _STOCHASTIC_DP_STAGE_H_
