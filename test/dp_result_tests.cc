#include "simple_state.h"
#include "dp_result.h"

#include <gtest/gtest.h>
#include <memory>

class DPResultTest : public ::testing::Test {
 public:
  DPResultTest() {}

 protected:
  virtual void SetUp() {
    state1_.probability = 0.4;
    state1_.value = 20;
    state1_.immediate_value = 10;
    state1_.future_value = 5;

    state2_.probability = 0.6;
    state2_.value = 100;
    state2_.immediate_value = 50;
    state2_.future_value = 10;
  }
  genericdp::DPState<genericdptest::SimpleState> state1_, state2_;
};

TEST_F(DPResultTest, AddStateAggregatedValues) {
  genericdp::DPResult<genericdptest::SimpleState> res;
  res.AddState(state1_);
  res.AddState(state2_);
  ASSERT_DOUBLE_EQ(res.GetFutureValue(), 8);
  ASSERT_DOUBLE_EQ(res.GetImmediateValue(), 34);
  ASSERT_DOUBLE_EQ(res.GetValue(), 68);
  ASSERT_DOUBLE_EQ(res.GetProbability(), 1);
}

TEST_F(DPResultTest, AddStateAccessor) {
  genericdp::DPResult<genericdptest::SimpleState> res;
  res.AddState(state1_);
  res.AddState(state2_);
  ASSERT_DOUBLE_EQ(res[0].value, 20);
}

TEST_F(DPResultTest, AddStateStoredStates) {
  genericdp::DPResult<genericdptest::SimpleState> res;
  res.AddState(state1_);
  res.AddState(state2_);
  ASSERT_DOUBLE_EQ(res.GetStates()[0].value, 20);
}

TEST_F(DPResultTest, SingleStateConstructor) {
  genericdp::DPResult<genericdptest::SimpleState> res(state1_);
  ASSERT_DOUBLE_EQ(res.GetFutureValue(), 2);
  ASSERT_DOUBLE_EQ(res.GetStates()[0].value, 20);
}

TEST_F(DPResultTest, AddResultTest) {
  genericdp::DPResult<genericdptest::SimpleState> res;
  res.AddState(state1_);
  genericdp::DPResult<genericdptest::SimpleState> res2;
  res2.AddState(state2_);
  res.AddResult(res2);
  ASSERT_DOUBLE_EQ(res.GetFutureValue(), 8);
  ASSERT_DOUBLE_EQ(res.GetImmediateValue(), 34);
  ASSERT_DOUBLE_EQ(res.GetValue(), 68);
  ASSERT_DOUBLE_EQ(res.GetProbability(), 1);
}
