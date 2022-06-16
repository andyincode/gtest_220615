
class Calc
{
public:
	// Calc(double n) {} // !!

	double Display() { return -1; }

	void Enter(double n) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

#include <gtest/gtest.h>

//  2) Delegate Setup(위임 설치)
//    : 픽스쳐 설치에 관한 코드를 별도의 함수를 통해 캡슐화 합니다.
//     => "테스트 유틸리티 함수"
//     => 명시적인 테스트 스위트를 클래스를 제공하고,
//        TEST_F를 통해서 테스트 케이스를 만들어야 합니다.

// TestSuite 클래스를 만드는 방법
//  => testing::Test의 자식 클래스로 제공하면 됩니다.
class CalcTest : public testing::Test
{
protected:
	void foo() { printf("CalcTest::foo\n"); }

	Calc *CreateCalc() { return new Calc; }
};

TEST_F(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour)
{
	foo();

	// 1. Arrange
	// Calc* calc = new Calc;
	Calc *calc = CreateCalc();
	double expected = 4;

	// 2. Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// 3. Assert
	ASSERT_EQ(calc->Display(), expected) << "2 + 2 하였을 때";
}

TEST_F(CalcTest, PressMinus)
{
	foo();

	// Calc* calc = new Calc;
	Calc *calc = CreateCalc();

	calc->Enter(2);
	calc->PressMinus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 0) << "2 - 2";
}
