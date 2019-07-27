#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 2e5 + 10;

int n;
int a[N];
int pos[N];
int l[N], r[N];
ll ans;

bool contains(int L, int R, int at) {
	return (L <= at) && (R >= at);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pos[a[i]] = i;
	}

	stack<int> st;
	for (int i = 1; i <= n; i++) {
		while (!st.empty() && a[st.top()] < a[i]) st.pop();
		if (st.empty()) l[i] = 1;
		else l[i] = st.top() + 1;
		st.push(i);
	}

	st = {};
	for (int i = n; i >= 1; i--) {
		while (!st.empty() && a[st.top()] < a[i]) st.pop();
		if (st.empty()) r[i] = n;
		else r[i] = st.top() - 1;
		st.push(i);
	}

	for (int i = 1; i <= n; i++) {
		int szL = i - l[i];
		int szR = r[i] - i;

		int L, R;
		if (szL <= szR) L = l[i], R = i - 1;
		else L = i + 1, R = r[i];

		for (int j = L; j <= R; j++) {
			int val = a[i] - a[j];
			if (contains(l[i], r[i], pos[val]) && !contains(L, R, pos[val])) ans++;
		}
	}

	cout << ans << endl;

	return 0;
}