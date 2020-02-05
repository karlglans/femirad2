#include "gtest/gtest.h"
#include "../../logic/GoodCellList.h"

TEST(GoodCellList, store_will) {

  GoodCellList gcl;

  gcl.store(11, 2);
  gcl.store(18, 3);
  gcl.store(13, 1);
  short* list = gcl.getList();

  EXPECT_EQ(list[0], 18);
  EXPECT_EQ(list[1], 11);
  EXPECT_EQ(list[2], 13);

  //short* list = gcl.getList();
}