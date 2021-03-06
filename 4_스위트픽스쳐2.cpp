// 4_스위트픽스쳐.cpp
#include <string>
#include <unistd.h> // sleep

class Terminal
{
public:
  // Connect / Disconnect가 느리다고 가정합니다.
  void Connect() { sleep(2); }
  void Disconnect() { sleep(1); }

  void Login(const std::string &id, const std::string &password) {}
  void Logout() {}

  bool IsLogin() const { return false; }
};

//-------------------------
#include <gtest/gtest.h>

class TerminalTest : public testing::Test
{
protected:
  // Terminal *terminal = nullptr;
  static Terminal *terminal;

  void SetUp() override
  {
  }

  void TearDown() override
  {
  }

  // Suite Fixture SetUp() / TearDown()
  static void SetUpTestSuite()
  {
    printf("SetUpTestSuite()\n");
    terminal = new Terminal;
    terminal->Connect();
  }

  static void TearDownTestSuite()
  {
    printf("TearDownTestSuite()\n");
    terminal->Disconnect();
    delete terminal;
  }
};

// 정적 멤버 변수는 외부 정의가 필요합니다 - C++ 문법
Terminal *TerminalTest::terminal = nullptr;

TEST_F(TerminalTest, Login)
{
  terminal->Login("test_id", "test_password");

  ASSERT_TRUE(terminal->IsLogin()) << "로그인하였을 때";
}

TEST_F(TerminalTest, Logout)
{
  terminal->Login("test_id", "test_password");
  terminal->Logout();

  ASSERT_FALSE(terminal->IsLogin()) << "로그아웃 하였을 때";
}

TEST_F(TerminalTest, foo) {}
TEST_F(TerminalTest, goo) {}
TEST_F(TerminalTest, hoo) {}

// 문제점: SetUp() / TearDown()이 느려서, 테스트 케이스가 추가될 때마다
//       전체적인 테스트 시간이 느려지는 문제가 발생합니다.
//    => Slow Test 문제
//    1) 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.
//    2) 테스트가 너무 느려서, 아무도 코드가 변경되어도 테스트를 수행되지 않는다.
//    해결방법
//    => Test Suite SetUp() / TearDown()을 통해서 해결할 수 있습니다.
//    => 스위트 픽스쳐

// 스위트 픽스쳐(Suite Fixture)
// : "신선한 픽스쳐 전략"이 "공유 픽스쳐 전략" 으로 변경됩니다.
// 문제점
//  - 더 이상 각각의 테스트 케이스가 독립적이지 않습니다.
//  - 이전 테스트케이스로 인해서 스위트 픽스쳐의 상태가 망가졌다면,
//    이후의 테스트케이스들의 모든 결과를 신뢰할 수 없습니다.
//   => "변덕스러운 테스트"
//  - 공유 픽스쳐의 전략에서 "변덕스러운 테스트" 문제가 발생한다면
//    테스트 스위트를 분리하는 것이 좋습니다.

// --- Suite Fixture SetUp ---
// TerminalTest()
// SetUp()
// Login()
// TearDown()
// ~TerminalTest()
// TerminalTest()
// SetUp()
// Login()
// TearDown()
// ~TerminalTest()
// --- Suite Fixture TearDown ---
