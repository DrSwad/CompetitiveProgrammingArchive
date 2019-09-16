#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 1e5 + 10;

int n;
set<int> st;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	while (n--) {
		int x;
		cin >> x;
		st.insert(x);
	}
	int ans = 0;
	while (!st.empty()) {
		int num = *st.begin();
		for (auto it = st.begin(); it != st.end();) {
			if (*it % num == 0) it = st.erase(it);
			else it++;
		}
		ans++;
	}

	cout << ans << endl;

	return 0;
}