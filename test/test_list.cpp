#include <gtest.h>
#include "list.h"

TEST(List, CanMakeEmptyList) {
	ASSERT_NO_THROW(ForwardList<int> list);
}
TEST(List, TheEmptyListHasNoValues) {
	ForwardList<int> list;
	EXPECT_TRUE(list.IsEmpty());
}
TEST(List, CanPushNewValueInFront) {
	ForwardList<int> list;
	list.PushFront(1);
	EXPECT_EQ(list.Front(), 1);
}
TEST(List, CanPushNewValueInFrontManyValues) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	EXPECT_EQ(list.Front(), 2);
}
TEST(List, CanGetSizeOfList) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	EXPECT_EQ(list.size(), 5);
}
TEST(List, CanFindValueAfterFrontPushingManyValues) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	EXPECT_EQ(list[2], 7);
}
TEST(List, CanPushNewValueAfterAnother) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	list.PushAfter(2, 6);
	EXPECT_EQ(list[3], 6);
}
TEST(List, CanMakeEqualList) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	list.PushAfter(2, 6);
	ForwardList<int> list1 = list;
	EXPECT_EQ(list1, list);
}
TEST(List, CanEraseFrontValue) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	list.PopFront();
	EXPECT_EQ(list.Front(), 3);
}
TEST(List, CanEraseValueAfterAnother) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	list.PushFront(9);
	list.PushFront(8);
	list.EraseAfter(3);
	EXPECT_EQ(list[4], 4);
}
TEST(List, CantEraseFrontValueOfEmptyList) {
	ForwardList<int> list;
	ASSERT_ANY_THROW(list.PopFront());
}
TEST(List, CantEraseValueAfterLastValue) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	list.PushFront(9);
	list.PushFront(8);
	ASSERT_ANY_THROW(list.EraseAfter(6));
}
TEST(List, DifferentListsAreNotEqual) {
	ForwardList<int> list1, list2;
	list1.PushFront(1);
	list1.PushFront(4);
	list1.PushFront(7);
	list1.PushFront(3);
	list1.PushFront(2);
	list2 = list1;
	list2.PushFront(5);
	EXPECT_NE(list1, list2);
}
TEST(List, ListSwapWorks) {
	ForwardList<int> list1, list2, list3;
	list1.PushFront(1);
	list1.PushFront(4);
	list1.PushFront(7);
	list1.PushFront(3);
	list1.PushFront(2);
	list3 = list1;
	std::swap(list1, list2);
	EXPECT_NE(list1, list3);
}
TEST(List, CanSortList) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	list.PushFront(9);
	list.PushFront(8);
	list.Sort();
	const size_t size = list.size();
	vector<int> first = {1, 2, 3, 4, 7, 8, 9};
	vector<int> second(size);
	for (size_t i = 0; i < size; i++) {
		second[i] = list[i];
	}
	EXPECT_EQ(first, second);
}
TEST(List, CanClearList) {
	ForwardList<int> list;
	list.PushFront(1);
	list.PushFront(4);
	list.PushFront(7);
	list.PushFront(3);
	list.PushFront(2);
	list.PushFront(9);
	list.PushFront(8);
	list.Clear();
	EXPECT_TRUE(list.IsEmpty());
}