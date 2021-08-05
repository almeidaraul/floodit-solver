#include <iostream>
#include <vector>
#include <queue>
#include <utility>

struct state {
	std::vector<std::vector<bool>> b;
	std::vector<std::vector<int>> &board;
  int n, m, k;
	std::vector<int> history;
  int color;

  void solve();
  void printsolution();
  void print();
  bool win();
  state ();
  state (int n, int m, int k, std::vector<std::vector<int>> &board);
  void init();
	std::vector<std::pair<int, int>> bfs(int sx, int sy, int c);
  int h();
};
