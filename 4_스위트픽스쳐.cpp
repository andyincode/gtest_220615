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

#if 0
class TerminalTest : public testing::Test
{
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TerminalTest, Login)
{
  // Arrange
  Terminal *terminal = new Terminal;
  terminal->Connect();

  // Act
  terminal->Login("test_id", "test_password");

  // Assert
  ASSERT_TRUE(terminal->IsLogin()) << "로그인하였을 때";

  // 해체
  terminal->Disconnect();
  delete terminal;
}

TEST_F(TerminalTest, Logout)
{
  // Arrange
  Terminal *terminal = new Terminal;
  terminal->Connect();

  // Act
  terminal->Login("test_id", "test_password");
  terminal->Logout();

  // Assert
  ASSERT_FALSE(terminal->IsLogin()) << "로그아웃 하였을 때";

  // 해체
  terminal->Disconnect();
  delete terminal;
}
#endif

class TerminalTest : public testing::Test
{
protected:
  Terminal *terminal = nullptr;

  void SetUp() override
  {
    terminal = new Terminal;
    terminal->Connect();
  }

  void TearDown() override
  {
    terminal->Disconnect();
    delete terminal;
  }

  // Suite Fixture SetUp() / TearDown()
  static void SetUpTestSuite()
  {
    printf("SetUpTestSuite()\n");
  }

  static void TearDownTestSuite()
  {
    printf("TearDownTestSuite()\n");
  }

#if 0
  static void SetUpTestCase()
  {
    printf("SetUpTestCase()\n");
  }

  static void TearDownTestCase()
  {
    printf("TearDownTestCase()\n");
  }
#endif
};

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