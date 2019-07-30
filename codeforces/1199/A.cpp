#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<ll, ll> ii;
 
#define x first
#define y second
 
const int N = 1e5 + 10;

int n, x, y;
int a[N];

bool ok(int at) {
	for (int i = max(1, at - x); i < at; i++) if (a[i] <= a[at]) return false;
	for (int i = at + 1; i <= min(n, at + y); i++) if (a[i] <= a[at]) return false;
	return true;
}
 
int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) if (ok(i)) {
		cout << i << endl;
		return 0;
	}
 
	return 0;
}