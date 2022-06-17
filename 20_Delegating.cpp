// 20_Delegating.cpp

#include <stdio.h>

class Calc {
public:
  virtual ~Calc() {}

  virtual int Add(int a, int b) { return a + b; }
  virtual int Sub(int a, int b) { return a - b; }
};

void Calculate(Calc *p) {
  if (p->Add(10, 202) == 30) {
    int result = p->Sub(10, 30);
    printf("result: %d OK!\n", result);
  } else {
    printf("NO!\n");
  }
}

#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
  MOCK_METHOD(int, Add, (int a, int b), (override));
  MOCK_METHOD(int, Sub, (int a, int b), (override));
};

using testing::NiceMock;
using testing::Return;

TEST(SampleTest, Sample2) {
  NiceMock<MockCalc> mock;
  ON_CALL(mock, Add).WillByDefault(Return(30));
  ON_CALL(mock, Sub).WillByDefault(Return(100));

  EXPECT_CALL(mock, Add);
  EXPECT_CALL(mock, Sub);

  Calculate(&mock);
}

int Add(int a, int b) {
  printf("함수로 위임\n");
  return a + b;
}

struct Functor {
  int operator()(int a, int b) const {
    printf("함수객체로 위임\n");
    return a + b;
  }
};

TEST(SampleTest, Sample) {
  NiceMock<MockCalc> mock;

  // 모의 객체의 연산의 결과를 다른 함수에게 위임할 수 있습니다.
  // 1. 함수
  ON_CALL(mock, Add(10, 20)).WillByDefault(&Add);

  // 2. 함수 객체
  ON_CALL(mock, Add(30, 40)).WillByDefault(Functor());

  // 3. 람다 - C++11
  ON_CALL(mock, Add(40, 50)).WillByDefault([](int a, int b) {
    printf("람다로 위임\n");
    return a + b;
  });

  std::cout << mock.Add(10, 20) << std::endl;
  std::cout << mock.Add(30, 40) << std::endl;
  std::cout << mock.Add(40, 50) << std::endl;
}
