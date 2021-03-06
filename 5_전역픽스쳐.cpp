// 5_전역픽스쳐.cpp
//  : Global Fixture SetUp / TearDown
// => xUnit Test Framework이 제공하는 공통의 기능이 아니라,
//    Google Test 고유의 기능입니다.
// => 프로그램의 시작 단계에서 초기화해야 하는 작업과,
//    프로그램의 종료 단계에서 정리해야 하는 작업을 정의합니다.

#include <gtest/gtest.h>

class SampleTest : public testing::Test
{
protected:
  void SetUp() override { printf("SetUp()\n"); }
  void TearDown() override { printf("TearDown()\n"); }
  static void SetUpTestSuite() { printf("SetUpTestSuite()\n"); }
  static void TearDownTestSuite() { printf("TearDownTestSuite()\n"); }
};

TEST_F(SampleTest, FirstTest) {}
TEST_F(SampleTest, SecondTest) {}

TEST(SampleTest2, foo) {}
TEST(SampleTest3, foo) {}

class TestEnvironment : public testing::Environment
{
public:
  TestEnvironment() { printf("TestEnvironment()\n"); }
  ~TestEnvironment() { printf("~TestEnvironment()\n"); }

  void SetUp() override { printf("TestEnvironment::SetUp()\n"); }
  void TearDown() override { printf("TestEnvironment::TearDown()\n"); }
};

class TestEnvironment2 : public testing::Environment
{
public:
  TestEnvironment2() { printf("TestEnvironment2()\n"); }
  ~TestEnvironment2() { printf("~TestEnvironment2()\n"); }

  void SetUp() override { printf("TestEnvironment::SetUp2()\n"); }
  void TearDown() override { printf("TestEnvironment::TearDown2()\n"); }
};

// Global Fixture를 설치하는 방법 2가지
// 1) 사용자가 main을 제공하고 있지 않을 때 => 권장하지 않습니다.
//  > 전역 변수에 대한 초기화가 main 시작 전에 수행되는 언어적인 특성을 이용합니다.
// testing::Environment *env1 = testing::AddGlobalTestEnvironment(new TestEnvironment);
// testing::Environment *env2 = testing::AddGlobalTestEnvironment(new TestEnvironment2);
// 각 파일에 있는 전역 변수의 초기화 순서가 보장되지 않습니다.
// => 표준에 정의되어 있지 않습니다.

// 2) 사용자가 main을 제공하고 있을 때
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  testing::AddGlobalTestEnvironment(new TestEnvironment);
  testing::AddGlobalTestEnvironment(new TestEnvironment2);
  // 주의사항: 반드시 new를 통해 제공해야 합니다.

  return RUN_ALL_TESTS();
}
