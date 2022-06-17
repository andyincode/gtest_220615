#include <gmock/gmock.h>

// Mocking
// 1. Interface
// 2. Class
// 3. Template Class

template <typename T>
struct StackInterface
{
  virtual ~StackInterface() {}

  virtual int GetSize() const = 0;
  virtual void Push(const T &x) = 0;
};

template <typename T>
class MockStack : public StackInterface<T>
{
public:
  MOCK_METHOD(int, GetSize, (), (const, override));
  MOCK_METHOD(void, Push, (const T &x), (override));
};

TEST(StackTest, UseStack)
{
  MockStack<int> mock;

  EXPECT_CALL(mock, GetSize);

  // mock.GetSize();
}