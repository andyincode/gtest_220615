// 10_파라미터화테스트.cpp

bool IsPrime(int value)
{
  for (int i = 2; i < value; i++)
  {
    if (value % 2 == 0)
      return false;
  }

  return true;
}

#include <gtest/gtest.h>

// 데이터 검증을 위해서 제어 구문을 직접적으로 사용하고 있습니다. => 유지보수
TEST(PrimeTest, IsPrime2)
{
  int data[] = {2, 3, 5, 7, 8, 11, 13, 17, 19, 23, 37};
  for (int value : data)
  {
    EXPECT_TRUE(IsPrime(value)) << "value: " << value;
  }
}

// 데이터 중심의 테스트에서 발생하는 코드 중복의 문제가 있습니다.
TEST(PrimeTest, IsPrime)
{
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));
  EXPECT_TRUE(IsPrime(5));
  EXPECT_TRUE(IsPrime(7));
  EXPECT_TRUE(IsPrime(11));
  EXPECT_TRUE(IsPrime(13));
  EXPECT_TRUE(IsPrime(17));
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));
  EXPECT_TRUE(IsPrime(5));
  EXPECT_TRUE(IsPrime(7));
  EXPECT_TRUE(IsPrime(11));
  EXPECT_TRUE(IsPrime(13));
  EXPECT_TRUE(IsPrime(17));
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));
  EXPECT_TRUE(IsPrime(5));
  EXPECT_TRUE(IsPrime(7));
  EXPECT_TRUE(IsPrime(11));
}
