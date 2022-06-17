
#include <string>
#include <vector>

enum Level
{
  INFO,
  WARN,
  ERROR,
};

struct DLoggerTarget
{
  virtual ~DLoggerTarget() {}
  virtual void Write(Level level, const std::string &message) = 0;
};

class ConsoleTarget : public DLoggerTarget
{
public:
  void Write(Level level, const std::string &message)
  {
    printf("[%d]: %s\n", level, message.c_str());
  }
};

class DLogger
{
  std::vector<DLoggerTarget *> targets;

public:
  void AddTarget(DLoggerTarget *p) { targets.push_back(p); }

  void Write(Level level, const std::string &message)
  {
    for (DLoggerTarget *t : targets)
    {
      t->Write(level, message);
      break;
    }
  }
};

#include <algorithm>
#include <gtest/gtest.h>

// Test Spy Pattern
//  의도: SUT의 함수를 호출하였을 때 발생하는 부수 효과를 관찰할 수 없어서,
//       테스트되지 않은 요구사항이 있다.
//  방법: 목격한 일을 기록해두었다가 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역을 사용합니다.
//      "다른 컴포넌트로부터의 간접 출력을 저장해두었다가 검증한다."

TEST(DLoggerTest, Write)
{
  ConsoleTarget t1, t2;
  DLogger logger;
  logger.AddTarget(&t1);
  logger.AddTarget(&t2);

  logger.Write(INFO, "test_message");
}

class SpyTarget : public DLoggerTarget
{
  std::vector<std::string> history;

  std::string concat(Level level, const std::string &message)
  {
    static std::string levels[] = {
        "I",
        "W",
        "E",
    };

    return levels[level] + message;
  }

public:
  void Write(Level level, const std::string &message)
  {
    history.push_back(concat(level, message));
  }

  bool IsReceived(Level level, const std::string &message)
  {
    return std::find(begin(history), end(history),
                     concat(level, message)) != end(history);
  }
};

TEST(DLoggerTest, Write2)
{
  SpyTarget t1, t2;
  DLogger logger;
  logger.AddTarget(&t1);
  logger.AddTarget(&t2);

  logger.Write(INFO, "test_message");

  EXPECT_TRUE(t1.IsReceived(INFO, "test_message"));
  EXPECT_TRUE(t2.IsReceived(INFO, "test_message"));
}