#ifndef _GENERICDP_STATE_ITERATOR_FACTORY_H_
#define _GENERICDP_STATE_ITERATOR_FACTORY_H_

#include <memory>

#include "genericdp/state.h"
#include "genericdp/state_iterator.h"

namespace genericdp {
template <typename InState, typename OutDec>
class DPStateIteratorFactory {
 public:
  virtual std::unique_ptr<StateIterator<InState, OutDec>> GetIterator(
      const State<InState, OutDec>& input) const = 0;
  DPStateIteratorFactory() = default;
  DPStateIteratorFactory(const DPStateIteratorFactory&) = delete;
  DPStateIteratorFactory& operator=(const DPStateIteratorFactory&) = delete;
  virtual ~DPStateIteratorFactory() {}
};
}  // namespace genericdp
#endif  // _GENERICDP_DP_STATE_ITERATOR_FACTORY_H_
