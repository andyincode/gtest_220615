// 22_Matcher.cpp
#include <gmock/gmock.h>

// Hamcrest Matcher
// => JUnit 안에서 단언문을 작성할 때, 가독성이 좋은 단언문을 작성할 수
//    있습니다.
//   "비교 표현의 확장 라이브러리"

// => GoogleMock은 Hamcrest Style의 단언문을 작성할 수 있습니다.

int GetAge() { return 42; }
const char *GetMessage() { return "Hello, world"; }

using testing::Eq; // ==

using testing::MatchesRegex;
using testing::StartsWith;

TEST(HamcrestTest, Sample1) {
  EXPECT_EQ(GetAge(), 42);

  EXPECT_THAT(GetAge(), Eq(42));
  EXPECT_THAT(GetMessage(), StartsWith("Hello"));
  EXPECT_THAT(GetMessage(), MatchesRegex(".*"));
}

class User {
  std::string name;
  int age;

public:
  User(const std::string &name, int age) : name(name), age(age) {}

  std::string GetName() const { return name; }
  int GetAge() const { return age; }

  FRIEND_TEST(UserTest, Sample1);
};

using testing::Field;
using testing::Lt;
using testing::Property;

std::ostream &operator<<(std::ostream &os, const User &user) {
  return os << "User{name=" << user.GetName() << "}";
}

TEST(UserTest, Sample1) {
  User user("Bob", 42);
  ///...

  EXPECT_EQ(user.GetName(), "Tom");
  EXPECT_EQ(user.GetAge(), 42);

  EXPECT_THAT(user, Property(&User::GetName, Eq("Tom")));
  EXPECT_THAT(user, Field(&User::age, Lt(10))) << "연산하였을 때";
}