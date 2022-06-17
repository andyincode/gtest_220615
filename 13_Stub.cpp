// 13_Stub.cpp
#include <string>

class Time {
public:
  virtual ~Time() {}

  virtual std::string GetCurrentTime() = 0;
};

// 현재 시간을 구해서 반환합니다.
class Clock : public Time {
public:
  std::string GetCurrentTime() override { return "08:37"; }
};

class User {
public:
  int Display(Time *time) {
    std::string t = time->GetCurrentTime();

    // 시간에 따라서 다른 동작을 수행합니다.
    if (t == "00:00")
      return 42;
    else if (t == "10:00")
      return 100;

    return 0;
  }
};

//---------------------
// Test Stub Pattern
// 의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고
// 싶다. 방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데
// 필요한 결과를 보내도록 한다.
//   => 특수한 상황을 시뮬레이션하고 싶다.
//   => 예외, 반환값, 시간 등의 제어하기 힘든 요소를 제어할 수 있습니다.

// User --------> Time
//                  |
//                Clock / StubTime
#include <gtest/gtest.h>

class StubTime : public Time {
  std::string result;

public:
  void SetResult(const std::string &r) { result = r; }
  std::string GetCurrentTime() override { return result; }
};

TEST(UserTest, Display1) {
  StubTime stub;
  stub.SetResult("00:00");
  User user;

  EXPECT_EQ(42, user.Display(&stub)) << "00:00 일때";
}

TEST(UserTest, Display2) {
  StubTime stub;
  stub.SetResult("10:00");
  User user;

  EXPECT_EQ(100, user.Display(&stub)) << "10:00 일때";
}

#include <gmock/gmock.h>

// Google Mock을 이용해서 Stub을 만들 수 있습니다.
class MockTime : public Time {
public:
  MOCK_METHOD(std::string, GetCurrentTime, (), (override));
};

using testing::NiceMock;
using testing::Return;
TEST(UserTest2, Display1) {
  NiceMock<MockTime> stub;
  ON_CALL(stub, GetCurrentTime).WillByDefault(Return("00:00"));
  User user;

  EXPECT_EQ(42, user.Display(&stub)) << "00:00 일때";
}

TEST(UserTest2, Display2) {
  NiceMock<MockTime> stub;
  ON_CALL(stub, GetCurrentTime).WillByDefault(Return("10:00"));
  User user;

  EXPECT_EQ(100, user.Display(&stub)) << "10:00 일때";
}