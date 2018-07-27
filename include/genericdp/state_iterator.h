#ifndef _GENERICDP_STATE_ITERATOR_H_
#define _GENERICDP_STATE_ITERATOR_H_

#include <iterator>
#include <memory>

#include "genericdp/state.h"

namespace genericdp {
template <typename InState, typename OutDec>
class StateIterator
    : public std::iterator<std::forward_iterator_tag, State<InState, OutDec>> {
 public:
  virtual explicit operator bool() const;
  virtual State<InState, OutDec>& operator*();
  virtual State<InState, OutDec>* operator->();
  virtual StateIterator<InState, OutDec>& operator++();
  virtual StateIterator<InState, OutDec> operator++(int);

  StateIterator(const StateIterator&) = delete;
  StateIterator& operator=(const StateIterator&) = delete;
  virtual ~StateIterator() {}
};
}  // namespace genericdp
#endif  // _GENERICDP_STATE_ITERATOR_H_
