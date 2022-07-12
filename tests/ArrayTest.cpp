//
// Created by adeon on 7/12/22.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "gtest/gtest.h"
#include "array_d.hpp"
#include "ratiod_t.hpp"

class ArrayTest : public testing::Test {
protected:
    void SetUp() override {}

    bsd::array_d<int, 4> arr1 = {1, 2, 3};
    bsd::array_d<int, 4> arr2{1, 2, 4};
    bsd::array_d<int, 4> arr3{1, 2};
    bsd::array_d<int, 4> arr4{1, 2, 3, 4, 5};
};

TEST_F(ArrayTest, ConstructionTest) {
    // Different construction equality
    arr2[2] = 3;
    ASSERT_EQ(arr1, arr2);
    ASSERT_EQ(arr1[3], 0);

    // = operator
    arr2 = arr3;
    ASSERT_EQ(arr2, arr3);

    // More args than size(TODO later)
    arr1[3] = 4;
    EXPECT_EQ(arr1, arr4);
}

TEST_F(ArrayTest, ElementAccess) {
    // at()
    arr2.at(2) = 3;
    ASSERT_EQ(arr2.at(2), 3);
    ASSERT_EQ(arr1, arr2);
    ASSERT_THROW(arr2.at(10), std::out_of_range);

    // operator []
    arr3[2] = 3;
    ASSERT_EQ(arr3[2], 3);
    ASSERT_EQ(arr3, arr2);

    // front
    arr1.front() = 10;
    arr2.front() = 10;
    ASSERT_EQ(arr1, arr2);
    ASSERT_EQ(arr1.front(), arr2.front());

    // back
    arr1.back() = 10;
    arr2[3] = 10;
    ASSERT_EQ(arr1, arr2);
    ASSERT_EQ(arr1[3], arr2.front());

    // data
    *(arr4.data() + 3) = 10;
    *arr4.data() = 10;
    ASSERT_EQ(arr1, arr4);
    ASSERT_EQ(*arr4.data(), *arr4.begin());
}

TEST_F(ArrayTest, IteratorTest) {
    // Just some iterator playing
    ASSERT_EQ(arr1.begin(), ++arr1.rend());
    ASSERT_EQ(--arr1.end(), arr1.rbegin());
    ASSERT_EQ(arr1.cbegin(), arr1.crend() + 1);
    ASSERT_EQ(arr1.cend() - 1, arr1.crbegin());
    ASSERT_EQ(arr1.begin()[2], *(arr1.begin() + 2));

    ASSERT_EQ(*arr1.begin(), 1);
    ASSERT_EQ(*arr1.end() - 1, 0);
}

TEST_F(ArrayTest, CapacityTest) {
    ASSERT_EQ(arr1.is_empty(), false);
    ASSERT_EQ(arr1.size(), 4);
    ASSERT_EQ(arr1.max_size(), 4);
}

TEST_F(ArrayTest, OperationsTest) {
    // Fill
    arr1.fill(2);
    for (int & it : arr1) {
        ASSERT_EQ(it, 2);
    }
    // Swap
    arr1.swap(arr2);
    for (int & it : arr2) {
        ASSERT_EQ(it, 2);
    }
    arr1[2] = 3;
    arr1[3] = 4;
    ASSERT_EQ(arr4, arr1);
}

TEST_F(ArrayTest, OperatorTest) {
    // < <= > >= == !=
    ASSERT_EQ(arr1 < arr2, true);
    ASSERT_EQ(arr1 <= arr2, true);
    ASSERT_EQ(arr1 > arr2, false);
    ASSERT_EQ(arr1 >= arr2, false);
    ASSERT_EQ(arr1 == arr2, false);
    ASSERT_EQ(arr1 != arr2, true);
    // <= < > >= == != when equal
    arr1 = arr2;
    ASSERT_EQ(arr1 < arr2, false);
    ASSERT_EQ(arr1 <= arr2, true);
    ASSERT_EQ(arr1 > arr2, false);
    ASSERT_EQ(arr1 >= arr2, true);
    ASSERT_EQ(arr1 == arr2, true);
    ASSERT_EQ(arr1 != arr2, false);
}