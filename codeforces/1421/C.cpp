#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

// const int N = int(1e5) + 10;
// const int MOD = int(1e9) + 7;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	string s;
	cin >> s;

	int n = s.length();

	cout << 4 << endl;
	printf("L %d\n", n - 1); n += (n - 2);
	printf("R %d\n", n - 1); n += 1;
	printf("L %d\n", n - 1); n += (n - 2);
	printf("L %d\n", 2); n += 1;

	return 0;
}