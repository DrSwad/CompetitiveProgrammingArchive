#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 2e5 + 10;

int n;
int a[N];
vector<int> ids[N];
vector<int> adj[N];

int ans;
int visDFS[N];
int dfs(int at, int parent, int prime) {
	visDFS[at] = prime;

	vector<int> lens;
	for (int ch : adj[at]) if (ch != parent && a[ch] % prime == 0) {
		lens.push_back(dfs(ch, at, prime));
	}

	if (lens.size() == 0) {
		ans = max(ans, 1);
		return 1;
	}
	else if (lens.size() == 1) {
		ans = max(ans, lens[0] + 1);
		return lens[0] + 1;
	}
	else {
		int m1 = 0, m2 = -1;
		for (int i = 1; i < lens.size(); i++) {
			if (lens[i] >= lens[m1]) {
				m2 = m1;
				m1 = i;
			}
			else {
				if (m2 == -1) m2 = i;
				else if (lens[i] > lens[m2]) m2 = i;
			}
		}

		ans = max(ans, lens[m1] + lens[m2] + 1);
		return lens[m1] + 1;
	}
}

bool visSieve[N];
void sieve() {
	for (int i = 2; i < N; i++) if (!visSieve[i]) {
		for (int j = i; j < N; j += i) {
			visSieve[j] = true;

			for (int id : ids[j])
				if (visDFS[id] != i)
					dfs(id, id, i);
		}
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		ids[a[i]].push_back(i);
	}
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	sieve();

	cout << ans << endl;

	return 0;
}