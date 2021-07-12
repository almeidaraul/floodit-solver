#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  cout << "aqui\n";
  vector<vector<int>> tab(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < m; ++j)
    cin >> tab[i][j];
  //criando estado inicial com bfs
  vector<vector<bool>> s0(n, vector<bool>(m, false));
  queue<pair<int, int>> q;
  q.push(make_pair(0, 0));
  s0[0][0] = true;
  while (!q.empty()) {
    pair<int, int> p = q.front(); q.pop();
    int cor = tab[p.first][p.second];
    for (int i = -1; i < 2; ++i)
    for (int j = -1; j < 2; ++j)
      if ((i != 0 || j != 0)
          && p.first+i >= 0
          && p.second+j >= 0
          && p.first+i < n
          && p.second+j < m
          && !s0[p.first+i][p.second+j]
          && tab[p.first+i][p.second+j] == cor) {
        s0[p.first+i][p.second+j] = true;
        q.push(make_pair(p.first+i, p.second+j));
      }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j)
      cout << s0[i][j] << ' ';
    cout << endl;
  }
  /*
    possibilidades de estruturas p/ estado
    - vetor de indíces com a fronteira do role
      - problema: remover indices
    - bitset onde 1 indica que um quadrado é
      da cor do [0][0] e 0 indica que não é
      - teria que consultar o tabuleiro
  */
}