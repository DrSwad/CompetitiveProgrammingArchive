#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(1e5) + 10;
// const int MOD = int(1e9) + 7;

int n;
int a[N];

queue<int> q[4];
int row[N];
vector<pii> ans;

void impossible() {
	puts("-1");
	exit(EXIT_SUCCESS);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}

	int at_row = n;

	for (int at_column = n; at_column >= 1; at_column--) {
		if (a[at_column] == 0) {
			continue;
		} else if (a[at_column] == 1) {
			row[at_column] = at_row;
			ans.push_back({at_row, at_column});
			q[1].push(at_column);
			at_row--;
		} else if (a[at_column] == 2) {
			if (q[1].empty()) {
				impossible();
			} else {
				ans.push_back({row[q[1].front()], at_column});
				q[1].pop();
				q[2].push(at_column);
			}
		} else {
			ans.push_back({at_row, at_column});
			if (!q[3].empty()) {
				ans.push_back({at_row, q[3].front()});
				q[3].pop();
			} else if (!q[2].empty()) {
				ans.push_back({at_row, q[2].front()});
				q[2].pop();
			} else if (!q[1].empty()) {
				ans.push_back({at_row, q[1].front()});
				q[1].pop();
			} else {
				impossible();
			}
			q[3].push(at_column);
			at_row--;
		}
	}

	printf("%d\n", (int)ans.size());

	for (auto cell : ans) {
		printf("%d %d\n", cell.x, cell.y);
	}

	return 0;
}