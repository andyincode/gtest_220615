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

// private 함수는 검증해야 하는가?
// 1. 검증해야 한다.
//    테스트 커버리지를 달성하기 위해서
// 2. private 함수
//    => 외부에서 호출이 불가능한 기능입니다.
//    Clean Code: Robert C Martin
//      : 테스트되지 않은 private 메소드가
//        테스트된 public 메소드보다 위험하다.
//      - public 함수를 통해서 private 함수가 자연스럽게 호출되어야 한다.
//      - private 함수는 public 함수의 가독성을 높이기 위해 사용해야 한다.