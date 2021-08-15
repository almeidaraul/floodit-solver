#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstdlib>

struct choice {
	int color, perimeter;
	std::vector<std::pair<int, int>> path;
	choice ();
	choice (int color, std::vector<std::pair<int, int>> path);
};

struct state {
  int n, m, k;
	std::vector<std::vector<bool>> b;
	std::vector<std::vector<int>> &board;
	std::vector<int> history;
  int covered;

	void printsolution();
  void solve(std::string strategy);
	void apply(choice step);
  bool win();
  state (int n, int m, int k, std::vector<std::vector<int>> &board);
  void init();
	std::vector<std::pair<int, int>> bfs(int sx, int sy, int c);
	choice choose_color(bool area_first);
	choice choose_by_area();
	choice choose_by_perimeter();
};
