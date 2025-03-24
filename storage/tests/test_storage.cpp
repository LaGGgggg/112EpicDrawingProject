#include <gtest/gtest.h>
#include "../storage.h"
#include "../../objects/dot.h"
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

        ds_empty.m_size = 0;
        ds_empty.m_storage = nullptr;

        ss.m_size = 0;
        ss.m_storage = nullptr;
    }
};

TEST_F(TestStorage, addDot) {
    dot d1{1.4, 2.5};   
    ds_empty.add(d1);
  
    ASSERT_EQ(ds_empty.size(), 1);
    dot Dot = ds_empty.getElementPosition(0);
    ASSERT_DOUBLE_EQ(Dot.getx(), 1.4);
    ASSERT_DOUBLE_EQ(Dot.gety(), 2.5);
}
  
TEST_F(TestStorage, addSegment){
    segment s1{{1.4, 2.5}, {2.4, 3.5}};
    ss.add(s1);
  
    ASSERT_EQ(ss.size(), 1);
    segment seg = ss.getElementPosition(0);
    ASSERT_EQ(seg.getStart().getx(), s1.getStart().getx());
    ASSERT_EQ(seg.getStart().gety(), s1.getStart().gety());
    ASSERT_EQ(seg.getEnd().getx(), s1.getEnd().getx());
    ASSERT_EQ(seg.getEnd().gety(), s1.getEnd().gety());
}

// test 1: del first el
TEST_F(TestStorage, removeFirst){
    ds.remove(0);
    ASSERT_EQ(ds.size(),2);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).getx(), 2.2);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).gety(), 2.2);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(1).getx(), 3.3);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(1).gety(), 3.3);
}

// test 2: del second el
TEST_F(TestStorage, removeSecond){
    ds.remove(1);
    ASSERT_EQ(ds.size(), 2);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).getx(), 1.1);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).gety(), 1.1);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(1).getx(), 3.3);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(1).gety(), 3.3);
}

// test 3: del third el
TEST_F(TestStorage, removeThird){
    ds.remove(2);
    ASSERT_EQ(ds.size(), 2);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).getx(), 1.1);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).gety(), 1.1);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(1).getx(), 2.2);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(1).gety(), 2.2);
}

// test 4: del second & third el
TEST_F(TestStorage, remove2elem){
    ds.remove(1);
    ds.remove(1);
    ASSERT_EQ(ds.size(), 1);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).getx(), 1.1);
    ASSERT_DOUBLE_EQ(ds.getElementPosition(0).gety(), 1.1);
}

 
    //Test 1
TEST_F(TestStorage, getElement){
    dot d1 = ds.getElementPosition(0);
    ASSERT_DOUBLE_EQ(d1.getx(), 1.1);
    ASSERT_DOUBLE_EQ(d1.gety(), 1.1);
    dot d3 = ds.getElementPosition(2);
    ASSERT_DOUBLE_EQ(d3.getx(), 3.3);
    ASSERT_DOUBLE_EQ(d3.gety(), 3.3);
}

//Test 2 and Test 3
TEST_F(TestStorage, getInvalidPos){
    EXPECT_THROW(ds.getElementPosition(-1), const char*);
    EXPECT_THROW(ds.getElementPosition(10), const char*);
}

    //Test 4
TEST_F(TestStorage, getAfterRemove){
    ds.remove(1);
    dot d = ds.getElementPosition(1);
    ASSERT_DOUBLE_EQ(d.getx(), 3.3);
    ASSERT_DOUBLE_EQ(d.gety(), 3.3);
}
