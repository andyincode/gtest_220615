// 12_테스트대역.cpp
// : Test Double
// => 반드시 이해해야 합니다.

#include <string>

class FileSystem
{
public:
  virtual ~FileSystem() {}

  virtual bool IsValid(const std::string &filename)
  {
    // 현재의 파일 시스템에서 적합한 이름인지 여부를 판단합니다.
    return false;
  }
};

// Logger -----<> FileSystem

// Logger -----<> TestDouble: FileSystem
//                   IsValid: 무조건 true를 반환합니다.

// 문제점: 테스트 대역은 제품 코드의 설계가 테스트 대역을 적용할 수 있어야 합니다.

class Logger
{
public:
  // log 파일은 확장자를 제외한 파일의 이름이 반드시 5글자 이상이어야 한다.
  // file.log
  bool IsValidLogFilename(const std::string &filename)
  {
    //--------------------
    size_t index = filename.find_last_of(".");
    std::string name = filename.substr(0, index);
    if (name.size() < 5)
    {
      return false;
    }
    //--------------------

    // 파일 시스템에서 체크해야 합니다.
    FileSystem fs;
    return fs.IsValid(filename);
  }
};

#include <gtest/gtest.h>

TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue)
{
  Logger logger;
  std::string validFilename = "valid_file.log";

  EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
  Logger logger;
  std::string invalidFilename = "bad.log";

  EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}