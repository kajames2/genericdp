#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "genericdp/dp_result.h"
#include "test/simple_state.h"
#include "test/simple_storage.h"

class DPStorageSingleVectorTest : public ::testing::Test {
 public:
  DPStorageSingleVectorTest() {}

 protected:
  virtual void SetUp() {
    storage_ = std::make_unique<genericdptest::SimpleStorage>(5, 5);
    state_.cash = 3;
    state_.period = 2;
    state2_.cash = 3;
    state2_.period = 2;

    dp_state_.domain = state_;
    dp_state_.probability = 1;
    dp_state_.immediate_value = 1;
    dp_state_.value = 2;
    dp_state_.domain.investment = 5;
    res_.AddState(&dp_state_);
  }

  std::unique_ptr<genericdptest::SimpleStorage> storage_;
  genericdp::DPState<genericdptest::SimpleState> dp_state_;
  genericdptest::SimpleState state_, state2_;
  genericdp::DPResult<genericdptest::SimpleState> res_;
};

TEST_F(DPStorageSingleVectorTest, IsStoredStateTest) {
  ASSERT_FALSE(storage_->IsStoredState(state_));
  storage_->StoreOptimalResult(state_, res_);
  ASSERT_TRUE(storage_->IsStoredState(state_));
  ASSERT_TRUE(storage_->IsStoredState(state2_));
}

TEST_F(DPStorageSingleVectorTest, GetStoredStateTest) {
  storage_->StoreOptimalResult(state_, res_);
  auto stored_res = storage_->GetOptimalResult(state_);
  ASSERT_DOUBLE_EQ(2, stored_res.GetValue());
}
