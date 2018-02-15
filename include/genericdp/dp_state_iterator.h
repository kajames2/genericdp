#ifndef _DP_STATE_ITERATOR_H_
#define _DP_STATE_ITERATOR_H_

#include "dp_state.h"

#include <iterator>
#include <memory>

namespace genericdp {
template <class T>
class DPStateIterator : public std::iterator<std::forward_iterator_tag, T> {
public:
  using reference = DPState<T> &;
  using pointer = DPState<T> *;

  DPStateIterator() : done_(false) {}

  explicit operator bool() const { return !done_; }
  reference operator*() { return state_; }
  pointer operator->() { return &state_; }

  virtual DPStateIterator<T> &operator++() {
    if (!done_) {
      this->NextTemplate();
      SetState();
      this->NextState();
    }
    return *this;
  }

  DPStateIterator<T> operator++(int) {
    DPStateIterator<T> ret = *this;
    this->operator++();
    return ret;
  }

  DPStateIterator(const DPStateIterator &) = delete;
  DPStateIterator &operator=(const DPStateIterator &) = delete;
  virtual ~DPStateIterator() {}

protected:
  DPStateIterator(const DPState<T> &state)
      : state_(state), template_state_(state), done_(false) {
    SetState();
  }
  virtual void NextTemplate() {}
  virtual void NextState() {}
  void SetState() { state_ = template_state_; }
  bool done_;
  DPState<T> state_;
  DPState<T> template_state_;
};
} // namespace genericdp
#endif // _DP_STATE_ITERATOR_H_
