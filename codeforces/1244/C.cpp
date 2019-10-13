#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10;

long long n, p;
int w, d;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> p >> w >> d;

	for (int i = 0; i < w; i++) {
		ll rem = p - i * 1LL * d;
		if (rem < 0) break;
		if (rem % w == 0) {
			if (rem / w < 0) break;
			if (rem / w + i > n) break;

			printf("%lld %lld %lld\n", rem / w, (ll)i, n - i - rem / w);
			return 0;
		}
	}

	printf("-1\n");

	return 0;
}