#include <iostream>
#include <vector>
#include <algorithm>

int N, M;
std::vector<int> u, s;
std::vector<std::vector<int> > c1, c2;

void dfs1(int n) {
	if (u[n]) return;
	u[n] = -1;
	for (int i = 0; i<c1[n].size(); i++) dfs1(c1[n][i]);
	s.push_back(n);
}

void dfs2(int n, int mark) {
	if (u[n] != -1) return;
	u[n] = mark;
	for (int i = 0; i<c2[n].size(); i++) dfs2(c2[n][i], mark);
}

int main() {

	int runs;
	std::cin >> runs;

	while (runs--) {
		std::cin >> N >> M;
		c1 = c2 = std::vector<std::vector<int> >(N);

		for (int i = 0; i<M; i++) {
			int a, b;
			std::cin >> a >> b;
			a--; b--;
			c1[a].push_back(b);
			c2[b].push_back(a);
		}

		s.clear();

		int mark = 0;
		u = std::vector<int>(N, 0);
		for (int i = 0; i<N; i++) dfs1(i);
		for (int i = N - 1; i >= 0; i--) if (u[s[i]] == -1) dfs2(s[i], mark++);

		if (mark == 1) {
			std::cout << 0 << std::endl;
			continue;
		}

		std::vector<int> nin(mark, 0), nout(mark, 0);

		for (int i = 0; i<N; i++)
			for (int j = 0; j<c1[i].size(); j++) if (u[i] != u[c1[i][j]]) {
				nout[u[i]]++;
				nin[u[c1[i][j]]]++;
			}

		int nin0 = 0, nout0 = 0;
		for (int i = 0; i<mark; i++) {
			if (nin[i] == 0) nin0++;
			if (nout[i] == 0) nout0++;
		}

		std::cout << std::max(nin0, nout0) << std::endl;
	}

	return 0;
}

/*
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;
typedef vector<int> vi;

int root[50000], in[50000], out[50000];
int C = 0, ins = 0, outs = 0;
vi P, F[50000];

int dfs(int v) {
  root[v] = out[v] = in[v] = ++ins;
  P.push_back(v);
  for (vi::iterator it = F[v].begin(); it != F[v].end(); ++it)
    root[v] <?= in[*it] ? root[*it] : root[*it] ? root[v] : dfs(*it);
  if (out[v] == root[v] && ++C)
    do out[v] = P.back(), P.pop_back(), root[out[v]] = v, in[out[v]] = 0;
    while (out[v] != v);
  return in[v] ? root[v] : (out[v]=0)+ins;
}

void solve() {
  int S, I;
  scanf("%d%d", &S, &I);
  fprintf(stderr, "%d %d\n", S, I);
  for (int i = 1; i <= S; ++i) F[i].clear();
  for (int i = 0; i < I; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    assert(1 <= a && a <= S && 1 <= b && b <= S && a != b);
    F[a].push_back(b);
  }
  memset(in, 0, sizeof(in));
  memset(out, 0, sizeof(out));
  memset(root, 0, sizeof(root));
  C = ins = outs = 0;
  P.clear();
  for (int i = 1; i <= S; ++i) root[i] || dfs(i);
  ins = 0;
  for (int i = 1; i <= S; ++i)
    for (vi::iterator it = F[i].begin(); it != F[i].end(); ++it)
      if (root[i] != root[*it]) {
	if (!out[root[i]]++) ++outs;
	if (!in[root[*it]]++) ++ins;
      }
  printf("%d\n", C > 1 ? max(C-ins, C-outs) : 0);
}

int main(void) {
  int N;
  for (scanf("%d", &N); N--; solve());
  return 0;
}
*/