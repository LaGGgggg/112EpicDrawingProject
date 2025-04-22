#include <gtest/gtest.h>
#include "../storage.h"
#include "../../objects/dot.h"
#include "../../objects/segment.h"
#include <iostream>

Storage<dot> createTestDotStorage() {
    Storage<dot> ds;
    dot d1{1.1, 1.1};
    dot d2{2.2, 2.2};
    dot d3{3.3, 3.3};
    ds.add(d1);
    ds.add(d2);
    ds.add(d3);
    return ds;
}
  
class TestStorage : public ::testing::Test{ //один класс для всех тестов Storage
protected:
    Storage<segment> ss;
    Storage<dot> ds_empty;
    Storage<dot> ds;
    void SetUp(){
        ds = createTestDotStorage();
    }
};

TEST_F(TestStorage, addDot) {
    dot d1{1.4, 2.5};   
    ds_empty.add(d1);
  
    ASSERT_EQ(ds_empty.size(), 1);
    dot Dot = ds_empty[0];
    ASSERT_DOUBLE_EQ(Dot.x, 1.4);
    ASSERT_DOUBLE_EQ(Dot.y, 2.5);
}
  
TEST_F(TestStorage, addSegment){
	dot d1{ 1.4, 2.5 };
	dot d2{ 2.4, 3.5 };
    segment s1(&d1,&d2);
    ss.add(s1);
  
    ASSERT_EQ(ss.size(), 1);
    segment seg = ss[0];
    ASSERT_EQ(seg.getStart().x, s1.getStart().x);
    ASSERT_EQ(seg.getStart().y, s1.getStart().y);
    ASSERT_EQ(seg.getEnd().x, s1.getEnd().x);
    ASSERT_EQ(seg.getEnd().y, s1.getEnd().y);
}

// test 1: del first el
TEST_F(TestStorage, removeFirst){
    ds.remove(0);
    ASSERT_EQ(ds.size(),2);
    ASSERT_DOUBLE_EQ(ds[0].x, 2.2);
    ASSERT_DOUBLE_EQ(ds[0].y, 2.2);
    ASSERT_DOUBLE_EQ(ds[1].x, 3.3);
    ASSERT_DOUBLE_EQ(ds[1].y, 3.3);
}

// test 2: del second el
TEST_F(TestStorage, removeSecond){
    ds.remove(1);
    ASSERT_EQ(ds.size(), 2);
    ASSERT_DOUBLE_EQ(ds[0].x, 1.1);
    ASSERT_DOUBLE_EQ(ds[0].y, 1.1);
    ASSERT_DOUBLE_EQ(ds[1].x, 3.3);
    ASSERT_DOUBLE_EQ(ds[1].y, 3.3);
}

// test 3: del third el
TEST_F(TestStorage, removeThird){
    ds.remove(2);
    ASSERT_EQ(ds.size(), 2);
    ASSERT_DOUBLE_EQ(ds[0].x, 1.1);
    ASSERT_DOUBLE_EQ(ds[0].y, 1.1);
    ASSERT_DOUBLE_EQ(ds[1].x, 2.2);
    ASSERT_DOUBLE_EQ(ds[1].y, 2.2);
}

// test 4: del second & third el
TEST_F(TestStorage, remove2elem){
    ds.remove(1);
    ds.remove(1);
    ASSERT_EQ(ds.size(), 1);
    ASSERT_DOUBLE_EQ(ds[0].x, 1.1);
    ASSERT_DOUBLE_EQ(ds[0].y, 1.1);
}

 
    //Test 1
TEST_F(TestStorage, getElement){
    dot d1 = ds[0];
    ASSERT_DOUBLE_EQ(d1.x, 1.1);
    ASSERT_DOUBLE_EQ(d1.y, 1.1);
    dot d3 = ds[2];
    ASSERT_DOUBLE_EQ(d3.x, 3.3);
    ASSERT_DOUBLE_EQ(d3.y, 3.3);
}

//Test 2 and Test 3
TEST_F(TestStorage, getInvalidPos){
    EXPECT_THROW(ds[-1], const char*);
    EXPECT_THROW(ds[10], const char*);
}

    //Test 4
TEST_F(TestStorage, getAfterRemove){
    ds.remove(1);
    dot d = ds[1];
    ASSERT_DOUBLE_EQ(d.x, 3.3);
    ASSERT_DOUBLE_EQ(d.y, 3.3);
}
