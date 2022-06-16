// 10_파라미터화테스트2.cpp

bool IsPrime(int value)
{
  for (int i = 2; i < value; i++)
  {
    if (value % 2 == 0)
      return false;
  }

  return true;
}

// 파라미터화 테스트 패턴(Parameterized Test Pattern)
// : xUnit Test Framework이 제공하는 기능입니다.
// 의도: 입력 데이터를 바꿔가며, 반복 검사하는 데이터 중심의 테스트에서
//      코드 중복을 제거하는 것이 가능합니다.