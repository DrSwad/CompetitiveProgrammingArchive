#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<ll, ll> ii;
 
#define x first
#define y second
 
const int N = 1e5 + 10;

ll h, l;
double x;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> h >> l;
	x = (double)(l * l - h * h) / 2.0 / h;
	cout << setprecision(15) << x << endl;
 
	return 0;
}