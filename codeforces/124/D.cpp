#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10;

ll a, b;
ll X1, Y1;
ll X2, Y2;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> a >> b;
	cin >> X1 >> Y1;
	cin >> X2 >> Y2;

	X1 = (X1 + Y1);
	Y1 = (X1 - 2 * Y1);

	X2 = (X2 + Y2);
	Y2 = (X2 - 2 * Y2);

	a *= 2;
	b *= 2;

	ll cnt_a = floor(max(X1, X2) / (double)a) - (ceil(min(X1, X2) / (double)a) - 1);
	ll cnt_b = floor(max(Y1, Y2) / (double)b) - (ceil(min(Y1, Y2) / (double)b) - 1);

	cout << max(cnt_a, cnt_b) << endl;

	return 0;
}