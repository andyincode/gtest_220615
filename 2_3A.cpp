
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
// 2. TestCase를 구성하는 방법 - 3A(TDD) / BDD
//    1) Arrange: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고
//    준비합니다. 2) Act: 테스트 대상 코드에 작용을 가한다.(함수를 호출한다) 3)
//    Assert: 기대하는 바를 단언한다.
//
// 3. 테스트 코드 품질
//    1) 가독성
//     - 테스트케이스의 시나리오가 제대로 드러나는가?
//     - 테스트케이스가 실패하였을 때 실패의 원인이 쉽게 드러나는가?
//    2) 유지보수성
//     - 테스트케이스에서 오류가 발생할 수 없는 형태의 코드를 지향해야 합니다.
//      > 제어 구문(조건문, 반복문, 예외 처리 등) 검증
//        : 테스트 유틸리티 함수를 통해서 별도 검증하고 사용해야 합니다.
//
//      > 테스트케이스 코드 안에서 제어 구문을 지양해야 합니다.
//    3) 신뢰성
//     - 테스트케이스의 결과를 신뢰할 수 있는가?
//        : 테스트의 결과가 간헐적으로 바뀐다.
//          테스트의 결과가 환경에 따라 변경된다.
//
// 5. BDD(Behavior Driven Development) => Google Test도 지원하는 기능입니다.
//  : 행위 주도 개발
//   1) 사용하는 용어에 차이점이 있습니다.
//     - 좀 더 사람과 가까운 용어를 사용하자.
//       Arrange -> Given
//       Act     -> When
//       Assert  -> Then
//   2) 상태 기반 검증 + 행위 기반 검증(Mock Framework)

TEST(SampleTest, foo) {
  // Arrange
  // Act
  // Assert
}

TEST(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour) {
  // 1. Arrange
  Calc *calc = new Calc;
  double expected = 4;
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
  //  ASSERT_EQ / LT / GT / NE / LE / GE / NULL / NOT_NULL / TRUE / FALSE ...
  // ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
  ASSERT_EQ(calc->Display(), expected) << "2 + 2 하였을 때";
  // ASSERT_EQ(expected, actual)
  //  - Google Test 1.10 이전에는 반드시 인자의 순서가 중요합니다.
}
