#ifndef _GENERICDP_STAGE_DECISION_H_
#define _GENERICDP_STAGE_DECISION_H_

#include <memory>
#include <utility>

#include "genericdp/dp_state_iterator.h"
#include "genericdp/dp_state_iterator_factory.h"
#include "genericdp/result_set.h"
#include "genericdp/stage.h"
#include "genericdp/state.h"

namespace genericdp {
namespace stage {

template <typename InState, typename OutDec>
class Decision : public Stage<InState, OutDec> {
 public:
  explicit Decision(
      std::unique_ptr<StateIteratorFactory<InState, OutDec>> fact);
  ResultSet<OutDec> Evaluate(State<InState, OutDec>& state) override;

 private:
  std::unique_ptr<StateIteratorFactory<InState, OutDec>> fact_;
};

template <typename InState, typename OutDec>
Decision<InState, OutDec>::StageOutDecision(
    std::unique_ptr<StateIteratorFactory<InState, OutDec>> fact)
    : Stage<InState, OutDec>(nullptr), fact_(std::move(fact)) {}

template <typename InState, typename OutDec>
ResultSet<OutDec> Decision<InState, OutDec>::Evaluate(
    State<InState, OutDec>& state) {
  auto it_ptr = fact_->GetIterator(state);
  StateIterator<InState, OutDec>& it_ref = *it_ptr;
  ResultSet<OutDec> opt_out;
  do {
    auto cur_out = this->ProcessNext(*it_ref);
    if (opt_out.size() == 0 || cur_out.GetValue() > opt_out.GetValue()) {
      opt_out = std::move(cur_out);
    }
  } while (++it_ref);
  return opt_out;
}

}  // namespace stage
}  // namespace genericdp
#endif  // _GENERICDP_STAGE_DECISION_H_
