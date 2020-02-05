#ifndef GOOD_CELL_LIST
#define GOOD_CELL_LIST

#define MAX_CAP 5
#define LIST_END -1

class GoodCellList
{
  short _list[MAX_CAP];
public:
  void store(short cellIdx, int value);
  short* getList();
  int copyFromList(short* indecis);
  void reset();
  GoodCellList();
  ~GoodCellList();
};
#endif
