// 11_테스트리스너.cpp
#include <gtest/gtest.h>

TEST(SampleTest, FirstTest)
{
  std::cout << "FirstTest" << std::endl;
  FAIL();
}

TEST(SampleTest, SecondTest)
{
  std::cout << "SecondTest" << std::endl;
}

using testing::TestInfo;
using testing::TestPartResult;
using testing::TestSuite;
using testing::UnitTest;

using std::cout;
using std::endl;

// Google Test는 Test Listener를 통해 출력을 제공하고 있습니다.
// class MyTestPrinter : public testing::TestEventListener
class MyTestPrinter : public testing::EmptyTestEventListener
{
  void OnTestProgramStart(const UnitTest & /*unit_test*/) override
  {
    cout << "My Test Program Start" << endl;
  }
  void OnTestProgramEnd(const UnitTest & /*unit_test*/) override
  {
    cout << "My Test Program End" << endl;
  }

  void OnTestSuiteStart(const TestSuite &test_suite) override
  {
    cout << test_suite.name() << " Start" << endl;
  }

  void OnTestSuiteEnd(const TestSuite &test_suite) override
  {
    cout << test_suite.name() << " End" << endl;
  }

  void OnTestStart(const TestInfo &test_info) override
  {
    cout << "  " << test_info.name() << endl;
  }

  void OnTestEnd(const TestInfo &test_info) override
  {
    cout << "  " << test_info.name() << ": " << (test_info.result()->Passed() ? "[PASS]" : "[FAIL]") << endl;
  }
};

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);

  // 테스트 이벤트 리스너를 등록하는 방법.
  testing::TestEventListeners &listeners = testing::UnitTest::GetInstance()->listeners();
  listeners.Append(new MyTestPrinter); // !!

  // 기본 출력을 제거하는 방법.
  delete listeners.Release(listeners.default_result_printer());

  return RUN_ALL_TESTS();
}