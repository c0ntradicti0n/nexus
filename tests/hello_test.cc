#include <gtest/gtest.h>
#include <bp.cpp>




TEST(Plan, BasicAssertions) {
  Spielfeld spiel = Spielfeld();
  int res = bp(spiel, 1,2,.3,4,9,10);
  EXPECT_EQ(res, 2);
}
