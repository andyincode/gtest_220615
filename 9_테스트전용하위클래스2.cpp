// 9_테스트전용하위클래스2.cpp

class User
{
private:
  int age = 100;

  // public:
protected:
  int GetAge() const { return age; }
};

#include <gtest/gtest.h>

// 테스트 전용 하위 클래스
//  => protected로 구성되어 있는 기능에 접근이 가능합니다.
class TestUser : public User
{
public:
  using User::GetAge; // TestUser 에서는 GetAge가 public으로 취급됩니다.
};

TEST(UserTest, Age)
{
  // User user;
  TestUser user;
  EXPECT_EQ(user.GetAge(), 100);
}
