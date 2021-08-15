#include "state.hpp"
using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> b(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < m; ++j)
    cin >> b[i][j];
  //criando state inicial com bfs
  state s0(n, m, k, b);
  s0.solve();
  s0.printsolution();
}
