#ifndef _GENERICDP_DP_STATE_ITERATOR_FACTORY_H_
#define _GENERICDP_DP_STATE_ITERATOR_FACTORY_H_

#include <memory>

#include "genericdp/dp_state.h"
#include "genericdp/dp_state_iterator.h"

namespace genericdp {
template <class T>
class DPStateIteratorFactory {
 public:
  virtual std::unique_ptr<DPStateIterator<T>> GetIterator(
      const DPState<T>& input) const = 0;
  DPStateIteratorFactory() = default;
  DPStateIteratorFactory(const DPStateIteratorFactory&) = delete;
  DPStateIteratorFactory& operator=(const DPStateIteratorFactory&) = delete;
  virtual ~DPStateIteratorFactory() {}
};
}  // namespace genericdp
#endif  // _GENERICDP_DP_STATE_ITERATOR_FACTORY_H_
