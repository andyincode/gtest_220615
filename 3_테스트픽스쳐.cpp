
class Calc {
public:
	double Display() { return 0; }

	void Enter(double n) {}
	void PressPlus() {}
	void PressEquals() {}
};

#include <gtest/gtest.h>

TEST(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour) {
	// 1. Arrange
	Calc* calc = new Calc;
	double expected = 4;

	// 2. Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// 3. Assert
	ASSERT_EQ(calc->Display(), expected) << "2 + 2 하였을 때";
}
















