// 21_동작검증.cpp
// : 동작 검증 / 행위 기반 검증
// 1) 함수 호출 여부
// 2) 함수 호출 횟수
// 3) 함수 호출 인자
// 4) 함수 호출 순서

#include <vector>

class User {
public:
  virtual ~User() {}

  virtual void Go(int x, int y) = 0;
  virtual void Print(const std::vector<int> &numbers) = 0;
};

#include <gmock/gmock.h>

class MockUser : public User {
public:
  MOCK_METHOD(void, Go, (int x, int y), (override));
  MOCK_METHOD(void, Print, (const std::vector<int> &numbers), (override));
};

void Sample1(User *p) {
  p->Go(100, 200);
  p->Go(10, 20);
}

// 1. 함수 호출 여부를 검증
//  => EXPECT_CALL
TEST(SampleTest, Sample1) {
  MockUser mock;

  // EXPECT_CALL(mock, Go); // 인자에 상관없이 호출된지 체크합니다.
  EXPECT_CALL(mock, Go(10, 20));
  EXPECT_CALL(mock, Go(100, 200));

  Sample1(&mock);
}

void Sample2(User *p) {
  p->Go(100, 200);
  p->Go(100, 200);
  p->Go(10, 20);
  p->Go(10, 20);
}

// 2. 함수 호출 횟수 검증
//   + Times(N)
using testing::AnyNumber;
using testing::AtLeast;
using testing::AtMost;
using testing::Between;

TEST(SampleTest, Sample2) {
  MockUser mock;

  // EXPECT_CALL(mock, Go); // 1번 호출됩니다.
  // EXPECT_CALL(mock, Go).Times(2);

  // 적어도 1번 이상 Go가 호출되어야 합니다. - AtLeast
  // EXPECT_CALL(mock, Go).Times(AtLeast(1));

  // 최대 2번까지 Go가 호출되어야 합니다.  - AtMost
  // EXPECT_CALL(mock, Go).Times(AtMost(2));
  EXPECT_CALL(mock, Go).Times(Between(2, 4));

  Sample2(&mock);
}

// 3. 함수 호출 횟수는 인자 매칭에 따라 달라질 수 있습니다.
void Sample3(User *p) {
  p->Go(100, 35);
  p->Go(100, -1);
}

// => 인자 매칭은 Matcher를 이용해야 합니다.
using testing::_;     // *
using testing::AllOf; // &&
using testing::AnyOf; // ||
using testing::Eq;    // ==
using testing::Ge;    // >=
using testing::Gt;    // >
using testing::Le;    // <=
using testing::Lt;    // <
using testing::Matcher;
using testing::Ne; // !=

TEST(SampleTest, DISABLED_Sample3) {
  MockUser mock;

  // Go의 첫번째 인자가 0보다 커야 한다.
  // EXPECT_CALL(mock, Go(Gt(0), _)).Times(2);

  // 첫번째 인자가 10보다 크고 30보다 작거나 같아야 한다.
  // Gt(10) && Le(30)
  // Matcher<int> arg1 = AllOf(Gt(10), Le(30)); // 10 < arg1 <= 30
  auto arg1 = AllOf(Gt(10), Le(30));

  // 두번째 인자는 0보다 작거나, 30보다 커야 한다.
  // Lt(0) || Gt(30)
  Matcher<int> arg2 = AnyOf(Lt(0), Gt(30));
  EXPECT_CALL(mock, Go(arg1, arg2)).Times(2);

  Sample3(&mock);
}

void Sample4(User *p) {
  std::vector<int> data = {20, 30, 10};
  p->Print(data);
}

using testing::ElementsAre;
using testing::ElementsAreArray;
using testing::UnorderedElementsAre;
using testing::UnorderedElementsAreArray;

TEST(SampleTest, Sample4) {
  MockUser mock;

  // {10, 20, 30}
  // EXPECT_CALL(mock, Print(ElementsAre(10, 20, 30)));

  // int expected[] = {10, 20, 30};
  Matcher<int> expected[] = {Lt(30), Gt(15), Lt(100)};
  // EXPECT_CALL(mock, Print(ElementsAreArray(expected)));

  EXPECT_CALL(mock, Print(UnorderedElementsAreArray(expected)));

  Sample4(&mock);
}