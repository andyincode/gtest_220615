// 12_테스트대역2.cpp
#include <string>

// 문제점: 테스트 대역은 제품 코드의 설계가 테스트 대역을 적용할 수 있어야 합니다.
//      => '강한 결합'이 아닌 '약한 결합'이 형성되어야 합니다.
//   강한 결합: 협력 객체(FileSystem)를 사용할 때, 구체적인 타입에 의존합니다.
//   약한 결합: 협력 객체(FileSystem)를 사용할 때, 인터페이스나 추상 클래스 타입에 의존합니다.
//       - 교체 가능한 설계
//       - 협력 객체를 직접 생성하는 것이 아니라, 외부에서 생성해서 전달 받아야 합니다.
//        : 의존성 주입(Dependency Injection)
//        1) 생성자 전달
//          - 협력 객체가 필수적일 때
//        2) 메소드 전달
//          - 협력 객체가 필수적이지 않을 때

struct IFileSystem
{
  virtual ~IFileSystem() {}

  virtual bool IsValid(const std::string &filename) = 0;
};

class FileSystem : public IFileSystem
{
public:
  bool IsValid(const std::string &filename) override
  {
    // 현재의 파일 시스템에서 적합한 이름인지 여부를 판단합니다.
    return false;
  }
};

class Logger
{
  IFileSystem *fs;

public:
  Logger(IFileSystem *p = nullptr) : fs(p)
  {
    // 기존 코드가 깨지지 않도록 하고 싶습니다.
    if (!fs)
    {
      fs = new FileSystem;
    }
  }

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
    // FileSystem fs;
    // return fs.IsValid(filename);

    return fs->IsValid(filename);
  }
};

#include <gtest/gtest.h>

// Logger ---------<>     IFileSystem
//                             |
//                      ----------------
//                      |              |
//                FileSystem     TestDoubleFileSystem

class TestDoubleFileSystem : public IFileSystem
{
public:
  bool IsValid(const std::string &filename) override { return true; }
};

TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue)
{
  TestDoubleFileSystem fs;
  Logger logger(&fs);
  std::string validFilename = "valid_file.log";

  EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
  TestDoubleFileSystem fs;
  Logger logger(&fs);
  std::string invalidFilename = "bad.log";

  EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}