
#include <gtest/gtest.h>
// new / delete 연산자를 재정의해야 합니다.
//  1. new
//     1) 메모리 할당 -* : void* operator new(size_t size)
//     2) 생성자 호출

// 2. delete
//     1) 소멸자 호출
//     2) 메모리 해지 -* : void operator delete(void* p, size_t)
class Image
{
public:
  void Draw()
  {
    printf("Draw Image...\n");
  }

  static int allocCount;

// 테스트 코드 상에서만 사용되는 코드는 조건부 컴파일을 통해 테스트 상에서 사용되도록 해야 합니다.
#ifdef GTEST_LEAK_TEST
  void *operator new(size_t size)
  {
    ++allocCount;
    return malloc(size);
  }

  void operator delete(void *p, size_t)
  {
    --allocCount;
    free(p);
  }
#endif
};

int Image::allocCount = 0;

bool DrawImage()
{
  Image *p = new Image;
  p->Draw();

  new Image;
  new Image;
  new Image;
  new Image;

  return true;
}

// 객체의 메모리 누수가 발생하는지 여부를 검증하고 싶다.
// 1) 제품 코드(SUT)에 미리 정의된 코드가 필요합니다.
// 2) TestSuite 클래스를 통해서 자동적으로 메모리 검사를 수행하도록 할 수 있습니다.
//   - SetUp
//   - TearDown

// DrawImage를 호출하였을 때, 메모리 해지가 제대로 되는지 검증하고 싶다.
#if 0
TEST(ImageTest, DrawImage)
{
  int allocCount = Image::allocCount;
  DrawImage();
  int diff = Image::allocCount - allocCount;

  EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
}
#endif

class ImageTest : public testing::Test
{
  int allocCount;

protected:
  void SetUp() override
  {
    allocCount = Image::allocCount;
  }

  void TearDown() override
  {
    int diff = Image::allocCount - allocCount;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
  }
};

TEST_F(ImageTest, DrawImage)
{
  EXPECT_TRUE(DrawImage());
}