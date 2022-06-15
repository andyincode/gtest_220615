
// 1. 헤더 파일을 포함
#include <gtest/gtest.h>

// 2. main을 제공해주어야 합니다.
int main(int argc, char** argv)
{
	// 3. Google Test 라이브러리 초기화
	testing::InitGoogleTest(&argc, argv);

	// 4. 작성한 테스트를 수행합니다.
	return RUN_ALL_TESTS();
}
