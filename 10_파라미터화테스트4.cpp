
// 데이터를 정적으로 정의하는 것이 아니라, 파일에서 로드해서 처리하고 싶다.
#include <gtest/gtest.h>
#include <string>
#include <vector>

class StringTest : public testing::TestWithParam<std::string>
{
};

// 데이터 셋을 로드하는 함수를 만들어줍니다.
std::vector<std::string> LoadFromFile()
{
  std::vector<std::string> v;

  // ./a.out < data.txt
  while (!std::cin.eof())
  {
    std::string input;
    std::cin >> input;

    v.push_back(input);
  }

  return v;
}

INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
                         testing::ValuesIn(LoadFromFile()));

TEST_P(StringTest, LoadTest)
{
  std::string s = GetParam();
  std::cout << s << std::endl;
}
