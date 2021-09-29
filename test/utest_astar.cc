#include "gtest/gtest.h"

#include "../src/map.hpp"

namespace my {
namespace project {
namespace {

// The fixture for testing class Astar.
class AstarTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  AstarTest() {
     // You can do set-up work for each test here.
  }

  ~AstarTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that Map::Map() correctly creates a map.
TEST_F(AstarTest, MapCreatesAMap) {
	astar::Map map{"../test/test_map_1.csv", 20};

  	EXPECT_EQ(map.getWidth(), 4);
  	EXPECT_EQ(map.getWidth(), 9);
}

// Tests that Foo does Xyz.
TEST_F(AstarTest, DoesXyz) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace
}  // namespace project
}  // namespace my
