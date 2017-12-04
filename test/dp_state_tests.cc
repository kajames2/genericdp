#include "simple_dp_state.h"

#include <gtest/gtest.h>
#include <memory>

class DPStateTest : public ::testing::Test {
 public:
  DPStateTest() {}
};

TEST_F(DPStateTest, DefaultProb1) {
  genericdptest::SimpleDPState state;
  ASSERT_DOUBLE_EQ(state.probability, 1);
}
