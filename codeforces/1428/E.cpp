#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(1e5) + 10;

int n, k;
int a[N];
int splitCount[N];

priority_queue<pair<ll, int>> potentialSavings;

ll takesTime(int carrotLength, int totalSplits) {
	int splitLength = carrotLength / totalSplits;
	int remains = carrotLength % totalSplits;
	return (ll)splitLength * splitLength * (totalSplits - remains) +
		(ll)(splitLength + 1) * (splitLength + 1) * remains;
}

ll savesTime(int carrotLength, int totalSplits) {
	return takesTime(carrotLength, totalSplits - 1) - takesTime(carrotLength, totalSplits);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);

		splitCount[i] = 1;
		if (splitCount[i] + 1 <= a[i]) {
			potentialSavings.push({savesTime(a[i], splitCount[i] + 1), i});
		}
	}

	while (k-- > n) {
		auto top = potentialSavings.top();
		potentialSavings.pop();

		int carrotIndex = top.y;
		splitCount[carrotIndex]++;
		if (splitCount[carrotIndex] + 1 <= a[carrotIndex]) {
			potentialSavings.push({savesTime(a[carrotIndex], splitCount[carrotIndex] + 1), carrotIndex});
		}
	}

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += takesTime(a[i], splitCount[i]);
	}

	cout << ans << endl;

	return 0;
}