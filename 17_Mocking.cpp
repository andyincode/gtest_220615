#include <gmock/gmock.h>
// 이 안에 gtest에 대한 의존성이 존재하기 때문에
// <gtest/gtest.h>를 포함할 필요가 없습니다.

struct MP3
{
  virtual ~MP3() {}

  virtual void Play() = 0;
  virtual void Stop(int n) = 0;

  virtual std::string GetName() const = 0;
  virtual void Foo() const noexcept = 0;

  virtual std::pair<bool, int> GetPair() const = 0;
  virtual bool CheckMap(std::map<int, double> a, bool b) const = 0;
};

// 아래 처럼 작성해야 합니다.
class MockMP3 : public MP3
{
public:
  // 주의사항: 템플릿 타입 인자가 2개 이상인 경우, 괄호 처리가 필요합니다.
  // bool CheckMap(std::map<int, double> a, bool b) const override
  MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (const, override));

  // std::pair<bool, int> GetPair() const override
  MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));

  // void Foo() const noexcept override
  MOCK_METHOD(void, Foo, (), (const, noexcept, override));

  // std::string GetName() const override
  MOCK_METHOD(std::string, GetName, (), (const, override));

  // void Play() override {}
  MOCK_METHOD(void, Play, (), (override));

  // void Stop(int n) override {}
  MOCK_METHOD(void, Stop, (int n), (override));
};

// 모의 객체가 잘 생성되는지 확인해야 합니다.
TEST(MP3Test, Sample)
{
  MockMP3 mp3; // !!!!!
}

// 1.10 이전의 방법입니다.
#if 0
class MockMP3 : public MP3
{
public:
  MOCK_METHOD0(Play, void());
  MOCK_METHOD1(Stop, void(int));
};
#endif