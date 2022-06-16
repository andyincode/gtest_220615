// 8_FriendTest.cpp
// => C++의 friend 문법을 이용합니다.
// => friend로 선언된 클래스나 함수는 클래스의 private에 접근이 가능합니다.

#if 0
class User
{
  int age = 0;
  int GetAge() const { return age; }

public:
  void NextYear() { age += 1; }
};
#endif
#include "User.h"

// 좋지 않는 접근 방식입니다.
// => 사용하지 않는 것이 좋습니다.
#if 0
#define private public
#define class struct
#include "User.h"
#undef private
#undef class
#endif

#include <gtest/gtest.h>

// 테스트 코드에서 상태를 확인할 수 없는 경우,
// 테스트 검증 코드를 작성할 수 없습니다.

TEST(UserTest, NextYear)
{
  User user;

  user.NextYear();

  EXPECT_EQ(user.GetAge(), 1);
}