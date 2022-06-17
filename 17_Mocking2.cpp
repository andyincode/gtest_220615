// 17_Mocking2.cpp

#include <gmock/gmock.h>

struct Element
{
};

class Calc
{
public:
  virtual ~Calc() {}

  // 검증 대상 X
  virtual int Add(Element x)
  {
    std::cout << "Add(Element x)" << std::endl;
  }

  // 검증 대상 O
  virtual int Add(int times, Element x)
  {
    std::cout << "Add(int times, Element x)" << std::endl;
  }
};

void Process(Calc *p)
{
  p->Add(Element());
  p->Add(10, Element());
}

bool operator==(const Element &a, const Element &b) { return true; }

class MockCalc : public Calc
{
public:
  MOCK_METHOD(int, Add, (int times, Element x), (override));

  // 명시적으로 동일한 이름을 가지는 오버로딩 함수를 사용한다.라고 해야 합니다.
  using Calc::Add;
};

TEST(CalcTest, Sample)
{
  MockCalc calc;

  // EXPECT_CALL(calc, Add(10, Element()));
  calc.Add(10, Element());

  // 모의객체에서 Mocking한 함수 중에 오버로딩 함수는 가려지는 현상이 있습니다.
  calc.Add(Element());

  Process(&calc);
}