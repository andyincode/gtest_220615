// 3_테스트픽스쳐5.cpp

#include <gtest/gtest.h>

// TEST_F: 반드시 사용자가 명시적인 Test Suite 클래스를 제공해야 합니다.
class ImageProcessorTest : public testing::Test
{
protected:
  ImageProcessorTest() { printf("ImageProcessorTest()\n"); }
  ~ImageProcessorTest() { printf("~ImageProcessorTest()\n"); }

  void SetUp() override { printf("SetUp()\n"); }
  void TearDown() override { printf("TearDown()\n"); }
};

TEST_F(ImageProcessorTest, ResizeImage) {}
TEST_F(ImageProcessorTest, BlurImage) {}
TEST_F(ImageProcessorTest, BlurImage2) {}

// 1. TestSuite 클래스의 객체는 모든 TestCase 마다 새롭게 생성되고 파괴됩니다.
//  => xUnit Test Framework은 "신선한 픽스쳐의 전략"을 사용하고 있습니다.
//  => 픽스쳐가 이전의 테스트케이스를 통해서 문제가 생겨도, 이후의 테스트케이스에는 영향을 주지 않는
//     전략입니다.
//  => 테스트는 독립적으로 구성될 수 있습니다.

// 2. 테스트케이스를 구성하는 방법
//   xUnit Test Pattern => 4단계 테스트 패턴(Four Phase Test Pattern)
//   1단계: 테스트 픽스처를 설치하거나 실제 결과를 관찰하기 위해 필요하는 것을 설정하는 작업(테스트 대역 주입)을 수행합니다.
//         => SetUp()
//   2단계: SUT와 상호작용 합니다.  => TestBody()
//   3단계: 기대 결과를 확인합니다.  => TestBody()
//   4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓습니다.
//        => TearDown()

// 3. Test Suite
//  : A test suite is a set of tests that all share the same fixture
//  => 동일한 픽스쳐를 공유하는 테스트 케이스의 집합입니다.

// ImageProcessorTest* test = new ImageProcessorTest;
// ImageProcessorTest.ResizeImage
//  test->SetUp()
//  test->TearDown()
// delete test;

// ImageProcessorTest* test = new ImageProcessorTest;
// ImageProcessorTest.BlurImage
//  test->SetUp()
//  test->TearDown()
// delete test;
