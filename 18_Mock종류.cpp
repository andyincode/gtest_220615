// 18_Mock종류.cpp

class User
{
public:
  virtual ~User() {}

  virtual void Go() {}
  virtual void Say() {}
};

void UseUser(User *p)
{
  p->Go();
  p->Say();
}

#include <gmock/gmock.h>

// Google Mock은 3가지 종류의 Mock을 제공합니다.
// > MOCK_METHOD한 메소드가 호출이 되었는데, EXPECT_CALL을 하고 있지 않을 때
// 1. Default(Naggy Mock)
//   : 테스트의 결과는 성공입니다.
//     관심없는 호출에 대한 경고가 출력됩니다.
//     Uninteresting mock function call - returning directly.
//        Function call: Say()

// 2. Nice Mock
//   : 테스트의 결과도 동일하고, 경고도 출력되지 않습니다.

// 3. Strict Mock
//   : 테스트가 실패합니다.
//   => 테스트의 통과 기준이 높아집니다.
//      테스트를 작성하는 비용이 증가할 수 있습니다.

class MockUser : public User
{
public:
  MOCK_METHOD(void, Go, (), (override));
  MOCK_METHOD(void, Say, (), (override));
};

using testing::NiceMock;
using testing::StrictMock;

TEST(UserTest, UseUser)
{
  StrictMock<MockUser> mock;

  EXPECT_CALL(mock, Go);
  // EXPECT_CALL(mock, Say);

  UseUser(&mock);
}