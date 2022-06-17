// 22_Matcher2.cpp
#include <gmock/gmock.h>

class Printer {
public:
  virtual ~Printer() {}

  virtual void Print(int n) = 0;
  virtual void Print(char c) = 0;
};

void Print(Printer *p) {
  p->Print(42);
  p->Print('A');
}

using testing::An;
using testing::Matcher;
using testing::TypedEq;

class MockPrinter : public Printer {
public:
  MOCK_METHOD(void, Print, (int n), (override));
  MOCK_METHOD(void, Print, (char c), (override));
};

TEST(PrinterTest, Print) {
  MockPrinter mock;

  // 컴파일 오류가 발생합니다.
  // EXPECT_CALL(mock, Print(42));
  // EXPECT_CALL(mock, Print('A'));

  // 1. TypedEq
  EXPECT_CALL(mock, Print(TypedEq<int>(42)));
  EXPECT_CALL(mock, Print(TypedEq<char>('A')));

  // 2. Matcher<int> / Matcher<char>
  EXPECT_CALL(mock, Print(Matcher<int>(42)));
  EXPECT_CALL(mock, Print(Matcher<char>('A')));

  // 3. An
  EXPECT_CALL(mock, Print(An<int>()));
  EXPECT_CALL(mock, Print(An<char>()));

  Print(&mock);
}