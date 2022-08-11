//
// Created by adeon on 7/19/22.
//

#include "gtest/gtest.h"
#include "memory/unique_ptr_d.hpp"
#include "ratiod_t.hpp"

class UniquePrtTest: public testing::Test {
public:
    void SetUp() override {
        p1_.reset();
        p2_.reset();
        p3_.reset();
    }

    bsd::unique_ptr_d<bsd::ratio_d_t> p1_;
    bsd::unique_ptr_d<int> p2_;
    bsd::unique_ptr_d<int> p3_;
};

TEST_F(UniquePrtTest, ConstructionTest) {
    // Move constructor
    bsd::unique_ptr_d<int> p1(new int{111});
    bsd::unique_ptr_d<int> p2(std::move(p1));
    ASSERT_EQ(p1, nullptr);
    ASSERT_EQ(*p2, 111);

    // Move = operator
    p2_ = std::move(p2);
    ASSERT_EQ(p2, nullptr);
    ASSERT_EQ(*p2_, 111);
}

TEST_F(UniquePrtTest, ModifierTest) {
    p2_ = bsd::unique_ptr_d<int>(new int{112});
    p3_ = bsd::unique_ptr_d<int>(new int{113});
    ASSERT_EQ(*p2_, 112);
    ASSERT_EQ(*p3_, 113);

    // release test
    int *ip = p2_.release();
    ASSERT_EQ(p2_, nullptr);
    ASSERT_EQ(*ip, 112);

    // reset
    p3_.reset(ip);
    ASSERT_NE(p3_, nullptr);
    ASSERT_EQ(*p3_, 112);
    ASSERT_EQ(*ip, 112);

    // swap
    p3_.swap(p2_);
    ASSERT_EQ(p3_, nullptr);
    ASSERT_EQ(*p2_, 112);
}