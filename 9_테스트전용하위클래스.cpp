
#include <stdio.h>

class Engine
{
public:
  Engine() {}
  virtual ~Engine() {}
  // 가상 소멸자: 상속이 가능한 클래스

  virtual void Start()
  {
    printf("Engine Start\n");
  }
};

class Car
{
  Engine *engine;

public:
  Car(Engine *p) : engine(p) {}

  void Go()
  {
    // ...
    // engine->Start();
    // ...
  }
};

#include <gtest/gtest.h>

// Car의 Go가 호출되었을 때, Engine의 Start가 제대로 되었는지 확인하고 싶다.
//  문제점: SUT의 상태를 확인하는 기능이 제공되고 있지 않습니다.
TEST(CarTest, Go)
{
  Engine engine;
  Car car(&engine);

  car.Go();

  // !!!!!
}
// 해결 방법: 테스트 전용 하위 클래스 패턴(Test Specific Subclass Pattern)
//  의도: SUT의 클래스에 테스트를 위한 기능이 제공되지 않을 때,
//       SUT의 하위 클래스를 만들어서 해당 기능을 제공하는 방법입니다.
//     => SUT의 코드를 변경하지 않고, 테스트되지 않은 요구사항을 검증할 수 있습니다.
class TestEngine : public Engine
{
  bool isStart = false;

public:
  void Start() override
  {
    Engine::Start(); // 부모의 동작을 그대로 수행합니다.
    isStart = true;
  }

  bool IsStart() const { return isStart; }
};

TEST(CarTest, Go2)
{
  TestEngine engine;
  Car car(&engine);

  car.Go();

  EXPECT_TRUE(engine.IsStart()) << "자동차가 Go 하였을 때";
}