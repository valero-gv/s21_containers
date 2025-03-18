#include <gtest/gtest.h>
#include "tests.h"

using namespace s21;

TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PushAndTop) {
    Stack<int> stack;
    stack.push(1);
    EXPECT_EQ(stack.top(), 1);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 1);
}

TEST(StackTest, Pop) {
    Stack<int> stack;
    stack.push(1);
    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, CopyConstructor) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    Stack<int> copyStack(stack);
    EXPECT_EQ(copyStack.top(), 2);
    EXPECT_EQ(stack.size(), copyStack.size());
}

TEST(StackTest, MoveConstructor) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    Stack<int> movedStack(std::move(stack));
    EXPECT_EQ(movedStack.top(), 2);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, AssignmentOperator) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    Stack<int> assignedStack;
    assignedStack = stack;
    EXPECT_EQ(assignedStack.top(), 2);
    EXPECT_EQ(stack.size(), assignedStack.size());
}

TEST(StackTest, Swap) {
    Stack<int> stack1;
    stack1.push(1);
    Stack<int> stack2;
    stack2.push(2);
    stack1.swap(stack2);
    EXPECT_EQ(stack1.top(), 2);
    EXPECT_EQ(stack2.top(), 1);
}

TEST(StackTest, Iterator) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    int expected = 3;
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        EXPECT_EQ(*it, expected--);
    }
}
