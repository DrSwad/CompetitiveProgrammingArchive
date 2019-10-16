#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 13845 + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int n;
	cin >> n;

	int cnt = 0;
	while (n--) {
		int a;
		scanf("%d", &a);
		if (a % 2 == 0) printf("%d\n", a / 2);
		else {
			printf("%d\n", int(floor(a / 2.0) + cnt));
			cnt ^= 1;
		}
	}

	return 0;
}