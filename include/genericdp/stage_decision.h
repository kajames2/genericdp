#ifndef _STAGE_DECISION_H_
#define _STAGE_DECISION_H_

#include "dp_result.h"
#include "dp_state_iterator.h"
#include "dp_state_iterator_factory.h"
#include "stage.h"

#include <memory>

namespace genericdp {

template <typename T> class StageDecision : public Stage<T> {
public:
  StageDecision(std::unique_ptr<DPStateIteratorFactory<T>> fact);
  virtual DPResult<T> Evaluate(DPState<T> *state) override;

protected:
  std::unique_ptr<DPStateIteratorFactory<T>> fact_;
};

template <typename T>
StageDecision<T>::StageDecision(std::unique_ptr<DPStateIteratorFactory<T>> fact)
    : Stage<T>(nullptr), fact_(std::move(fact)) {}

template <typename T>
DPResult<T> StageDecision<T>::Evaluate(DPState<T> *state) {
  auto it_ptr = fact_->GetIterator(*state);
  DPStateIterator<T> &it_ref = *it_ptr;
  DPResult<T> opt_out;
  do {
    auto cur_out = this->ProcessNext(&(*it_ref));
    if (opt_out.GetSize() == 0 || cur_out.GetValue() > opt_out.GetValue()) {
      opt_out = std::move(cur_out);
    }
  } while (++it_ref);
  return opt_out;
}

} // namespace genericdp
#endif // _STAGE_DECISION_H_
