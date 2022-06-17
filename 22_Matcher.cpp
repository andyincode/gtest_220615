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
  EXPECT_THAT(GetMessage(), StartsWith("xHello"));
  EXPECT_THAT(GetMessage(), MatchesRegex("x.*"));
}
