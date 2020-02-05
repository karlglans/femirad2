#include "GoodCellList.h"
#include <queue>

struct CellPos {
  short pos;
  int value;
};

auto cmp = [](CellPos left, CellPos right) { return (left.value) < (right.value); };
std::priority_queue<CellPos, std::vector<CellPos>, decltype(cmp)> q3(cmp);

GoodCellList::GoodCellList()
{
  reset();
}


GoodCellList::~GoodCellList()
{
}

short* GoodCellList::getList() {
  int idx = 0;
  while (!q3.empty()) {
    if (idx < MAX_CAP) {
      _list[idx] = q3.top().pos;
      idx++;
    }
    q3.pop();
  }
  return _list;
}

int GoodCellList::copyFromList(short* indecis) {
  int idx = 0;
  while (!q3.empty()) {
    if (idx < MAX_CAP) {
      indecis[idx] = q3.top().pos;
      idx++;
    }
    q3.pop();
  }
  return idx;
}

void GoodCellList::store(short cellIdx, int value) {

  //for (int i = 0; i < MAX_CAP; i++) {
  //  if (_list[i] == -1) {
  //    _list[i] = cellIdx;
  //  }
  //  if (i + 1 < MAX_CAP) {
  //    _list[i + 1] = -1;
  //  }
  //}
  //CellPos* cellPos = new CellPos();
  //cellPos->pos = cellIdx;
  //cellPos->value = value;
  CellPos cellPos;
  cellPos.pos = cellIdx;
  cellPos.value = value;
  q3.push(cellPos);
}

void GoodCellList::reset() {
  _list[0] = LIST_END;
}
