// 21_동작검증2.cpp
//  - 호출 순서

class User {
public:
  virtual ~User() {}

  virtual void First() = 0;
  virtual void Second() = 0;
  virtual void Third() = 0;
  virtual void Fourth() = 0;
};

#include <gmock/gmock.h>

class MockUser : public User {
public:
  MOCK_METHOD(void, First, (), (override));
  MOCK_METHOD(void, Second, (), (override));
  MOCK_METHOD(void, Third, (), (override));
  MOCK_METHOD(void, Fourth, (), (override));
};

void Sample1(User *p) {
  p->First();
  p->Second();
  p->Third();
  p->Fourth();
}

// 호출 순서
//  : First -> Second -> Third -> Fourth
//  - InSequence
using testing::InSequence; // 순서 검증

TEST(SampleTest, Sample1) {
  InSequence seq; // !!!!
  MockUser mock;

  EXPECT_CALL(mock, First);
  EXPECT_CALL(mock, Second);
  EXPECT_CALL(mock, Third);
  EXPECT_CALL(mock, Fourth);

  Sample1(&mock);
}

void Sample2(User *p) {
  p->First();
  p->Third();
  p->Second();
  p->Fourth();
}

// First ----> Second             => seq1
//        |
//        |
//         ---> Third -> Fourth   => seq2

using testing::Sequence;
//   EXPECT_CALL(...).InSequence(seq1, seq2);

TEST(SampleTest, Sample2) {
  MockUser mock;
  Sequence seq1, seq2;

  EXPECT_CALL(mock, First).InSequence(seq1, seq2);
  EXPECT_CALL(mock, Second).InSequence(seq1);
  EXPECT_CALL(mock, Third).InSequence(seq2);
  EXPECT_CALL(mock, Fourth).InSequence(seq2);

  Sample2(&mock);
}

// Mock / InSequence / Sequence
// => 파괴되는 시점에 테스트의 결과가 판단됩니다.

TEST(SampleTest, Sample3) {
  MockUser mock;

  EXPECT_CALL(mock, First);

  // MockUser *mock = new MockUser;
  // EXPECT_CALL(*mock, First);
  // delete mock;
}