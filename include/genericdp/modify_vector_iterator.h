#ifndef _MODIFY_VECTOR_ITERATOR_H_
#define _MODIFY_VECTOR_ITERATOR_H_

#include "dp_state_iterator.h"
#include "modify_strategy.h"

#include <memory>
#include <vector>

namespace genericdp {
template <class T> class ModifyVectorIterator : public DPStateIterator<T> {
public:
  ModifyVectorIterator(
      const T &state,
      const std::vector<std::shared_ptr<ModifyStrategy<T>>> &vec)
      : DPStateIterator<T>(state), it_(vec.begin()), end_(vec.end()) {
    if (it_ == end_) {
      this->done_ = true;
    } else {
      (*it_)->Modify(&(this->state_));
    }
  }

protected:
  virtual void NextState() override {
    if (++it_ == end_) {
      this->done_ = true;
    } else {
      (*it_)->Modify(&(this->state_));
    }
  }
  typename std::vector<std::shared_ptr<ModifyStrategy<T>>>::const_iterator it_,
      end_;
};
} // namespace genericdp
#endif // _MODIFY_VECTOR_ITERATOR_H_
