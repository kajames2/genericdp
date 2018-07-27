#ifndef _GENERICDP_IMPL_STATE_ITERATOR_H_
#define _GENERICDP_IMPL_STATE_ITERATOR_H_

#include <iterator>
#include <memory>

#include "genericdp/state.h"
#include "genericdp/state_iterator.h"

namespace genericdp {
namespace impl {

template <typename InState, typename OutDec>
class StateIterator : public genericdp::StateIterator<InState, OutDec> {
 public:
  using reference = State<InState, OutDec>&;
  using pointer = State<InState, OutDec>*;

  StateIterator() : done_(false) {}
  operator bool() const override { return !done_; }
  reference operator*() override { return state_; }
  pointer operator->() override { return &state_; }

  StateIterator<InState, OutDec>& operator++() override;
  StateIterator<InState, OutDec> operator++(int) override;

  StateIterator(const StateIterator&) = delete;
  StateIterator& operator=(const StateIterator&) = delete;

 protected:
  explicit StateIterator(const State<InState, OutDec>& state)
      : state_(state), template_state_(state), done_(false) {}

 private:
  virtual void NextTemplate() {}
  virtual void NextState() {}
  void SetState() { state_ = template_state_; }
  bool done_;
  State<InState, OutDec> state_;
  State<InState, OutDec> template_state_;
};

template <typename InState, typename OutDec>
StateIterator<InState, OutDec>& StateIterator<InState, OutDec>::operator++() {
  if (!done_) {
    NextTemplate();
    SetState();
    NextState();
  }
  return *this;
}

template <typename InState, typename OutDec>
StateIterator<InState, OutDec> StateIterator<InState, OutDec>::operator++(int) {
  auto temp = *this;
  ++*this;
  return temp;
}

}  // namespace impl
}  // namespace genericdp
#endif  // _GENERICDP_IMPL_STATE_ITERATOR_H_
