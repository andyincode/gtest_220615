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