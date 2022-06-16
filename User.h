#ifndef USER_H
#define USER_H

#include <gtest/gtest.h>

class User
{
  int age = 0;
  int GetAge() const { return age; }

public:
  void NextYear() { age += 1; }

  FRIEND_TEST(UserTest, NextYear);
  // 제품 코드에서 gtest 의존성이 발생합니다.
};

#endif