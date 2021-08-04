#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct state {
  vector<vector<bool>> b;
  vector<vector<int>> board;
  int n, m, k;
  vector<int> history;
  int color, covered;

  void printsolution() {
    cout << history.size() << endl;
    for (auto x: history)
      cout << x << ' ';
    cout << endl;
  }

	void solve() {
		do {
			history.push_back(h());
			bfs(0, 0, history.back());
			//print();
		} while (!win());
	}

	vector<int> h(int min_diff, int max_steps) { //TODO nova funcao
		/* min_diff: menor diferença entre pior e melhor p/ parar
		 * max_steps: maior profundidade antes de parar
		 */
		queue<pair<state, int>> q; //state, level (how deep it is)
		state best, worst;
		best.covered = -1;
		worst.covered = n*m*k*100;
		for (int i = 0; i < k; ++i) {
			state s = state(n, m, k);
			q.push(i);
		}
		while (!q.empty()) { //TODO seguir só os melhores
			/*
			 * pega o estado que tem na fila
			 * ve quantos ele cobre
			 * atualiza variaveis best e worst
			 * verifica o nivel vs max_steps
			 * verifica diferença best vs worst vs min_diff
			 * enfileira os proximos
			 */
			pair<state, int> p = q.top(); q.pop();
			int covers = p.first.covered;
			if (covers > best.covered)
				best = p.first;
			if (covers < worst.covered)
				worst = p.first;
			if (p.second >= max_steps)
				return best.history;
			for (int i = 0; i < k; ++i)
				q.push(
		}
	}

  void print() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j)
        cout << b[i][j] << ' ';
      cout << endl;
    }
    cout << endl;
    cout << endl;
  }
  
  bool win() {
    for (auto x: b)
    for (auto y: x)
      if (!y) return false;
    return true;
  }

  state () {}

  state (int n, int m, int k, vector<vector<int>> board) {
    this->n = n;
    this->m = m;
    this->k = k;
    this->board = board;
    b.resize(n, vector<bool>(m, false));
    init();
  }

  void init() {
    b[0][0] = true;
    bfs(0, 0, board[0][0]);
  }

  vector<pair<int, int>> bfs(int sx, int sy, int c) {
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
            && (b[l][r] || !b[l][r] && board[l][r] == c)) {
              visited[l][r] = true;
              if (!b[l][r])
                path.push_back(make_pair(l, r));
              b[l][r] = true;
              q.push(make_pair(l, r));
            }
      }
    }
		covered += path.size();
    return path;
  }

  int h() {
    int n = board.size(), m = board[0].size();
    pair<int, int> best = make_pair(-1, -1);
    for (int i = 0; i < k; ++i) {
      vector<pair<int, int>> path = bfs(0, 0, i+1);
      if ((int)path.size() > best.second) {
        best = make_pair(i+1, path.size());
      }
      for (auto p: path)
        b[p.first][p.second] = false;
			covered -= path.size();
    }
    return best.first;
  }

};

/*
 * estado ve algumas jogadas à frente com uma bfs
	 * inicialmente ve só 1 msm
 * vê qual é a melhor escolha de jogadas a seguir
 * mais rapido do que fazer uma bfs pra preencher a matriz de boolean: cada jogada no resultado já guarda a matriz resultado
 */

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> b(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < m; ++j)
    cin >> b[i][j];
  //criando state inicial com bfs
  state s0(n, m, k, b);
  s0.init();
  s0.solve();
  s0.printsolution();
}
