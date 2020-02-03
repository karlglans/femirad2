#ifndef SEARCH
#define SEARCH

#include "Board.h"

struct SearchResult{
  short move;
  int value;
};

class Search
{
private:
  const int depth;
public:
  Search(int depth);
  void doSearch(SearchResult& sr, char actingPlayer, Board* board);
  ~Search();
};
#endif
