#include "state.hpp"
using namespace std;

int main(int argc, char** argv) {
	//read input
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> b(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < m; ++j)
    cin >> b[i][j];
	//create and initialize state
  state s0(n, m, k, b);
	//define strategy
	string strategy = argc > 1 ?  argv[1] : "area";
	//solve
  s0.solve(strategy);
  s0.printsolution();
}
