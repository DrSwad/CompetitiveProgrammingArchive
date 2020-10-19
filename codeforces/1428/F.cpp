#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(5e5) + 10;

int n;
char s[N];
int streak[N];
int lcsFreq[N];
ll suffixAns[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> (s + 1);

	for (int i = n; i >= 1; i--) {
		if (s[i] == '0') {
			streak[i] = 0;
			lcsFreq[0]++;
			suffixAns[i] = suffixAns[i + 1];
		} else {
			streak[i] = 1 + (s[i + 1] == s[i] ? streak[i + 1] : 0);
			if (s[i + 1] == '1') {
				suffixAns[i] = suffixAns[i + 1];

				lcsFreq[streak[i]]++;
				suffixAns[i] += streak[i];

				int updates = lcsFreq[streak[i + 1]] - 1;
				lcsFreq[streak[i]] += updates;
				lcsFreq[streak[i + 1]] -= updates;
				suffixAns[i] += updates;
			} else if (s[i + 1] == '0') {
				suffixAns[i] = suffixAns[i + 1];

				lcsFreq[streak[i]]++;
				suffixAns[i] += streak[i];

				int updates = lcsFreq[streak[i + 1]];
				lcsFreq[streak[i]] += updates;
				lcsFreq[streak[i + 1]] -= updates;
				suffixAns[i] += updates;
			} else {
				lcsFreq[1]++;
				suffixAns[i] = 1;
			}
		}
	}

	ll ans = 0LL;
	for (int i = 1; i <= n; i++) {
		ans += suffixAns[i];
	}

	cout << ans << endl;

	return 0;
}