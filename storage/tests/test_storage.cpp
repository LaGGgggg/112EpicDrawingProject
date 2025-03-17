#include <gtest/gtest.h>
#include "../storage.h"
#include "../../objects/dot.h"
#include <iostream>

TEST(testStorage, addDot) {
    Storage<dot> ds;
    dot d1{1.4, 2.5};   
    ds.add(d1);
  
    ASSERT_EQ(ds.size(), 1);
    ASSERT_DOUBLE_EQ(ds.storage()[0].getx(), 1.4);
    ASSERT_DOUBLE_EQ(ds.storage()[0].gety(), 2.5);
}
  
TEST(testStorage, addSegment){
    Storage<segment> ss;
    segment s1{{1.4, 2.5}, {2.4, 3.5}};
    ss.add(s1);
  
    ASSERT_EQ(ss.size(), 1);
    ASSERT_TRUE(ss.storage()[0].getStart().getx() == s1.getStart().getx() && ss.storage()[0].getStart().gety() == s1.getStart().gety());
    ASSERT_TRUE(ss.storage()[0].getEnd().getx() == s1.getEnd().getx() && ss.storage()[0].getEnd().gety() == s1.getEnd().gety());
}
  
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
  
// test 1: del first el
TEST(testStorage, removeFirst){
    Storage<dot> ds = createTestDotStorage();
    ds.remove(0);
    ASSERT_EQ(ds.size(),2);
    ASSERT_TRUE(ds.storage()[0].getx() == 2.2 && ds.storage()[0].gety() == 2.2);
    ASSERT_TRUE(ds.storage()[1].getx() == 3.3 && ds.storage()[1].gety() == 3.3);
}

// test 2: del second el
TEST(testStorage, removeSecond){
    ds = createTestDotStorage();
    ds.remove(1);
    ASSERT_EQ(ds.size(), 2);
    ASSERT_TRUE(ds.storage()[0].getx() == 1.1 && ds.storage()[0].gety() == 1.1);
    ASSERT_TRUE(ds.storage()[1].getx() == 3.3 && ds.storage()[1].gety() == 3.3);
}

// test 3: del third el
TEST(testStorage, removeThird){
    ds = createTestDotStorage();
    ds.remove(2);
    ASSERT_EQ(ds.size(), 2);
    ASSERT_TRUE(ds.storage()[0].getx() == 1.1 && ds.storage()[0].gety() == 1.1);
    ASSERT_TRUE(ds.storage()[1].getx() == 2.2 && ds.storage()[1].gety() == 2.2);
}

// test 4: del second & third el
TEST(testStorage, remove2elem){
    ds = createTestDotStorage();
    ds.remove(1);
    ds.remove(1);
    ASSERT_EQ(ds.size(), 1);
    ASSERT_TRUE(ds.storage()[0].getx() == 1.1 && ds.storage()[0].gety() == 1.1);
}

 
    //Test 1
 TEST(testStorage, getElement){
        Storage<dot> ds = createTestDotStorage();
        dot d1 = ds.getElementPosition(0);
        EXPECT_DOUBLE_EQ(d1.getx(), 1.1);
        EXPECT_DOUBLE_EQ(d1.gety(), 1.1);
        dot d3 = ds.getElementPosition(2);
        EXPECT_DOUBLE_EQ(d3.getx(), 3.3);
        EXPECT_DOUBLE_EQ(d3.gety(), 3.3);
}

//Test 2 and Test 3
TEST(testStorage, getInvalidPos){
        Storage<dot> ds = createTestDotStorage();
        EXPECT_THROW(ds.getElementPosition(-1), const char* error);
        EXPECT_THROW(ds.getElementPosition(10), const char* error);
    }

    //Test 4
TEST(testStorage, getAfterRemove){
    Storage<dot> ds = createTestDotStorage();
    ds.remove(1);
    dot d = ds.getElementPosition(1);
    ASSERT_TRUE(d.getx() == 3.3 && d.gety() == 3.3);
}