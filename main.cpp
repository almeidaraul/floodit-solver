#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct state {
  vector<vector<bool>> b;
  vector<int> history;
  int color;
  bool win() {
    for (auto x: b)
    for (auto y: x)
      if (!y) return false;
    return true;
  }
  bool get(int i, int j) {
    return b[i][j];
  }
  bool set(int i, int j, bool v) {
    return b[i][j] = v;
  }
  state () {}
  state (int n, int m) {
    b.resize(n, vector<bool>(m, false));
  }
};

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> b(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < m; ++j)
    cin >> b[i][j];
  //criando state inicial com bfs
  state s0(n, m);
  queue<pair<int, int>> q;
  q.push(make_pair(0, 0));
  s0.set(0, 0, true);
  while (!q.empty()) {
    pair<int, int> p = q.front(); q.pop();
    int color = b[p.first][p.second];
    for (int i = -1; i < 2; ++i)
    for (int j = -1; j < 2; ++j)
      if ((i != 0 || j != 0)
          && p.first+i >= 0
          && p.second+j >= 0
          && p.first+i < n
          && p.second+j < m
          && !s0.get(p.first+i, p.second+j)
          && b[p.first+i][p.second+j] == color) {
        s0.set(p.first+i, p.second+j, true);
        q.push(make_pair(p.first+i, p.second+j));
      }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j)
      cout << s0.get(i, j) << ' ';
    cout << endl;
  }
  if (s0.win())
    cout << "W\n";
  else
    cout << "L\n";
}