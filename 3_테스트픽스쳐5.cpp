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

// ImageProcessorTest* test = new ImageProcessorTest;
// ImageProcessorTest.ResizeImage
//  SetUp()
//  TearDown()
// ImageProcessorTest.BlurImage
//  SetUp()
//  TearDown()
// delete test;