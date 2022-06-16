// 3_테스트픽스쳐5.cpp

#include <stdio.h>

class ImageProcessor
{
public:
  ImageProcessor() { printf("ImageProcessor()\n"); }
  ~ImageProcessor() { printf("~ImageProcessor()\n"); }
};

#include <gtest/gtest.h>

// TEST_F: 반드시 사용자가 명시적인 Test Suite 클래스를 제공해야 합니다.
class ImageProcessorTest : public testing::Test
{
protected:
  void SetUp() override { printf("SetUp()\n"); }
  void TearDown() override { printf("TearDown()\n"); }
};

TEST_F(ImageProcessorTest, ResizeImage) {}
TEST_F(ImageProcessorTest, BlurImage) {}
