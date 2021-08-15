#include "state.hpp"
using namespace std;

//constructors for choice variables
choice::choice() { perimeter = -1; }

choice::choice(int color, vector<pair<int, int>> path) : color(color), path(path) {
	perimeter = -1;
}

void state::printsolution() {
 cout << history.size() << endl;
 for (auto x: history)
	 cout << x << ' ';
 cout << endl;
}

void state::solve(string strategy="random") {
	/*
	 * solves a floodit instance
	 * available strategies are:
	 *  - random: randomly chooses between area-first or perimeter-first on each step
	 *  - switch: alternates between area- and perimeter-first steps
	 *  - area: always chooses color by increase in area
	 *  - perimeter: always chooses color by increase in perimeter, except when
	 *  						 the perimeter doesn't increase at all
	 *  - half: goes perimeter-first until half of the board is covered
	 *  - most: goes perimeter-first until 80% of the board is covered
	 */
	bool turn = false; //control sides for the "switch" strategy
	do {
		bool pick_area = strategy == "area" ||
										 (strategy == "switch" && !turn) ||
										 (strategy == "half" && covered >= n*m/2) ||
										 (strategy == "most" && covered >= n*m*10/8) ||
										 (strategy == "random" && rand()%2);
		turn = !turn;
		choice step = choose_color(pick_area);//pick_area ? choose_by_area() : choose_by_perimeter();
		apply(step);
	} while (!win());
}

void state::apply(choice step) {
	/* applies a step to this state */
	history.push_back(step.color);
	covered += step.path.size();
	for (auto &[x, y]: step.path)
		b[x][y] = true;
}

bool state::win() { return covered == n*m; }

//state construction and initialization
state::state (int n, int m, int k, vector<vector<int>> &board) : n(n), m(m), k(k), board(board) {
	b.resize(n, vector<bool>(m, false));
	init();
}

void state::init() {
	b[0][0] = true;
	covered = bfs(0, 0, board[0][0]).size() + 1; //fills the initial group
}

vector<pair<int, int>> state::bfs(int sx, int sy, int c) {
	/* 
	 * BFS through the board starting from (sx, sy) and painting
	 * it with the color c
	 */
	queue<pair<int, int>> q;
	q.push(make_pair(sx, sy));
	vector<pair<int, int>> path; //newly painted nodes
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	visited[0][0] = true;
	while (!q.empty()) {
		pair<int, int> t = q.front(); q.pop();
		for (int x = 0; x < 2; ++x)
		for (int y = -1; y < 2; ++y) {
			int l, r;
			l = t.first+x*y;
			r = t.second+(1-x)*y;
			if (y != 0 && l >= 0 && l < n && r >= 0 && r < m
					&& !visited[l][r]
					&& (b[l][r] || (!b[l][r] && board[l][r] == c))) {
						visited[l][r] = true;
						if (!b[l][r])
							path.push_back(make_pair(l, r));
						b[l][r] = true;
						q.push(make_pair(l, r));
					}
		}
	}
	return path;
}

choice state::choose_color(bool area_first) {
	choice best = choice(-1, vector<pair<int, int>>());
	for (int i = 0; i < k; ++i) {
		if ((history.size() && i+1 == history.back()) || (!history.size() && i+1 == board[0][0])) continue;
		vector<pair<int, int>> path = bfs(0, 0, i+1);
		int perimeter = 0;
		for (auto &[x, y]: path) {
			perimeter += (x == 0) + (y == 0) +
				(x > 0 ? -2*b[x-1][y]+1 : 0) +
				(x < n-1 ? -2*b[x+1][y]+1 : 0) +
				(y > 0 ? -2*b[x][y-1]+1 : 0) +
				(y < m-1 ? -2*b[x][y+1]+1 : 0) +
				(x == n-1) + (y == m);
		}
		perimeter = max(0, perimeter);
		bool best_yet = ((area_first || !best.perimeter) && path.size() > best.path.size())
			|| !area_first && perimeter > best.perimeter;
		if (best_yet) {
			best.color = i+1;
			best.path = path;
			best.perimeter = perimeter;
		}
		for (auto &[x, y]: path)
			b[x][y] = false;
	}
	return best;
}

choice state::choose_by_area() {
	/* 
	 * run BFS for each color and choose the one with the
	 * biggest contribution to the group's area
	 */
	choice best = choice(-1, vector<pair<int, int>>());
	for (int i = 0; i < k; ++i) {
		if ((history.size() && i+1 == history.back()) || (!history.size() && i+1 == board[0][0])) continue;
		vector<pair<int, int>> path = bfs(0, 0, i+1);
		if (path.size() > best.path.size()) {
			best.color = i+1;
			best.path = path;
		}
		for (auto &[x, y]: path)
			b[x][y] = false;
	}
	return best;
}

choice state::choose_by_perimeter() {
	/* 
	 * run BFS for each color and choose the one with the
	 * biggest contribution to the group's perimeter
	 */
	choice best = choice(-1, vector<pair<int, int>>());
	for (int i = 0; i < k; ++i) {
		if ((history.size() && i+1 == history.back()) || (!history.size() && i+1 == board[0][0])) continue;
		vector<pair<int, int>> path = bfs(0, 0, i+1);
		int perimeter = 0;
		for (auto &[x, y]: path) {
			perimeter += max(0,
				(x == 0) + (y == 0) +
				(x > 0 ? -2*b[x-1][y]+1 : 0) +
				(x < n-1 ? -2*b[x+1][y]+1 : 0) +
				(y > 0 ? -2*b[x][y-1]+1 : 0) +
				(y < m-1 ? -2*b[x][y+1]+1 : 0) +
				(x == n-1) + (y == m));
		}
		if (perimeter > best.perimeter)  {
			best.color = i+1;
			best.path = path;
			best.perimeter = perimeter;
		} else if (best.perimeter == 0 && path.size() > best.path.size()) {
			best.color = i+1;
			best.path = path;
		}
		for (auto &[x, y]: path)
			b[x][y] = false;
	}
	return best;
}
