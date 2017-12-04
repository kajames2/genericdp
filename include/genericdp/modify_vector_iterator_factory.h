#ifndef _MODIFY_VECTOR_ITERATOR_FACTORY_H_
#define _MODIFY_VECTOR_ITERATOR_FACTORY_H_

#include "dp_state_iterator_factory.h"
#include "modify_vector_iterator.h"
#include "modify_strategy.h"

#include <memory>
#include <vector>

namespace genericdp {
template <class T> class ModifyVectorIteratorFactory : public DPStateIteratorFactory<T> {
public:
  virtual std::unique_ptr<DPStateIterator<T>> GetIterator(const T& input) const {
    return std::make_unique<ModifyVectorIterator<T>>(input, mods_);
  };
  ModifyVectorIteratorFactory(std::vector<std::shared_ptr<ModifyStrategy<T>>> mods) : mods_(mods) {}
  
 private:
  std::vector<std::shared_ptr<ModifyStrategy<T>>> mods_;
};
} // namespace genericdp
#endif // _MODIFY_VECTOR_ITERATOR_FACTORY_H_
