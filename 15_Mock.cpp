
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
      // break;
    }
  }
};

#include <algorithm>
#include <gmock/gmock.h> // !!
#include <gtest/gtest.h>

// Mock Object Pattern / 모의 객체
//  의도: SUT의 함수를 호출하였을 때 발생하는 부수 효과를 관찰할 수 없어서,
//       테스트되지 않은 요구사항이 있다.
//  방법: 행위 기반 검증을 수행합니다.
//       => Mock Framework을 이용하여 행위 기반 검증을 수행할 수 있습니다.
//       => Google Mock

//  행위 기반 검증
//  : 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부 / 횟수 / 순서 / 인자를 통해 검증합니다.
//  상태 기반 검증
//  : 객체에 작용을 가한 후, 내부적으로 발생하는 부수 효과(값의 변경)를 통해 검증합니다.

// Mocking - 모의 객체를 만들어야 합니다.
#if 0
struct DLoggerTarget
{
  virtual ~DLoggerTarget() {}
  virtual void Write(Level level, const std::string &message) = 0;
};
#endif

class MockDLoggerTarget : public DLoggerTarget
{
public:
  // void Write(Level level, const std::string &message) override {}
  // MOCK_METHOD{인자개수}(메소드 이름, 메소드 타입);

  MOCK_METHOD2(Write, void(Level level, const std::string &message));
};

// Google Mock의 EXPECT_CALL은 작용을 가하기 전에 사용해야 합니다.
TEST(DLoggerTest, Write)
{
  // Arrange
  MockDLoggerTarget t1, t2;
  DLogger logger;
  logger.AddTarget(&t1);
  logger.AddTarget(&t2);

  // Assert
  EXPECT_CALL(t1, Write(INFO, "test_message"));
  EXPECT_CALL(t2, Write(INFO, "test_message"));

  // Act
  logger.Write(INFO, "test_message");
}

// Test Double(테스트 대역)
// 1. Test Stub
//   - 특수한 상황을 시뮬레이션 한다.
//   - 협력 객체가 원하는 결과를 주도록 제어한다.

// 2. Fake Object
//  - 가벼운 테스트 대역을 통해 검증되지 않은 로직을 검증한다.

// 3. Test Spy
//  - 관찰할 수 있는 부수 효과가 없다.
//    목격한 일을 기록해두었다가 테스트에서 검증할 수 있도록 하는 테스트 대역

// 4. Mock Object
//  - 관찰할 수 있는 부수 효과가 없다.
//    행위 기반 검증을 통해 검증을 수행한다.
// => xUnit Test Pattern에 의해서 정의되었습니다.
//    이전에는 테스트 대역을 총칭해서 Mock Object 라고 하였습니다.

// => Google Mock은 테스트 대역의 기능을 가지고 있습니다.
//     : Stub / Fake 등의 요소를 만들 수 있습니다.