// 7_비기능테스트.cpp
// 정의: 기능적인 부분 뿐 아니라 성능이나 메모리 등의 비기능적인 부분을 검증합니다.
// 1) 사용자 정의 단언문을 제공합니다.
// 2) TestSuite 클래스를 통해서 처리합니다.

#include <string>
#include <unistd.h>

void OpenFile(const std::string &filename)
{
  sleep(2);
}

#include <gtest/gtest.h>

#define EXPECT_TIMEOUT(fn, limit)          \
  do                                       \
  {                                        \
    time_t limitSeconds = limit;           \
    time_t startTime = time(0);            \
    fn;                                    \
    time_t duration = time(0) - startTime; \
    EXPECT_LE(duration, limitSeconds);     \
  } while (0)

TEST(OpenFileTest, OpenFile2)
{
  EXPECT_TIMEOUT(OpenFile("sample.txt"), 1);
}

// OpenFile이 1초 안에 수행되는지 여부를 검증하고 싶다.
TEST(OpenFileTest, OpenFile)
{
  time_t limitSeconds = 1;
  time_t startTime = time(0);
  OpenFile("sample.txt");
  time_t duration = time(0) - startTime;

  EXPECT_LE(duration, limitSeconds);
}
