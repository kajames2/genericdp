#ifndef _DP_STATE_ITERATOR_FACTORY_H_
#define _DP_STATE_ITERATOR_FACTORY_H_

#include "dp_state_iterator.h"

#include <memory>

namespace genericdp {
template <class T> class DPStateIteratorFactory {
public:
  virtual std::unique_ptr<DPStateIterator<T>> GetIterator(const T& input) const = 0;
  DPStateIteratorFactory() = default;
  DPStateIteratorFactory(const DPStateIteratorFactory&) = delete;
  DPStateIteratorFactory& operator=(const DPStateIteratorFactory&) = delete;
  virtual ~DPStateIteratorFactory() {}
};
} // namespace genericdp
#endif // _DP_STATE_ITERATOR_FACTORY_H_
