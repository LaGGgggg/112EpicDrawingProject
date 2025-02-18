#include "storage.h"

bool testAddDot() {
  Storage<dot> ds;
  dot d1{1.4, 2.5};
  ds.add(d1);

  if (ds.size() != 1) return false;
  if (ds.storage()[0].getx() != 1.4) return false;
  if (ds.storage()[0].gety() != 2.5) return false;

  return true;
}

bool testAddSegment() {
  Storage<segment> ss;
  segment s1{{1.4, 2.5}, {2.4, 3.5}};
  ss.add(s1);

  if (ss.size() != 1) return false;
  if (ss.storage()[0].getStart().getx() != s1.getStart().getx() || ss.storage()[0].getStart().gety() != s1.getStart().gety()) return false;
  if (ss.storage()[0].getEnd().getx() != s1.getEnd().getx() || ss.storage()[0].getEnd().gety() != s1.getEnd().gety()) return false;

  return true;
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

bool testRemove() {
  // test 1: del first el
  Storage<dot> ds = createTestDotStorage();
  ds.remove(0);
  if (ds.size() != 2) return false;
  if (ds.storage()[0].getx() != 2.2 || ds.storage()[0].gety() != 2.2) return false;
  if (ds.storage()[1].getx() != 3.3 || ds.storage()[1].gety() != 3.3) return false;

  // test 2: del second el
  ds = createTestDotStorage();
  ds.remove(1);
  if (ds.size() != 2) return false;
  if (ds.storage()[0].getx() != 1.1 || ds.storage()[0].gety() != 1.1) return false;
  if (ds.storage()[1].getx() != 3.3 || ds.storage()[1].gety() != 3.3) return false;

  // test 3: del third el
  ds = createTestDotStorage();
  ds.remove(2);
  if (ds.size() != 2) return false;
  if (ds.storage()[0].getx() != 1.1 || ds.storage()[0].gety() != 1.1) return false;
  if (ds.storage()[1].getx() != 2.2 || ds.storage()[1].gety() != 2.2) return false;

  // test 4: del second & third el
  ds = createTestDotStorage();
  ds.remove(1);
  ds.remove(1);
  if (ds.size() != 1) return false;
  if (ds.storage()[0].getx() != 1.1 || ds.storage()[0].gety() != 1.1) return false;

  return true;
}