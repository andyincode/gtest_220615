
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

// 1. Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해 준비해야 하는 모든 것을
//        테스트 픽스쳐라고 합니다.
//        => 테스트 픽스쳐를 구성하는 모든 로직 부분을 "픽스쳐 설치(Setup)"라고 부릅니다.

// 2. Test Fixture 설치 방법
//   1) Inline Fixture Setup
//   : 모든 픽스쳐 설치를 테스트케이스 안에서 수행한다.
//   장점: 픽스쳐를 설치하는 과정과 검증의 로직이 하나의 테스트 케이스 함수 안에서
//         존재하기 때문에 인과 관계를 쉽게 분석할 수 있다.
//   단점: 모든 테스트 코드 안에서 "코드 중복"이 발생합니다.
//      > "테스트 코드 중복" - 테스트 냄새(Smells)
//         : 테스트 코드의 가독성을 떨어 뜨리거나, 테스트 코드의 유지보수성을 떨어뜨리거나
//           테스트 코드의 신뢰성을 떨어 뜨릴 수 있습니다.

TEST(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour)
{
	// 1. Arrange
	Calc *calc = new Calc;
	double expected = 4;

	// 2. Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// 3. Assert
	ASSERT_EQ(calc->Display(), expected) << "2 + 2 하였을 때";
}

TEST(CalcTest, PressMinus)
{
	Calc *calc = new Calc;

	calc->Enter(2);
	calc->PressMinus();
	calc->Enter(2);
	calc->PressEquals();

	ASSERT_EQ(calc->Display(), 0) << "2 - 2";
}
