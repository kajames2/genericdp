#include "stage_decision.h"
#include "simple_decision_iterator_factory.h"
#include "simple_state.h"

#include <gtest/gtest.h>
#include <memory>
#include <cmath>

class StageDecisionTest : public ::testing::Test {
 public:
  StageDecisionTest() : stage_(nullptr) {}

 protected:
  virtual void SetUp() {
    fact_ = std::make_unique<genericdptest::SimpleDecisionIteratorFactory>();
    stage_ = genericdp::StageDecision<genericdptest::SimpleState>(std::move(fact_));
    genericdptest::SimpleState state, state2;
    state.cash = 10;
    state.period = 4;

    state2.cash = 0;
    state2.period = 1;
    
    dp_state_.domain = state;
    dp_state2_.domain = state2;
  }
  std::unique_ptr<genericdptest::SimpleDecisionIteratorFactory> fact_;
  genericdp::StageDecision<genericdptest::SimpleState> stage_;
  genericdp::DPState<genericdptest::SimpleState> dp_state_, dp_state2_;
};

TEST_F(StageDecisionTest, Evaluate) {
  auto res = stage_.Evaluate(&dp_state_);
  ASSERT_DOUBLE_EQ(res.GetValue(), 25);
  ASSERT_EQ(5, res[0].domain.investment);
}

TEST_F(StageDecisionTest, EvaluateOneDecision) {
  auto res = stage_.Evaluate(&dp_state2_);
  ASSERT_DOUBLE_EQ(res.GetValue(), 0);
  ASSERT_EQ(0, res[0].domain.investment);
}
