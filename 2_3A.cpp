
// SUT: System Under Test
//  => 테스트 대상 시스템
//  => CUT(Class/Code Under Test)
class Calc {
public:
	double Display() { return 0; }

	void Enter(double n) {}
	void PressPlus() {}
	void PressEquals() {}
};
// #include "Calc.h"


// 2_3A.cpp
#include <gtest/gtest.h>

// TEST(TestSuiteName, TestCaseName)
// 1. TestSuite Name
//  > 테스트 스위트의 이름은 테스트 대상 클래스(모듈)의 이름의
//    마지막에 Test 또는 Spec 접미를 사용합니다.
//              Calc -> CalcTest / CalcSpec
//    ImageProcessor -> ImageProcessorTest / ImageProcessorSpec
//
// 2. TestCase를 구성하는 방법 - 3A
//    1) Arrange: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고 준비합니다.
//    2) Act: 테스트 대상 코드에 작용을 가한다.(함수를 호출한다)
//    3) Assert: 기대하는 바를 단언한다.

TEST(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour) {
	// 1. Arrange
	Calc* calc = new Calc;

	// 2. Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// 3. Assert
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL();
	}
}
















