// 21_동작검증3.cpp
#include <gmock/gmock.h>

class Calc {
public:
  virtual ~Calc() {}

  virtual int Add(int a, int b) = 0;
  virtual int Sub(int a, int b) = 0;
};

class MockCalc : public Calc {
public:
  MOCK_METHOD(int, Add, (int a, int b), (override));
  MOCK_METHOD(int, Sub, (int a, int b), (override));
};

void Calculate(Calc *p) {
  // printf("Add: %d\n", p->Add(10, 20));
  // printf("Add: %d\n", p->Add(10, 20));
  // printf("Add: %d\n", p->Add(10, 20));
  // printf("Add: %d\n", p->Add(10, 20));
}

int AddFake(int a, int b) { return a + b; }

using testing::Return;

// ON_CALL 과 EXPECT_CALL을 같이 사용한다면,
// => EXPECT_CALL을 통해 ON_CALL의 역활을 대신할 수 있습니다.
//  1) WillOnce
//  2) WillRepeatedly

TEST(CalcTest, Sample4) {
  MockCalc mock;

  // Times(AtLeast(0))
  EXPECT_CALL(mock, Add).WillRepeatedly(Return(100));
  // 위처럼 사용하면, 호출이 되지 않아도 테스트는 성공합니다.
  //  => WillRepeatedly를 단독으로 사용하지 않는 것이 좋습니다.

  Calculate(&mock);
}

TEST(CalcTest, Sample3) {
  MockCalc mock;

  // Times(AtLeast(WillOnce 개수))
  EXPECT_CALL(mock, Add)
      .WillOnce(Return(10))
      .WillOnce(Return(20))
      .WillRepeatedly(Return(100));

  Calculate(&mock);
}

TEST(CalcTest, Sample2) {
  MockCalc mock;

  // Times(4)
  EXPECT_CALL(mock, Add)
      .WillOnce(Return(10))
      .WillOnce(Return(20))
      .WillOnce(Return(30))
      .WillOnce(Return(40));

  Calculate(&mock);
}

// ON_CALL
//   .WillByDefault
TEST(CalcTest, Sample1) {
  MockCalc mock;
  ON_CALL(mock, Add).WillByDefault(&AddFake);

  EXPECT_CALL(mock, Add).Times(4);

  Calculate(&mock);
}
