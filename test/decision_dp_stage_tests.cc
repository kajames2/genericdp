#include "decision_dp_stage.h"
#include "simple_decision_iterator_factory.h"
#include "simple_dp_state.h"

#include <gtest/gtest.h>
#include <memory>
#include <cmath>

class DecisionDPStageTest : public ::testing::Test {
 public:
  DecisionDPStageTest() : stage_(nullptr) {}

 protected:
  virtual void SetUp() {
    fact_ = std::make_unique<genericdptest::SimpleDecisionIteratorFactory>();
    stage_ = genericdp::DecisionDPStage<genericdptest::SimpleDPState>(std::move(fact_));
    state_.cash = 10;
    state_.period = 4;

    state2_.cash = 0;
    state2_.period = 1;
  }
  std::unique_ptr<genericdptest::SimpleDecisionIteratorFactory> fact_;
  genericdp::DecisionDPStage<genericdptest::SimpleDPState> stage_;
  genericdptest::SimpleDPState state_, state2_;
};

TEST_F(DecisionDPStageTest, Evaluate) {
  auto res = stage_.Evaluate(&state_);
  ASSERT_DOUBLE_EQ(res->GetValue(), 25);
  ASSERT_EQ(5, (*res)[0].investment);
}

TEST_F(DecisionDPStageTest, EvaluateOneDecision) {
  auto res = stage_.Evaluate(&state2_);
  ASSERT_DOUBLE_EQ(res->GetValue(), 0);
  ASSERT_EQ(0, (*res)[0].investment);
}
