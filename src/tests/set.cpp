#include <gtest/gtest.h>
#include "tests.h"

using namespace s21;

TEST(SetTest, DefaultConstructor) {
    Set<int> set;
    EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, Erase) {
    Set<int> set;
    set.insert(1);
    set.insert(2);
    set.erase(set.begin());
    EXPECT_EQ(set.size(), 1);
    EXPECT_FALSE(set.contains(1));
}

TEST(SetTest, CopyConstructor) {
    Set<int> set1;
    set1.insert(1);
    set1.insert(2);
    Set<int> set2(set1);
    EXPECT_EQ(set2.size(), 2);
    EXPECT_TRUE(set2.contains(1));
    EXPECT_TRUE(set2.contains(2));
}

TEST(SetTest, MoveConstructor) {
    Set<int> set1;
    set1.insert(1);
    set1.insert(2);
    Set<int> set2(std::move(set1));
    EXPECT_EQ(set2.size(), 2);
    EXPECT_TRUE(set2.contains(1));
    EXPECT_TRUE(set2.contains(2));
    EXPECT_TRUE(set1.empty());
}

TEST(SetTest, AssignmentOperator) {
    Set<int> set1;
    set1.insert(1);
    set1.insert(2);
    Set<int> set2;
    set2.insert(3);
    set2.insert(4);
    set2 = set1;
    EXPECT_EQ(set2.size(), 2);
    EXPECT_TRUE(set2.contains(1));
    EXPECT_TRUE(set2.contains(2));
}

TEST(SetTest, Swap) {
    Set<int> set1;
    set1.insert(1);
    Set<int> set2;
    set2.insert(2);
    set1.swap(set2);
    EXPECT_TRUE(set1.contains(2));
    EXPECT_TRUE(set2.contains(1));
}