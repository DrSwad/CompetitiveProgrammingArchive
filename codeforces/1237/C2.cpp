#include <bits/stdc++.h>
 
using namespace std;
 
#ifdef LOCAL
#include "debug.h"
#endif
 
typedef long long ll;
typedef pair<int, int> pii;
 
#define x first
#define y second
 
const int N = 5e4 + 10;
 
int n;
int p[N][3];

vector<int> solve(vector<int> v, int at) {
	if (at == 3) return v;

	map<int, vector<int>> mp;
	for (int id : v) {
		mp[p[id][at]].push_back(id);
	}

	vector<int> rem;

	for (auto p : mp) {
		vector<int> res = solve(p.y, at + 1);
		for (int id : res) rem.push_back(id);
	}

	for (int i = 0; i < (int)rem.size() - 1; i += 2) {
		printf("%d %d\n", rem[i], rem[i + 1]);
	}

	if (rem.size() % 2 == 1) return vector<int>(1, rem[rem.size() - 1]);
	else return vector<int>();
}
 
int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++)
			scanf("%d", &p[i][j]);
	}

	vector<int> v(n);
	iota(v.begin(), v.end(), 1);
	solve(v, 0);
 
	return 0;
}