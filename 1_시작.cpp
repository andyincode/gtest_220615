
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

// 3. main을 직접 제공할 필요가 없다면, gtest_main 이용한다.
// 4. Test Case를 추가하는 방법
//    - TEST
TEST(TestSuiteName, TestCaseName)
{

}

TEST(ImageProcessor, ResizeImage)
{

}

TEST(ImageProcessor, BlurImage)
{

}















