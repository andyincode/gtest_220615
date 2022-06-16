// 10_파라미터화테스트3.cpp

#include <string>

bool foo(int arg1, const std::string &name)
{
  return arg1 > name.size();
}

#include <gtest/gtest.h>

struct Input
{
  int arg1;
  std::string name;
};

class SampleTest : public testing::TestWithParam<Input>
{
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
                         testing::Values(Input{10, "Tom"}, Input{2, "Bob"}, Input{3, "A"}));

// 사용자 정의 타입이 구글 테스트에서 제대로 출력되도록 만들기 위해서는
// 사용자 정의 출력 방법을 직접 제공해주어야 합니다.
std::ostream &operator<<(std::ostream &os, const Input &input)
{
  return os << "Input{arg1=" << input.arg1 << ", name=" << input.name << "}";
}

TEST_P(SampleTest, foo)
{
  Input input = GetParam();

  std::cout << input.arg1 << ", " << input.name << std::endl;
  EXPECT_TRUE(foo(input.arg1, input.name));
}