#include <gtest.h>
#include "skiplist.h"

TEST(SkipList, CanMakeEmptyDefaultSkipList) {
	ASSERT_NO_THROW(SkipList<int> list);
}
TEST(SkipList, CanMakeEmptySkipListWithGivenMaxLevel) {
	ASSERT_NO_THROW(SkipList<int> list(2));
}
TEST(SkipList, CanAddNewElement) {
	SkipList<int> list(2);
	ASSERT_NO_THROW(list.insertElement(1));
}
TEST(SkipList, EmptyListHasZeroSize) {
	SkipList<int> list(2);
	EXPECT_EQ(0, list.getSize());
}
TEST(SkipList, CanFindTheElementInTheList) {
	SkipList<int> list(2);
	list.insertElement(1);
	list.insertElement(2);
	list.insertElement(3);
	list.insertElement(4);
	EXPECT_TRUE(list.searchElement(3));
}
TEST(SkipList, CanDeleteTheElementFromTheList) {
	SkipList<int> list(2);
	list.insertElement(1);
	list.insertElement(2);
	list.insertElement(3);
	list.insertElement(4);
	ASSERT_NO_THROW(list.deleteElement(3));
}
TEST(SkipList, CantFindNonexistentElement) {
	SkipList<int> list(2);
	list.insertElement(1);
	list.insertElement(2);
	list.insertElement(3);
	list.insertElement(4);
	EXPECT_FALSE(list.searchElement(5));
}
TEST(SkipList, CantFindDeletedElement) {
	SkipList<int> list(2);
	list.insertElement(1);
	list.insertElement(2);
	list.insertElement(3);
	list.insertElement(4);
	list.deleteElement(3);
	EXPECT_FALSE(list.searchElement(3));
}
TEST(SkipList, SizeIncreasesAfterAddingElement) {
	SkipList<int> list(2);
	list.insertElement(1);
	list.insertElement(2);
	list.insertElement(3);
	list.insertElement(4);
	EXPECT_EQ(4, list.getSize());
}
TEST(SkipList, SizeDecreasesAfterDeletingElement) {
	SkipList<int> list(2);
	list.insertElement(1);
	list.insertElement(2);
	list.insertElement(3);
	list.insertElement(4);
	list.deleteElement(3);
	EXPECT_EQ(3, list.getSize());
}
TEST(SkipList, CantDeleteNonexistentElement) {
	SkipList<int> list(2);
	list.insertElement(1);
	list.insertElement(2);
	list.insertElement(3);
	list.insertElement(4);
	list.deleteElement(5);
	EXPECT_EQ(4, list.getSize());
}