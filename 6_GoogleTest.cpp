// 6_GoogleTest.cpp
#include <gtest/gtest.h>

// xUnit Test Framework
// 1. Fixture
// 2. Assertion

int foo() { return -1; }
int goo() { return -1; }

// - ASSERT_XXX
//  => 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//  => 하나의 테스트 케이스안에 여러 개의 단언문이 존재할 경우,
//     이후의 단언문이 수행되지 않는 문제가 발생할 수 있습니다.
//    : 죽은 단언문
//  => 해결 방법
//    xUnit Test Pattern
//     : 하나의 테스트케이스 안에 여러개의 단언문을 사용하지 않는 것이 좋습니다.
//      문제점: 하나의 기능에 대해서 중복된 테스트케이스가 많아지는 발생할 수 있습니다.
TEST(SampleTest, Sample1)
{
  int actualFoo = foo();
  int actualGoo = goo();

  ASSERT_EQ(actualFoo, 42);
  ASSERT_EQ(actualGoo, 100);
}

// - EXPECT_XXX
//  => 실패할 경우, 테스트의 결과는 실패가 되지만, 이후의 코드를 계속 수행합니다.
//  => "죽은 단언문" / "중복된 테스트케이스"
TEST(SampleTest, Sample2)
{
  int actualFoo = foo();
  int actualGoo = goo();

  EXPECT_EQ(actualFoo, 42);
  EXPECT_EQ(actualGoo, 100);
}

class User
{
  int age = 10;

public:
  int GetAge() const { return age; }
};

User *GetUser() { return nullptr; }

TEST(SampleTest, Sample3)
{
  User *user = GetUser();

  ASSERT_NE(user, nullptr); // 사전 조건 단언문
                            // : 비정상 종료가 발생하지 않도록 합니다.
                            //   불필요한 검증이 더 이상 수행되지 않도록 할 수 있습니다.
  EXPECT_EQ(user->GetAge(), 100);
}

// 문자열 비교 단언문
// 1. C 문자열: const char* / char[]
// 2. C++ 문자열: string

// 주의사항: C의 문자열을 비교할 때는 문자열 전용 단언 매크로를 사용해야 합니다.
//    EXPECT_STREQ/STRNE
//    EXPECT_STRCASEEQ/STRCASENE
TEST(SampleTest2, Sample1)
{
  std::string s1 = "hello";
  std::string s2 = "hello";

  const char *s3 = "hello";
  char s4[] = "Hello";

  EXPECT_EQ(s1, s2);
  EXPECT_STRCASEEQ(s3, s4);
}

// 부동소수점 비교 단언문
// - EXPECT_DOUBLE_EQ / EXPECT_FLOAT_EQ / NE
// - 오차 범위를 직접 지정하고 싶다: EXPECT_NEAR
TEST(SampleTest2, Sample2)
{
  double a = 0.7;
  double b = 0.1 * 7;

  EXPECT_DOUBLE_EQ(a, b); // 4ULP - https://en.wikipedia.org/wiki/Unit_in_the_last_place
  EXPECT_NEAR(a, b, 0.0000000000001);
}

void OpenFile(const std::string &filename)
{
  if (filename.empty())
  {
    // throw std::invalid_argument("파일 이름이 비어있습니다.");
    // throw 1;
  }
}

TEST(SampleTest2, Sample3)
{
  // OpenFile 함수에 잘못된 인자가 전달된 경우,
  // invalid_argument 예외가 제대로 발생하는지 여부를 검증하고 싶다.

  try
  {
    OpenFile("");
    FAIL() << "예외가 발생하지 않았습니다.";
  }
  catch (std::invalid_argument &e)
  {
    SUCCEED();
  }
  catch (...)
  {
    FAIL() << "다른 종류의 예외가 발생하였습니다.";
  }
}

// 예외 테스트용 단언문을 제공합니다.
//  - EXPECT_THROW
//    : 기대한 예외 타입
//    EXPECT_ANY_THROW
//    : 예외 발생 여부
TEST(SampleTest2, Sample4)
{
  std::string emptyFilename = "";

  // OpenFile 함수에 잘못된 인자가 전달된 경우,
  // invalid_argument 예외가 제대로 발생하는지 여부를 검증하고 싶다.

  // EXPECT_THROW(OpenFile(""), std::invalid_argument);
  // Expected: OpenFile("") throws an exception of type std::invalid_argument.

  EXPECT_THROW(OpenFile(emptyFilename), std::invalid_argument);
  // Expected: OpenFile(emptyFilename) throws an exception of type std::invalid_argument.
}

// 테스트 비활성화
//  1) 테스트가 수행되지 않고, 결과에도 포함되지 않지만, 존재한다는 사실을 알려야 합니다.
//  2) 비활성화된 테스트를 포함해서 돌릴 수 있는 기능도 제공됩니다.
//   > $ ./a.out --gtest_also_run_disabled_tests

//  Google Test에서 비활성화 하는 방법
//  1. TestCase의 이름이 DISABLED_ 로 시작하는 경우
//  2. TestSuite의 이름이 DISABLED_ 로 시작하는 경우

// - 테스트 코드를 주석 처리를 통해 비활성화하면, "잊혀진 테스트"가 됩니다.

class DISABLED_SampleTest3 : public testing::Test
{
};

TEST_F(DISABLED_SampleTest3, DISABLED_Sample1)
{
  // 작성 중입니다.
  FAIL() << "작성 중입니다.";
}

TEST_F(DISABLED_SampleTest3, foo) {}
TEST_F(DISABLED_SampleTest3, goo) {}
TEST_F(DISABLED_SampleTest3, hoo) {}