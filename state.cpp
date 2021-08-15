#include "state.hpp"
using namespace std;

void state::solve() {
	do {
		pair<int, vector<pair<int, int>>> step = h();
		history.push_back(step.first);
		//covered += bfs(0, 0, history.back()).size();
		covered += step.second.size();
		for (auto &[x, y]: step.second)
			b[x][y] = true;
		//cout << "covered: " << covered << endl;
		//print();
	} while (!win());
}

void state::printsolution() {
	cout << history.size() << endl;
	for (auto x: history)
		cout << x << ' ';
	cout << endl;
}

void state::print() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			cout << b[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
	cout << endl;
}
  
bool state::win() {
	return covered == n*m;
}

state::state (int n, int m, int k, vector<vector<int>> &board) : n(n), m(m), k(k), board(board) {
	b.resize(n, vector<bool>(m, false));
	init();
}

void state::init() {
	b[0][0] = true;
	covered = bfs(0, 0, board[0][0]).size() + 1;
}

vector<pair<int, int>> state::bfs(int sx, int sy, int c) {
	queue<pair<int, int>> q;
	q.push(make_pair(sx, sy));
	vector<pair<int, int>> path;
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

pair<int, vector<pair<int, int>>> state::h() {
	pair<int, vector<pair<int, int>>> best = make_pair(-1, vector<pair<int, int>>());
	for (int i = 0; i < k; ++i) {
		vector<pair<int, int>> path = bfs(0, 0, i+1);
		if (path.size() > best.second.size()) {
			best = make_pair(i+1, path);
		}
		for (auto p: path)
			b[p.first][p.second] = false;
	}
	return best;
}
