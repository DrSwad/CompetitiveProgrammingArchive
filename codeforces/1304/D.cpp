#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

// const int N = int(2e5) + 10;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		string s;

		cin >> n >> s;

		vector<int> ans_min(n), ans_max(n);
		iota(ans_min.begin(), ans_min.end(), 1);
		iota(ans_max.begin(), ans_max.end(), 1);
		reverse(ans_min.begin(), ans_min.end());

		for (int i = 0; i < n - 1; i++) {
			if (s[i] == '>') continue;
			int j = i;
			while (j < n - 1 && s[j] == '<') j++;
			reverse(ans_min.begin() + i, ans_min.begin() + j + 1);
			i = j;
		}

		for (int i = 0; i < n - 1; i++) {
			if (s[i] == '<') continue;
			int j = i;
			while (j < n - 1 && s[j] == '>') j++;
			reverse(ans_max.begin() + i, ans_max.begin() + j + 1);
			i = j;
		}

		for (int i : ans_min) cout << i << " \n"[i == ans_min.back()];
		for (int i : ans_max) cout << i << " \n"[i == ans_max.back()];
	}

	return 0;
}