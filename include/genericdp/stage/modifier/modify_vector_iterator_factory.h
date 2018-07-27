#ifndef _GENERICDP_MODIFY_VECTOR_ITERATOR_FACTORY_H_
#define _GENERICDP_MODIFY_VECTOR_ITERATOR_FACTORY_H_

#include <memory>
#include <vector>

#include "genericdp/dp_state.h"
#include "genericdp/dp_state_iterator_factory.h"
#include "genericdp/modify_strategy_set.h"
#include "genericdp/modify_vector_iterator.h"

namespace genericdp {
template <class T>
class ModifyVectorIteratorFactory : public DPStateIteratorFactory<T> {
 public:
  explicit ModifyVectorIteratorFactory(ModifyStrategySet<T> mod_set)
      : mod_set_(mod_set) {}
  virtual std::unique_ptr<DPStateIterator<T>> GetIterator(
      const DPState<T> &input) const {
    return std::make_unique<ModifyVectorIterator<T>>(input, mod_set_);
  }

 private:
  ModifyStrategySet<T> mod_set_;
};

}  // namespace genericdp
#endif  // _GENERICDP_MODIFY_VECTOR_ITERATOR_FACTORY_H_
