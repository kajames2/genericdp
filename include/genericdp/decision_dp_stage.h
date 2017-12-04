#ifndef _DECISION_DP_STAGE_H_
#define _DECISION_DP_STAGE_H_

#include "dp_state_iterator.h"
#include "dp_state_iterator_factory.h"
#include "dp_result.h"
#include "dp_stage.h"

#include <memory>

namespace genericdp {

template <typename T> class DecisionDPStage : public DPStage<T> {
public:
  DecisionDPStage(std::unique_ptr<DPStateIteratorFactory<T>> fact);
  virtual std::unique_ptr<DPResult<T>> Evaluate(T *state) override;

protected:
  std::unique_ptr<DPStateIteratorFactory<T>> fact_;
};

template <typename T>
DecisionDPStage<T>::DecisionDPStage(
    std::unique_ptr<DPStateIteratorFactory<T>> fact)
    : DPStage<T>(nullptr), fact_(std::move(fact)) {}

template <typename T>
std::unique_ptr<DPResult<T>> DecisionDPStage<T>::Evaluate(T *state) {
  auto it_ptr = fact_->GetIterator(*state);
  DPStateIterator<T> &it_ref = *it_ptr;
  std::unique_ptr<DPResult<T>> opt_out = nullptr;
  do {
    auto cur_out = this->ProcessNext(&(*it_ref));
    if (!opt_out || cur_out->GetValue() > opt_out->GetValue()) {
      opt_out = std::move(cur_out);
    }
  } while (++it_ref);
  return opt_out;
}

} // namespace genericdp
#endif // _DECISION_DP_STAGE_H_
