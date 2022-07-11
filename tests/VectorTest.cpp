//
// Created by adeon on 7/9/22.
//
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "gtest/gtest.h"
#include "vector_d.hpp"
#include "ratiod_t.hpp"

class VectorTest : public testing::Test {
protected:
    void SetUp() override {
        v2_.push_back(10);
        v2_.push_back(8);
        v2_.push_back(9);
        v2_.push_back(12);
    }

    bsd::vector_d<int> v1_;
    bsd::vector_d<int> v2_;
    bsd::vector_d<bsd::ratio_d_t> v3_;
};

TEST_F(VectorTest, EmptyVector) {
    ASSERT_EQ(v1_.empty(), true);
    ASSERT_EQ(v2_.empty(), false);
}

TEST_F(VectorTest, SizeCapacityTest) {
    ASSERT_EQ(v1_.size(), 0);
    ASSERT_EQ(v1_.capacity(), 0);
    v1_.push_back(1);
    v1_.push_back(2);
    v1_.push_back(3);
    ASSERT_EQ(v1_.size(), 3);
    ASSERT_EQ(v1_.capacity(), 4);
}

TEST_F(VectorTest, ElementAccess) {
    ASSERT_EQ(v2_.back(), 12);
    v2_.pop_back();
    ASSERT_EQ(v2_.back(), 9);

    ASSERT_EQ(v2_.at(0), 10);
    ASSERT_EQ(v2_.front(), 10);

    ASSERT_EQ(v2_[1], 8);
    v2_[1] = 122;
    ASSERT_EQ(v2_[1], 122);

    ASSERT_THROW(v2_.at(3), std::out_of_range);

    // data pointer
    ASSERT_EQ(v1_.data(), nullptr);
}

TEST_F(VectorTest, VectorConstruction) {
    // Multiple element
    bsd::vector_d<int> v{10, 8, 9, 12};
    ASSERT_EQ(v, v2_);
    // Size + fill value
    bsd::vector_d<int> v2(3, 3);
    ASSERT_NE(v, v2);
    // Empty
    bsd::vector_d<int> v3{};
    ASSERT_EQ(v1_, v3);
    // Copy
    bsd::vector_d<int> v4{v2_};
    ASSERT_EQ(v4, v2_);
    // Move
    bsd::vector_d<int> v5{std::move(v2_)};
    ASSERT_NE(v5, v2_);
    // Iterator interval constructor
    bsd::vector_d<int> test1{3, 3};
    bsd::vector_d<int> v6{v2.begin(), v2.end() - 1};
    ASSERT_EQ(v6, test1);
    // =
    v6 = v;
    ASSERT_EQ(v6, v);
    // move = (don't know how good is this test)
    v1_ = std::move(v6);
    ASSERT_EQ(v1_, v);
    ASSERT_EQ(v6.data(), nullptr);

}

TEST_F(VectorTest, VectorIterators) {
    ASSERT_EQ(v2_.begin(), bsd::vector_d<int>::iterator(&v2_[0]));
    ASSERT_EQ(v2_.end(), bsd::vector_d<int>::iterator(&v2_[v2_.size()]));
    ASSERT_EQ(v2_.cbegin(), bsd::vector_d<int>::const_iterator(&v2_[0]));
    ASSERT_EQ(v2_.cend(), bsd::vector_d<int>::const_iterator(&v2_[v2_.size()]));

    ASSERT_EQ(v2_.rbegin(), bsd::vector_d<int>::reverse_iterator(&v2_[v2_.size() - 1]));
    ASSERT_EQ(v2_.rend(), bsd::vector_d<int>::reverse_iterator(&v2_[0] - 1));
    ASSERT_EQ(v2_.crbegin(), bsd::vector_d<int>::const_reverse_iterator(&v2_[v2_.size() - 1]));
    ASSERT_EQ(v2_.crend(), bsd::vector_d<int>::const_reverse_iterator(&v2_[0] - 1));
}

TEST_F(VectorTest, VectorEmplace) {
    bsd::ratio_d_t rt{1, 9};
    v3_.emplace_back(3, 9);
    v3_.emplace_back(1, 9);
    ASSERT_EQ(v3_[1], rt);

    v3_.emplace(v3_.cbegin() + 1, 1, 2);
    ASSERT_NE(v3_[1], rt);

    // Here go ranges
}

TEST_F(VectorTest, VectorSizeChangeOperations) {
    auto it1 = v2_.insert(v2_.begin() + 2, 22);
    ASSERT_EQ(v2_.size(), 5);
    ASSERT_EQ(v2_.capacity(), 8);
    ASSERT_EQ(v2_[2], 22);
    ASSERT_EQ(*it1, 22);

    auto it2 = v2_.insert(v2_.begin() + 5, 122);
    ASSERT_EQ(v2_.size(), 6);
    ASSERT_EQ(v2_.capacity(), 8);
    ASSERT_EQ(*v2_.rbegin(), 122);
    ASSERT_EQ(*it2, 122);

    auto it3 = v2_.insert(v2_.begin() + 5, 3, 228);
    ASSERT_EQ(v2_.size(), 9);
    ASSERT_EQ(v2_.capacity(), 16);
    ASSERT_EQ(*v2_.rbegin(), 122);
    ASSERT_EQ(*it3, 228);

    // equality test
    bsd::vector_d<int> t1{10, 8, 22, 9, 12, 228, 228, 228, 122};
    ASSERT_EQ(v2_, t1);

    auto it5 = v2_.erase(v2_.begin() + 1);
    ASSERT_EQ(v2_.size(), 8);
    ASSERT_EQ(v2_.capacity(), 16);
    ASSERT_EQ(*(v2_.begin() + 1), 22);
    ASSERT_EQ(*it5, 22);

    v2_.shrink_to_fit();
    ASSERT_EQ(v2_.size(), 8);
    ASSERT_EQ(v2_.capacity(), 8);

    v2_.reserve(20);
    ASSERT_EQ(v2_.size(), 8);
    ASSERT_EQ(v2_.capacity(), 20);

    v2_.resize(3);
    ASSERT_EQ(v2_.size(), 3);
    ASSERT_EQ(v2_.capacity(), 20);
}

TEST_F(VectorTest, VectorSwap) {
    v2_.swap(v1_);
    ASSERT_EQ(v2_.size(), 0);
    ASSERT_EQ(v2_.capacity(), 0);
    ASSERT_EQ(v2_.data(), nullptr);
    ASSERT_EQ(v1_.size(), 4);
    ASSERT_EQ(v1_.capacity(), 4);
    ASSERT_NE(v1_.data(), nullptr);
}