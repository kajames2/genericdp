#include "dp_result.h"
#include "single_vector_dp_storage.h"
#include "simple_storage.h"
#include "simple_dp_state.h"

#include <gtest/gtest.h>
#include <memory>
#include <iostream>

class SingleVectorDPStorageTest : public ::testing::Test {
 public:
  SingleVectorDPStorageTest() {}
 protected:
  virtual void SetUp() {
    storage_ = std::make_unique<genericdptest::SimpleStorage>(5, 5);
    state_.cash = 3;
    state_.period = 2;

    state2_.probability = 1;
    state2_.cash = 3;
    state2_.period = 2;
    state2_.immediate_value = 1;
    state2_.value = 2;
    state2_.investment = 5;
    res_.AddState(state2_);
  }

  std::unique_ptr<genericdptest::SimpleStorage> storage_;
  genericdptest::SimpleDPState state_, state2_;
  genericdp::DPResult<genericdptest::SimpleDPState> res_;
};

TEST_F(SingleVectorDPStorageTest, IsStoredStateTest) {
  ASSERT_FALSE(storage_->IsStoredState(state_));
  storage_->StoreOptimalResult(state_, res_);
  ASSERT_TRUE(storage_->IsStoredState(state_));
  ASSERT_TRUE(storage_->IsStoredState(state2_));
}

TEST_F(SingleVectorDPStorageTest, GetStoredStateTest) {
  storage_->StoreOptimalResult(state_, res_);
  auto stored_res = storage_->GetOptimalResult(state_);
  ASSERT_DOUBLE_EQ(2, stored_res.GetValue());
}
