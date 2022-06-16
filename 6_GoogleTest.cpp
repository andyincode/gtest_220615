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