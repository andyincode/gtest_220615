// 10_파라미터화테스트2.cpp

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
// 파라미터화 테스트 패턴(Parameterized Test Pattern)
//    : xUnit Test Framework이 제공하는 기능입니다.
// 의도: 입력 데이터를 바꿔가며, 반복 검사하는 데이터 중심의 테스트에서
//      코드 중복을 제거하는 것이 가능합니다.

// 1. 테스트 스위트 클래스
//           기존: class PrimeTest : public testing::Test {};
// 파라미터화 테스트: class PrimeTest : public testing::TestWithParam<InputType>

class PrimeTest : public testing::TestWithParam<int>
{
protected:
  void SetUp() override {}
  void TearDown() override {}

  static void SetUpTestSuite() {}
  static void TearDownTestSuite() {}
};

// 2. 데이터 셋 정의
int data[] = {2, 3, 5, 7, 8, 11, 13, 17, 19, 23, 37};

// 1.10 이후: INSTANTIATE_TEST_SUITE_P(데이터셋이름, TestSuite이름, 데이터)
// 1.10 이전: INSTANTIATE_TEST_CASE_P

INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, testing::ValuesIn(data));

// 3. 데이터 셋을 이용하는 테스트케이스 정의
//    -   TEST: 암묵적인 테스트 스위트
//    - TEST_F: 명시적인 테스트 스위트
//    - TEST_P: 파라미터화 테스트 스위트
TEST_P(PrimeTest, IsPrime)
{
  // 데이터 셋의 데이터를 한개씩 가져올 수 있습니다.
  // => GetParam()
  EXPECT_TRUE(IsPrime(GetParam()));
}

TEST_P(PrimeTest, IsPrime2)
{
  // 데이터 셋의 데이터를 한개씩 가져올 수 있습니다.
  // => GetParam()
  EXPECT_TRUE(IsPrime(GetParam()));
}