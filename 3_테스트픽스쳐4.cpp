#include <stdio.h>
class Calc
{
public:
	// Calc(double n) {} // !!

	~Calc()
	{
		printf("Calc 메모리 해지\n");
	}

	double Display() { return 0; }

	void Enter(double n) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
};

#include <gtest/gtest.h>

// 2. Test Fixture 설치 방법
//  3) Implicit Setup(암묵적인 설치/해체)
//  => xUnit Test Framework이 제공하는 기능입니다.
//  => 여러 테스트케이스에서 같은 테스트 픽스쳐 설치와 해체의 코드를 암묵적으로 호출되는
//     함수를 통해서 처리합니다.
//  장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 캡슐화할 수 있습니다.
//  단점: 픽스쳐 설치 코드가 테스트 케이스 밖에 존재하기 때문에,
//        테스트케이스 만으로 테스트 코드를 분석하기 어렵다.

// 3. ASSERT_XX
//  : 테스트 케이스 안에서 단언문이 실패하면, 이후의 코드는 수행되지 않습니다.
//  => 해결 방법: 암묵적인 해체

class CalcTest : public testing::Test
{
protected:
	Calc *calc;

public:
	// CalcTest의 TestCase의 공통의 픽스쳐 설치 로직을 작성하는 목적입니다.
	void SetUp() override
	{
		printf("CalcTest.SetUp()\n");
		calc = new Calc;
	}

	void TearDown() override
	{
		printf("CalcTest.TearDown()\n");
		delete calc;
	}
};

TEST_F(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour)
{
	// 1. Arrange
	// Calc* calc = new Calc;
	double expected = 4;

	// 2. Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// 3. Assert
	ASSERT_EQ(calc->Display(), expected) << "2 + 2 하였을 때";

	// delete calc;
}

TEST_F(CalcTest, PressMinus)
{
	// Calc* calc = new Calc;

	calc->Enter(2);
	calc->PressMinus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 0) << "2 - 2";

	// delete calc;
}
