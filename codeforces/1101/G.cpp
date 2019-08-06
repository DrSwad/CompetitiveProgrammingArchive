#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5 + 10, LOG_PREF = 31;
 
int n;
int basis[LOG_PREF];
 
void insertVector(int mask) {
	for (int i = 0; i < LOG_PREF; i++) {
		if ((mask & 1 << i) == 0) continue;
 
		if (!basis[i]) {
			basis[i] = mask;
			return;
		}
 
		mask ^= basis[i];
	}
}
 
int main() {
	cin >> n;
 
	int pref = 0;
 
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
 
		pref ^= a;
		insertVector(pref);
	}
 
	if (pref == 0) {
		cout << -1 << endl;
		return 0;
	}
 
	int ans = 0;
 
	for (int i = 0; i < LOG_PREF; i++) {
		ans += (basis[i] > 0);
	}
 
	cout << ans << endl;
 
	return 0;
}