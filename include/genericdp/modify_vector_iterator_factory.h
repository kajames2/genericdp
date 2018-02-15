#ifndef _MODIFY_VECTOR_ITERATOR_FACTORY_H_
#define _MODIFY_VECTOR_ITERATOR_FACTORY_H_

#include "dp_state.h"
#include "dp_state_iterator_factory.h"
#include "modify_strategy_set.h"
#include "modify_vector_iterator.h"

#include <memory>
#include <vector>

namespace genericdp {
template <class T>
class ModifyVectorIteratorFactory : public DPStateIteratorFactory<T> {
public:
  ModifyVectorIteratorFactory(ModifyStrategySet<T> mod_set)
      : mod_set_(mod_set) {}
  virtual std::unique_ptr<DPStateIterator<T>>
  GetIterator(const DPState<T> &input) const {
    return std::make_unique<ModifyVectorIterator<T>>(input, mod_set_);
  };

private:
  ModifyStrategySet<T> mod_set_;
};
} // namespace genericdp
#endif // _MODIFY_VECTOR_ITERATOR_FACTORY_H_
