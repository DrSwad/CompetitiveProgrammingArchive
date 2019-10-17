#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second
// #define size(a) (int)a.size()

// const int N = int(1e5) + 10;

int n, m, k;
map<int, int> row, col;
int xu, xd, yl, yr;

void possible() {
	cout << "Yes" << endl;
	exit(EXIT_SUCCESS);
}
void impossible() {
	cout << "No" << endl;
	exit(EXIT_SUCCESS);
}

void clearRight() {
	while (col.find(yr) != col.end() && col[yr] == xd - xu + 1) {
		for (int i = xu; i <= xd; i++) {
			row[i]--;
			if (row[i] == 0) row.erase(i);
		}
		col.erase(yr);
		yr--;
	}
}
void clearLeft() {
	while (col.find(yl) != col.end() && col[yl] == xd - xu + 1) {
		for (int i = xu; i <= xd; i++) {
			row[i]--;
			if (row[i] == 0) row.erase(i);
		}
		col.erase(yl);
		yl++;
	}
}
void clearUp() {
	while (row.find(xu) != row.end() && row[xu] == yr - yl + 1) {
		for (int i = yl; i <= yr; i++) {
			col[i]--;
			if (col[i] == 0) col.erase(i);
		}
		row.erase(xu);
		xu++;
	}
}
void clearDown() {
	while (row.find(xd) != row.end() && row[xd] == yr - yl + 1) {
		for (int i = yl; i <= yr; i++) {
			col[i]--;
			if (col[i] == 0) col.erase(i);
		}
		row.erase(xd);
		xd--;
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> m;

	cin >> k;
	while (k--) {
		int x, y;
		scanf("%d %d", &x, &y);
		row[x]++;
		col[y]++;
	}

	if (k == 0) possible();

	xu = 1, xd = n, yl = 1, yr = m;

	while (true) {
		while (
			xu <= xd &&
			yl <= yr &&
			row.find(xu) == row.end() &&
			row.find(xd) == row.end() &&
			col.find(yr) == col.end() &&
			col.find(yl) == col.end()
			)
			xu++, xd--, yl++, yr--;

		if (xu > xd || yl > yr) possible();

		// going right
		clearRight();
		if (row.size() == 0) possible();
		if (row.find(xu) != row.end()) impossible();
		xu++;
		if (xu > xd || yl > yr) possible();

		// going down
		clearDown();
		if (row.size() == 0) possible();
		if (col.find(yr) != col.end()) impossible();
		yr--;
		if (xu > xd || yl > yr) possible();

		// going left
		clearLeft();
		if (row.size() == 0) possible();
		if (row.find(xd) != row.end()) impossible();
		xd--;
		if (xu > xd || yl > yr) possible();

		// going up
		clearUp();
		if (row.size() == 0) possible();
		if (col.find(yl) != col.end()) impossible();
		yl++;
		if (xu > xd || yl > yr) possible();
	}

	return 0;
}