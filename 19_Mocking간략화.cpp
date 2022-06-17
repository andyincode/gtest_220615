// 19_Mocking간략화.cpp

enum Level
{
  INFO
};

class Logger
{
public:
  virtual ~Logger() {}

  virtual void Send(Level level,
                    const char *dir,
                    const char *filename,
                    int line,
                    const char *message) = 0;
};

class User
{
public:
  void Process(Logger *logger)
  {
    logger->Send(INFO, "/tmp", "process.log", 10, "hello world");
  }
};

#include <gmock/gmock.h>

class MockLogger : public Logger
{
public:
  // 필요한 인자를 가지는 함수를 MOCK_METHOD 합니다.
  // void Send(int line, const char* message)
  MOCK_METHOD(void, Send, (int line, const char *message));

  void Send(Level level,
            const char *dir,
            const char *filename,
            int line,
            const char *message) override
  {
    Send(line, message);
  }
};

// 필요한 요소에 대해서만 검증을 수행하는 방법입니다.
TEST(UserTest, Process)
{
  MockLogger mock;
  User user;

  EXPECT_CALL(mock, Send(10, "hello world"));

  user.Process(&mock);
}

#if 0
class MockLogger : public Logger
{
public:
  MOCK_METHOD(void, Send,
              (Level level, const char *dir, const char *filename, int line, const char *message),
              (override));
};

TEST(UserTest, Process)
{
  MockLogger mock;
  User user;

  EXPECT_CALL(mock, Send(INFO, "/tmp", "process.log", 10, "hello world"));

  user.Process(&mock);
}
#endif