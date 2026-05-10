#include "AVL-Tree.h"
#include <gtest.h>

TEST(AVLTree, CanInsertElemIntoEmptyTree) {
	AVLTree<int, int> tree;
	ASSERT_NO_THROW(tree.insert(1, 1));
}
TEST(AVLTree, CanFindElem) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	EXPECT_EQ('a', tree.find(1));
}
TEST(AVLTree, CanInsertTwoElems) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	ASSERT_NO_THROW(tree.insert(2, 'b'));
}
TEST(AVLTree, TheSecondElemCanBeFound) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(2, 'b');
	EXPECT_EQ('b', tree.find(2));
}
TEST(AVLTree, CantFindNonexistentElem) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(2, 'b');
	ASSERT_ANY_THROW(tree.find(3));
}
TEST(AVLTree, CanDeleteElem) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(2, 'b');
	ASSERT_NO_THROW(tree.remove(2));
}
TEST(AVLTree, DeletedElemIsNoLOngerInTree) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(2, 'b');
	tree.remove(2);
	ASSERT_ANY_THROW(tree.find(2));
}
TEST(AVLTree, CanDeleteRootWithOneChild) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(2, 'b');
	tree.remove(1);
	EXPECT_NE(tree.getRoot(), 'a');
}
TEST(AVLTree, RootChangesDependingOnKeys) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(3, 'b');
	tree.insert(5, 'c');
	EXPECT_EQ(tree.getRoot(), 'b');
}
TEST(AVLTree, CanDeleteRootWithTwoChildren) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(3, 'b');
	tree.insert(5, 'c');
	ASSERT_NO_THROW(tree.remove(3));
}
TEST(AVLTree, CanUpdateValueOfExistingElem) {
	AVLTree<int, char> tree;
	tree.insert(1, 'a');
	tree.insert(3, 'b');
	tree.insert(5, 'c');
	tree.insert(1, 'd');
	EXPECT_EQ(tree.find(1), 'd');
}