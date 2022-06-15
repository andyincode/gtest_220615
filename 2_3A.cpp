
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
//
// 3. 테스트 코드 품질
//    1) 가독성
//     - 테스트케이스의 시나리오가 제대로 드러나는가?
//     - 테스트케이스가 실패하였을 때 실패의 원인이 쉽게 드러나는가?
//    2) 유지보수성
//     - 테스트케이스에서 오류가 발생할 수 없는 형태의 코드를 지향해야 합니다.
//      > 제어 구문(조건문, 반복문, 예외 처리 등) 검증
//      > 테스트케이스 코드 안에서 제어 구문을 지양해야 합니다.
//    3)


TEST(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour) {
	// 1. Arrange
	Calc* calc = new Calc;

	// 2. Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// 3. Assert
/*
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		// FAIL();
		FAIL() << "2+2를 하였을 때 4가 나오지 않음.";
	}
*/
	// 위의 형태로 검증하는 것이 아니라, 단위 테스트 프레임워크가 제공하는
	// 단언문을 사용해야 합니다.
	//  => 함수, 매크로
	//  ASSERT_EQ / LT / GT / NE / LE / GE / NULL / NOT_NULL
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}
















