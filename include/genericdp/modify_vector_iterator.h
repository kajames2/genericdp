#ifndef _GENERICDP_MODIFY_VECTOR_ITERATOR_H_
#define _GENERICDP_MODIFY_VECTOR_ITERATOR_H_

#include <memory>
#include <vector>

#include "genericdp/dp_state.h"
#include "genericdp/dp_state_iterator.h"
#include "genericdp/modify_strategy_set.h"

namespace genericdp {
template <class T>
class ModifyVectorIterator : public DPStateIterator<T> {
 public:
  ModifyVectorIterator(const DPState<T> &state, const ModifyStrategySet<T> &set)
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
}  // namespace genericdp
#endif  // _GENERICDP_MODIFY_VECTOR_ITERATOR_H_
