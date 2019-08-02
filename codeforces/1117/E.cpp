#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<ll, ll> ii;
 
#define x first
#define y second
 
const int N = 1e4 + 10;

int n;
string t;
int MOD[] = {23, 24, 25};
int rem[3][N];
int pos[int(1e6) + 10];
char s[N];

void query(int mod_i) {
	int mod = MOD[mod_i];

	char q[N];
	for (int i = 0; i < n; i++) {
		q[i] = 'a' + (i % mod);
	}
	q[n] = '\0';

	printf("? %s", q);
	cout << endl;
	cout.flush();

	string res;
	cin >> res;

	assert(res != "0");
	assert(res.length() == n);

	for (int i = 0; i < n; i++) {
		rem[mod_i][i] = res[i] - 'a';
	}
}

void printAns() {
	s[n] = '\0';

	printf("! %s", s);
	cout << endl;
	cout.flush();
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> t;
	n = t.length();

	query(0);
	query(1);
	query(2);

	int LCM = MOD[0] * MOD[1] * MOD[2];
	for (int i = 0; i < LCM; i++) {
		pos[(i % MOD[2]) * 10000 + (i % MOD[1]) * 100 + (i % MOD[0])] = i;
	}

	for (int i = 0; i < n; i++) {
		s[pos[rem[2][i] * 10000 + rem[1][i] * 100 + rem[0][i]]] = t[i];
	}

	printAns();

	return 0;
}