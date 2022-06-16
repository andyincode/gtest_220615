// 10_파라미터화테스트5.cpp

#include <gtest/gtest.h>

#if 0
class SampleTest : public testing::TestWithParam<std::string>
{
};

// 데이터 셋을 정의할 때 사용하는 함수
// 1. testing::Values
// INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest, testing::Values("hello", "world"));

// 2. testing::ValuesIn
std::string data[] = {"hello", "world"};
INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest, testing::ValuesIn(data));
#endif

// 3. testing::Combine
enum Color
{
  BLACK = 100,
  RED,
  WHITE,
};

const char *cars[] = {"Sonata", "Avante", "Genesis"};

// Combine 하고자 하는 데이터를 tuple로 묶어서 전달해야 합니다.
class CarTest : public testing::TestWithParam<std::tuple<const char *, Color>>
{
};

INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
                         testing::Combine(testing::ValuesIn(cars),
                                          testing::Values(BLACK, RED, WHITE)));

TEST_P(CarTest, Sample)
{
  std::tuple<const char *, Color> data = GetParam();

  const char *car = std::get<0>(data);
  Color color = std::get<1>(data);

  std::cout << car << ", " << color << std::endl;
}

// 4. testing::Range
// : 정수 값을 범위 안에서 생성할 때 사용할 수 있습니다.
class SampleTest : public testing::TestWithParam<int>
{
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
                         testing::Range(0, 100, 10)); // [0, 100)

TEST_P(SampleTest, Range)
{
  std::cout << GetParam() << std::endl;
}