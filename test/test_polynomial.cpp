#include <gtest.h>
#include "polynomial.h"

TEST(Polynomial, CanMakeEmptyPolynomial) {
	ASSERT_NO_THROW(Polynomial<int> pol);
}
TEST(Polynomial, CanMakePolynomialOutOfMonomial) {
	Monomial<int> mon(2, "012");
	ASSERT_NO_THROW(Polynomial<int> pol(mon));
}
TEST(Polynomial, EmptyPolynomialHasNoValues) {
	Polynomial<int> pol;
	EXPECT_TRUE(pol.IsEmpty());
}
TEST(Polynomial, EmptyPolynomialIsNullPolynomial) {
	Polynomial<int> pol;
	EXPECT_TRUE(pol.IsNull());
}
TEST(Polynomial, PolynomialOutOfMonomialIsNotEmpty) {
	Monomial<int> mon(2, "012");
	Polynomial<int> pol(mon);
	EXPECT_FALSE(pol.IsEmpty());
}
TEST(Polynomial, PolynomialOutOfMonomialWithZeroCoefficientIsNullPolynomial) {
	Monomial<int> mon(0, "012");
	Polynomial<int> pol(mon);
	EXPECT_TRUE(pol.IsNull());
}
TEST(Polynomial, CanInsertMonomialIntoEmptyPolynomial) {
	Polynomial<int> pol;
	Monomial<int> mon(2, "012");
	pol.PushFront(mon);
	EXPECT_FALSE(pol.IsEmpty());
}
TEST(Polynomial, CanInsertMonomialIntoNotEmptyPolynomial) {
	Monomial<int> mon1(4, "132");
	Polynomial<int> pol(mon1);
	Monomial<int> mon2(2, "012");
	pol.PushFront(mon2);
	EXPECT_EQ(2, pol.GetSize());
}
TEST(Polynomial, CanGetMonomialFromGivenIndexOfPolynomial) {
	Monomial<int> mon1(4, "132");
	Polynomial<int> pol(mon1);
	Monomial<int> mon2(2, "012");
	pol.PushFront(mon2);
	Monomial<int> mon3 = pol[1];
	bool result = mon1 == mon3;
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanMakePolynomialOutOfListOfMonomials) {
	ForwardList<Monomial<int>> list;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "532");
	Monomial<int> mon3(6, "001");
	Monomial<int> mon4(-3, "240");
	list.PushFront(mon1);
	list.PushFront(mon2);
	list.PushFront(mon3);
	list.PushFront(mon4);
	ASSERT_NO_THROW(Polynomial<int> pol(list));
}
TEST(Polynomial, PolynomialOutOfListOfMonomialsHasCorrectValues) {
	ForwardList<Monomial<int>> list;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "532");
	Monomial<int> mon3(6, "001");
	Monomial<int> mon4(-3, "240");
	list.PushFront(mon1);
	list.PushFront(mon2);
	list.PushFront(mon3);
	list.PushFront(mon4);
	Polynomial<int> pol(list);
	bool mistake = false;
	for (size_t i = 0; i < pol.GetSize(); i++) {
		if (pol[i] != list[i]) {
			mistake = true;
			break;
		}
	}
	EXPECT_FALSE(mistake);
}
TEST(Polynomial, PushedMonomialWithDegreePresentInPolynomialOverridesIt) {
	ForwardList<Monomial<int>> list;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "532");
	Monomial<int> mon3(6, "001");
	Monomial<int> mon4(-3, "240");
	list.PushFront(mon1);
	list.PushFront(mon2);
	list.PushFront(mon3);
	list.PushFront(mon4);
	Polynomial<int> pol(list);
	Monomial<int> mon5(99, "001");
	pol.PushFront(mon5);
	EXPECT_EQ(99, pol[1].GetCoefficient());
}
TEST(Polynomial, CanMakeEqualPolynomial) {
	ForwardList<Monomial<int>> list;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "532");
	Monomial<int> mon3(6, "001");
	Monomial<int> mon4(-3, "240");
	list.PushFront(mon1);
	list.PushFront(mon2);
	list.PushFront(mon3);
	list.PushFront(mon4);
	Polynomial<int> pol1(list);
	Polynomial<int> pol2 = pol1;
	bool result = (pol1 == pol2);
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanAddTwoPolynomialsWithSameDegreesOfMonoms) {
	Polynomial<int> pol1, pol2, pol3, pol4;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "240");
	Monomial<int> mon3(6, "132");
	Monomial<int> mon4(-3, "240");
	pol1.PushFront(mon1);
	pol1.PushFront(mon2);
	pol2.PushFront(mon3);
	pol2.PushFront(mon4);
	pol3 = pol1 + pol2;
	Monomial<int> mon_res1(10, "132");
	Monomial<int> mon_res2(-1, "240");
	pol4.PushFront(mon_res1);
	pol4.PushFront(mon_res2);
	bool result = pol3 == pol4;
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanSubtractTwoPolynomialsWithSameDegreesOfMonoms) {
	Polynomial<int> pol1, pol2, pol3, pol4;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "240");
	Monomial<int> mon3(6, "132");
	Monomial<int> mon4(-3, "240");
	pol1.PushFront(mon1);
	pol1.PushFront(mon2);
	pol2.PushFront(mon3);
	pol2.PushFront(mon4);
	pol3 = pol1 - pol2;
	Monomial<int> mon_res1(-2, "132");
	Monomial<int> mon_res2(5, "240");
	pol4.PushFront(mon_res1);
	pol4.PushFront(mon_res2);
	bool result = pol3 == pol4;
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanAddTwoPolynomialsWithDifferentDegreesOfMonoms) {
	Polynomial<int> pol1, pol2, pol3, pol4;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "240");
	pol1.PushFront(mon1);
	pol2.PushFront(mon2);
	pol3 = pol1 + pol2;
	Monomial<int> mon_res1(4, "132");
	Monomial<int> mon_res2(2, "240");
	pol4.PushFront(mon_res1);
	pol4.PushFront(mon_res2);
	bool result = pol3 == pol4;
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanSubtractTwoPolynomialsWithDifferentDegreesOfMonoms) {
	Polynomial<int> pol1, pol2, pol3, pol4;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "240");
	pol1.PushFront(mon1);
	pol2.PushFront(mon2);

	pol3 = pol1 - pol2;
	Monomial<int> mon_res1(4, "132");
	Monomial<int> mon_res2(-2, "240");
	pol4.PushFront(mon_res1);
	pol4.PushFront(mon_res2);
	bool result = pol3 == pol4;
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanAddTwoPolynomialsWithMixedDegreesOfMonoms) {
	Polynomial<int> pol1, pol2, pol3, pol4;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "240");
	Monomial<int> mon3(6, "132");
	Monomial<int> mon4(-3, "240");
	Monomial<int> mon5(24, "353");
	Monomial<int> mon6(-12, "235");
	pol1.PushFront(mon1);
	pol1.PushFront(mon2);
	pol2.PushFront(mon3);
	pol2.PushFront(mon4);
	pol1.PushFront(mon5);
	pol2.PushFront(mon6);
	pol3 = pol1 + pol2;
	Monomial<int> mon_res1(10, "132");
	Monomial<int> mon_res2(-1, "240");
	Monomial<int> mon_res3(24, "353");
	Monomial<int> mon_res4(-12, "235");
	pol4.PushFront(mon_res1);
	pol4.PushFront(mon_res2);
	pol4.PushFront(mon_res3);
	pol4.PushFront(mon_res4);
	bool result = pol3 == pol4;
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanSubtractTwoPolynomialsWithMixedDegreesOfMonoms) {
	Polynomial<int> pol1, pol2, pol3, pol4;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "240");
	Monomial<int> mon3(6, "132");
	Monomial<int> mon4(-3, "240");
	Monomial<int> mon5(24, "353");
	Monomial<int> mon6(-12, "235");
	pol1.PushFront(mon1);
	pol1.PushFront(mon2);
	pol2.PushFront(mon3);
	pol2.PushFront(mon4);
	pol1.PushFront(mon5);
	pol2.PushFront(mon6);
	pol3 = pol1 - pol2;
	Monomial<int> mon_res1(-2, "132");
	Monomial<int> mon_res2(5, "240");
	Monomial<int> mon_res3(24, "353");
	Monomial<int> mon_res4(12, "235");
	pol4.PushFront(mon_res1);
	pol4.PushFront(mon_res2);
	pol4.PushFront(mon_res3);
	pol4.PushFront(mon_res4);
	bool result = pol3 == pol4;
	EXPECT_TRUE(result);
}
TEST(Polynomial, CanMultiplyTwoPolynomials) {
	Polynomial<int> pol1, pol2, pol3, pol4;
	Monomial<int> mon1(4, "132");
	Monomial<int> mon2(2, "240");
	Monomial<int> mon3(6, "221");
	Monomial<int> mon4(-3, "103");
	pol1.PushFront(mon1);
	pol1.PushFront(mon2);
	pol2.PushFront(mon3);
	pol2.PushFront(mon4);
	pol3 = pol1 * pol2;
	Monomial<int> mon_res1(24, "353");
	Monomial<int> mon_res2(-12, "235");
	Monomial<int> mon_res3(12, "461");
	Monomial<int> mon_res4(-6, "343");
	pol4.PushFront(mon_res1);
	pol4.PushFront(mon_res2);
	pol4.PushFront(mon_res3);
	pol4.PushFront(mon_res4);
	bool result = pol3 == pol4;
	EXPECT_TRUE(result);
}
TEST(Polynomial, SolvingPolynomialInGivenPoint1) {
	Polynomial<int> pol;
	Monomial<int> mon1(3, "100");
	Monomial<int> mon2(7, "010");
	Monomial<int> mon3(-4, "001");
	Monomial<int> mon4(8, "000");
	pol.PushFront(mon1);
	pol.PushFront(mon2);
	pol.PushFront(mon3);
	pol.PushFront(mon4);
	EXPECT_EQ(15, pol.CalculateInPoint(2, 3, 5));
}
TEST(Polynomial, SolvingPolynomialInGivenPoint2) {
	Polynomial<int> pol;
	Monomial<int> mon1(3, "200");
	Monomial<int> mon2(13, "100");
	Monomial<int> mon3(4, "000");
	pol.PushFront(mon1);
	pol.PushFront(mon2);
	pol.PushFront(mon3);
	EXPECT_EQ(0, pol.CalculateInPoint(-4, 0, 0));
} 
TEST(Polynomial, SolvingPolynomialInGivenPoint3) {
	Monomial<int> mon2(51, "013");
	Polynomial<int> pol;
	Monomial<int> mon1(43, "220");
	Monomial<int> mon3(25, "121");
	pol.PushFront(mon1);
	pol.PushFront(mon2);
	pol.PushFront(mon3);
	EXPECT_EQ(26207676, pol.CalculateInPoint(21, -34, 12));
}