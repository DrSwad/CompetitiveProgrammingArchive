#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = 110;

int n;
string s;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> s;

	while (true) {
		char ch = 0;
		for (int j = 0; j < s.length(); j++) {
			if ((j > 0 && s[j - 1] == s[j] - 1) ||
				(j < s.length() - 1 && s[j + 1] == s[j] - 1)) {
				ch = max(ch, s[j]);
			}
		}
		if (ch == 0) break;

		for (int j = 0; j < s.length(); j++) {
			if (s[j] == ch &&
				((j > 0 && s[j - 1] == s[j] - 1) ||
					(j < s.length() - 1 && s[j + 1] == s[j] - 1))) {
				s.erase(j, 1);
				break;
			}
		}
	}

	cout << n - s.length() << endl;

	return 0;
}