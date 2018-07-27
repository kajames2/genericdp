#ifndef _GENERICDP_STAGE_STOCHASTIC_H_
#define _GENERICDP_STAGE_STOCHASTIC_H_

#include <memory>
#include <utility>

#include "genericdp/dp_state_iterator_factory.h"
#include "genericdp/result.h"
#include "genericdp/stage.h"
#include "genericdp/state.h"

namespace genericdp {
namespace stage {

template <typename InState, typename OutDec>
class Stochastic : public Stage<InState, OutDec> {
 public:
  explicit Stochastic(
      std::unique_ptr<StateIteratorFactory<InState, OutDec>> fact_);
  ResultSet<OutDec> Evaluate(State<InState, OutDec>& state) override;

 private:
  std::unique_ptr<StateIteratorFactory<InState, OutDec>> fact_;
};

template <typename InState, typename OutDec>
Stochastic<InState, OutDec>::StageStochastic(
    std::unique_ptr<StateIteratorFactory<InState, OutDec>> fact)
    : Stage<InState, OutDec>(nullptr), fact_(std::move(fact)) {}

template <typename InState, typename OutDec>
ResultSet<OutDec> Stochastic<InState, OutDec>::Evaluate(
    State<InState, OutDec>& state) {
  auto it_ptr = fact_->GetIterator(*state);
  StateIterator<InState, OutDec>& it_ref = *it_ptr;
  ResultSet<OutDec> out;
  do {
    if (it_ref->valuation.probability > 0) {
      auto res = this->ProcessNext(it_ref);
      out.AddResultSet(res);
    }
  } while (++it_ref);
  return out;
}

}  // namespace stage
}  // namespace genericdp
#endif  // _GENERICDP_STAGE_STOCHASTIC_H_
