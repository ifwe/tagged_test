#include <test/kit.h>

//Trivial unit test example.
FIXTURE(Typical) {
  int x = 1;
  int y = 2;
  int z = 3;


  EXPECT_TRUE(x);
  EXPECT_EQ(x + y, z);
  EXPECT_FALSE(x > z);
}
