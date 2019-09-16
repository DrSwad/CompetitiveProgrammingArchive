#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 200;

int n;
string s;
int a, b;
int cnt[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> s;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;

		if (s[i] == '1') {
			for (int i = 0; i < b; i++) cnt[i]++;
		}

		int at = b;
		if (s[i] == '1') at = b + a;

		while (at < N) {
			for (int i = at; i < min(at + a, N); i++) cnt[i]++;
			at += 2 * a;
		}
	}

	cout << *max_element(cnt, cnt + N) << endl;

	return 0;
}