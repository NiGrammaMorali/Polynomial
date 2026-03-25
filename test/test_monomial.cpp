#include <gtest.h>
#include "monomial.h"

TEST(Monomial, CanMakeEmptyMonomial) {
	ASSERT_NO_THROW(Monomial<int> mon);
}
TEST(Monomial, CanMakeMonomialWithGivenValues) {
	ASSERT_NO_THROW(Monomial<int> mon(2, "111"));
}
TEST(Monomial, CanReturnMonomialCoefficient) {
	Monomial<int> mon(2, "111");
	EXPECT_EQ(2 ,mon.GetCoefficient());
}
TEST(Monomial, CanReturnMonomialDegree) {
	Monomial<int> mon(2, "111");
	EXPECT_EQ("111", mon.GetDegree());
}
TEST(Monomial, EmptyMonomialHasNullValues) {
	Monomial<int> mon;
	std::pair<int, std::string> pair1(mon.GetCoefficient(), mon.GetDegree());
	std::pair<int, std::string> pair2(0, "000");
	EXPECT_EQ(pair1, pair2);
}
TEST(Monomial, CanMakeEqualMonomial) {
	Monomial<int> mon1(2, "111");
	Monomial<int> mon2 = mon1;
	EXPECT_TRUE(mon1 == mon2);
}
TEST(Monomial, DifferentMonomialsAreNotEqual) {
	Monomial<int> mon1(2, "111");
	Monomial<int> mon2(3, "012");
	EXPECT_TRUE(mon1 != mon2);
}
TEST(Monomial, CanMultiplyMonomialByNumber) {
	Monomial<int> mon(3, "012");
	mon *= 2;
	EXPECT_EQ(6, mon.GetCoefficient());
}
TEST(Monomial, CanAddTwoMonomialWithSameDegrees) {
	Monomial<int> mon1(2, "111");
	Monomial<int> mon2(3, "111");
	Monomial<int> mon3 = mon1 + mon2;
	EXPECT_EQ(5, mon3.GetCoefficient());
}
TEST(Monomial, CantAddTwoMonomialWithDifferentDegrees) {
	Monomial<int> mon1(2, "111");
	Monomial<int> mon2(3, "012");
	ASSERT_ANY_THROW(Monomial<int> mon3 = mon1 + mon2);
}
TEST(Monomial, CanSubtractTwoMonomialWithSameDegrees) {
	Monomial<int> mon1(2, "111");
	Monomial<int> mon2(3, "111");
	Monomial<int> mon3 = mon2 - mon1;
	EXPECT_EQ(1, mon3.GetCoefficient());
}
TEST(Monomial, CantSubtractTwoMonomialWithDifferentDegrees) {
	Monomial<int> mon1(2, "111");
	Monomial<int> mon2(3, "012");
	ASSERT_ANY_THROW(Monomial<int> mon3 = mon1 - mon2);
}
TEST(Monomial, CanMultipyTwoMonomials) {
	Monomial<int> mon1(4, "111");
	Monomial<int> mon2(3, "012");
	Monomial<int> mon3 = mon1 * mon2;
	std::pair<int, std::string> pair1(mon3.GetCoefficient(), mon3.GetDegree());
	std::pair<int, std::string> pair2(12, "123");
	EXPECT_EQ(pair1, pair2);
}
TEST(Monomial, CantMultipyTwoMonomialsIfResultingDegreeIsBiggerThanGiven) {
	Monomial<int> mon1(4, "473");
	Monomial<int> mon2(3, "568");
	ASSERT_ANY_THROW(Monomial<int> mon3 = mon1 * mon2);
}