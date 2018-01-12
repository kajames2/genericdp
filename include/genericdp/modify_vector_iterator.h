#ifndef _MODIFY_VECTOR_ITERATOR_H_
#define _MODIFY_VECTOR_ITERATOR_H_

#include "dp_state_iterator.h"
#include "modify_strategy_set.h"
#include <memory>
#include <vector>

namespace genericdp {
template <class T> class ModifyVectorIterator : public DPStateIterator<T> {
public:
  ModifyVectorIterator(const T &state, const ModifyStrategySet<T> &set)
      : DPStateIterator<T>(state), it_(set.begin()), end_(set.end()) {
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
  typename ModifyStrategySet<T>::const_iterator it_, end_;
};
} // namespace genericdp
#endif // _MODIFY_VECTOR_ITERATOR_H_
