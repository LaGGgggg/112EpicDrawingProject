#include "storage.h"

bool testAddDot() {
  dotStorage ds{nullptr, 0};
  dot d1{1.4, 2.5};
  add(ds, d1);

  if (ds.size != 1) return false;
  if (ds.storage[0].x != 1.4) return false;
  if (ds.storage[0].y != 2.5) return false;

  return true;
}

bool testAddSegment() {
  segmentStorage ss{nullptr, 0};
  segment s1{{1.4, 2.5}, {2.4, 3.5}};
  add(ss, s1);

  if (ss.size != 1) return false;
  if (ss.storage[0].start.x != s1.start.x || ss.storage[0].start.y != s1.start.y) return false;
  if (ss.storage[0].end.x != s1.end.x || ss.storage[0].end.y != s1.end.y) return false;

  return true;
}

dotStorage createTestDotStorage() {
  dotStorage ds{nullptr, 0};
  dot d1{1.1, 1.1};
  dot d2{2.2, 2.2};
  dot d3{3.3, 3.3};
  add(ds, d1);
  add(ds, d2);
  add(ds, d3);
  return ds;
}

bool testRemove() {
  // test 1: del first el
  dotStorage ds = createTestDotStorage();
  remove<dotStorage, dot>(ds, 0);
  if (ds.size != 2) return false;
  if (ds.storage[0].x != 2.2 && ds.storage[0].y != 2.2) return false;
  if (ds.storage[1].x != 3.3 && ds.storage[1].y != 3.3) return false;

  // test 2: del second el
  ds = createTestDotStorage();
  remove<dotStorage, dot>(ds, 1);
  if (ds.size != 2) return false;
  if (ds.storage[0].x != 1.1 && ds.storage[0].y != 1.1) return false;
  if (ds.storage[1].x != 3.3 && ds.storage[1].y != 3.3) return false;

  // test 3: del third el
  ds = createTestDotStorage();
  remove<dotStorage, dot>(ds, 2);
  if (ds.size != 2) return false;
  if (ds.storage[0].x != 1.1 && ds.storage[0].y != 1.1) return false;
  if (ds.storage[1].x != 2.2 && ds.storage[1].y != 2.2) return false;

  // test 4: del second & third el
  ds = createTestDotStorage();
  remove<dotStorage, dot>(ds, 1);
  remove<dotStorage, dot>(ds, 1);
  if (ds.size != 1) return false;
  if (ds.storage[0].x != 1.1 && ds.storage[0].y != 1.1) return false;

  return true;
}
