#include <gtest/gtest.h>

// Fixture class for the tests
class HelloTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialization code here
    initialise_all_databases();
    zobrist::initialise_zobrist_keys();
  }

  void TearDown() override {
    // Clean-up code here if needed
  }
};

// Example test case
TEST_F(HelloTest, ExampleTest) {
  // Test code here
  // This test will have access to the initialized databases and keys
  // because the SetUp() function is called before this test runs
  EXPECT_EQ(2 + 2, 4);
}

// Run the tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
