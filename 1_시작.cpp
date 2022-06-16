
// 1_시작.cpp

// 1. Google Test Framework
//  1.7: Google Test + Google Mock
//  1.10: 구글 테스트 프레임워크 용어 정리(변경)
//    1.10 이전: xUnit Test Framework이 사용하는 용어와
//               Google Test Framework이 사용하는 용어가
//               차이가 있었습니다.

//  xUnit Test Framework  / Google Test 1.10 이전
//    Test Suite          / Test Case
//    - Test Case         / - Test
//    - Test Case         / - Test
//    - Test Case         / - Test
//    Test Suite
//    - Test Case
//    - Test Case
//    - Test Case

// 2. 구글 테스트 프레임워크를 사용하는 방법.
#include <gtest/gtest.h>

#define SPEC(message) printf(message "\n")

// 3. main을 직접 제공할 필요가 없다면, gtest_main 이용한다.
// 4. Test Case를 추가하는 방법
//    - TEST(TestSuiteName, TestCaseName)
// 5. 테스트는 실패하지 않으면, 항상 성공을 줍니다.
// 6. 테스트가 실패할 경우, 코드를 보지 않아도 실패의 원인을 쉽게
//    파악할수 있어야 합니다.
//     1) 실패의 원인을 반드시 명시해야 합니다.
//     2) 테스트의 이름이 테스트의 시나리오를 나타내야 합니다.
//        => 테스트대상클래스_시나리오_기대값

// TestSuiteName.TestCaseName
TEST(TestSuiteName, TestCaseName)
{
	SPEC("이미지 프로세서 안에서 이미지 리사이즈를 했을 경우 리사이즈가 제대로 수행되는지 검증한다.");
	// TODO: 작성 중입니다.
	//  > 명시적인 실패를 하는 것이 좋습니다.
	//  => "잊혀진 테스트"

	// - 테스트를 명시적으로 실패하는 방법
	// FAIL();
	FAIL() << "작성 중입니다.";
}

// ImageProcessor.ResizeImage
TEST(ImageProcessor, ResizeImage)
{
}

// ImageProcessor.BlurImage
TEST(ImageProcessor, BlurImage)
{
}
