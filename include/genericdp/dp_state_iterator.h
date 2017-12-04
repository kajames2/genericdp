#ifndef _DP_STATE_ITERATOR_H_
#define _DP_STATE_ITERATOR_H_

#include <iterator>
#include <memory>

namespace genericdp {
template <class T>
class DPStateIterator : public std::iterator<std::forward_iterator_tag, T> {
public:
  using reference = T &;
  using pointer = T *;

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
  DPStateIterator(const T &state)
      : state_(state), template_state_(state), done_(false) {
    SetState();
  }
  virtual void NextTemplate() {}
  virtual void NextState() {}
  void SetState() { state_ = template_state_; }
  bool done_;
  T state_;
  T template_state_;
};
} // namespace genericdp
#endif // _DP_STATE_ITERATOR_H_
