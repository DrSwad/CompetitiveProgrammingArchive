#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

const int N = 2e5 + 10, MOD = 1e9 + 7;

int n;
int l[N], r[N];

int stR[4 * 2 * N];
ll stDP[4 * 2 * N], stCnt[4 * 2 * N];
int maxVal;
void init() {
	for (int i = 0; i < 4 * 2 * N; i++) {
		stR[i] = 0;
		stDP[i] = LLONG_MAX;
	}
}
void update(int stI, int L, int R, int at, int r, ll dp, ll cnt) {
	if ((L > at) || (R < at)) return;

	if (L == R) {
		if ((stR[stI] == 0) || (stR[stI] > r)) {
			//cerr << "Updating " << L << " to " << r << endl;
			stR[stI] = r;
		}

		ll curr = stDP[stI];
		if (dp == curr) {
			stCnt[stI] += cnt;
			stCnt[stI] %=  MOD;
		}
		else if (dp < curr) {
			stDP[stI] = dp;
			stCnt[stI] = cnt % MOD;
		}

		return;
	}

	int mid = (L + R) / 2;
	update((stI << 1), L, mid, at, r, dp, cnt);
	update((stI << 1) + 1, mid + 1, R, at, r, dp, cnt);

	int _r = stR[(stI << 1)];
	if (_r == 0) _r = stR[(stI << 1) + 1];
	else if (stR[(stI << 1) + 1] != 0) _r = min(_r, stR[(stI << 1) + 1]);
	stR[stI] = _r;

	ll _dp = stDP[(stI << 1)];
	ll _cnt = stCnt[(stI << 1)];
	if (stDP[(stI << 1) + 1] < _dp) {
		_dp = stDP[(stI << 1) + 1];
		_cnt = stCnt[(stI << 1) + 1];
	}
	else if (stDP[(stI << 1) + 1] == _dp) {
		_cnt += stCnt[(stI << 1) + 1];
		_cnt %= MOD;
	}

	stDP[stI] = _dp;
	stCnt[stI] = _cnt;
}
void update(int at, int r, ll dp, ll cnt) {
	update(1, 0, maxVal, at, r, dp, cnt);
}
int queryR(int stI, int L, int R, int l, int r) {
	if ((L > r) || (R < l)) return 0;

	if ((L >= l) && (R <= r)) {
		//cerr << "Returning: " << L << " " << R << " " << stR[stI] << endl;
		return stR[stI];
	}

	int mid = (L + R) / 2;
	int q1 = queryR((stI << 1), L, mid, l, r);
	int q2 = queryR((stI << 1) + 1, mid + 1, R, l, r);

	//cerr << "Returning: " << L << " " << R << " " << q1 << " " << q2 << endl;

	if (q1 == 0) return q2;
	if (q2 == 0) return q1;
	return min(q1, q2);
}
int queryR(int l, int r) {
	return queryR(1, 0, maxVal, l, r);
}
ii queryDP(int stI, int L, int R, int l, int r) {
	//cerr << stI << " " << L << " " << R << endl;
	if ((L > r) || (R < l)) return {0, 0};

	if ((L >= l) && (R <= r)) {
		//cerr << L << " " << R << " " << l << " " << r << " " << stDP[stI] << " " << stCnt[stI] << endl;
		return {stDP[stI], stCnt[stI]};
	}

	int mid = (L + R) / 2;
	ii q1 = queryDP((stI << 1), L, mid, l, r);
	ii q2 = queryDP((stI << 1) + 1, mid + 1, R, l, r);

	//cerr << stI << " " << L << " " << R << " ";
	//cerr << q1.first << " " << q1.second << " ";
	//cerr << q2.first << " " << q2.second << endl;

	if (q1.second == 0) return q2;
	if (q2.second == 0) return q1;
	if (q1.first > q2.first) return q2;
	if (q2.first > q1.first) return q1;
	return {q1.first, (q1.second + q2.second) % MOD};
}
ii queryDP(int l, int r) {
	return queryDP(1, 0, maxVal, l, r);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	vector<int> cmp;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &r[i], &l[i]);
		cmp.push_back(r[i]);
		cmp.push_back(l[i]);
	}

	sort(cmp.begin(), cmp.end());
	cmp.resize(unique(cmp.begin(), cmp.end()) - cmp.begin());
	maxVal = cmp.size() - 1;

	for (int i = 1; i <= n; i++) {
		r[i] = lower_bound(cmp.begin(), cmp.end(), r[i]) - cmp.begin();
		l[i] = lower_bound(cmp.begin(), cmp.end(), l[i]) - cmp.begin();
	}

	int order[N];
	iota(order, order + N, 0);
	sort(order + 1, order + n + 1, [](int i, int j) {
		return l[i] > l[j];
	});

	ll mini[N], cnt[N];

	init();

	for (int j = 1; j <= n; j++) {
		int i = order[j];
		//cerr << endl << i << " " << l[i] << " " << r[i] << endl;

		int end = queryR(r[i], maxVal);
		//debug(end);

		ii dp;
		if (end > 0) {
			dp = queryDP(r[i], end - 1);
			//cerr << dp.first << " " << dp.second << endl;

			dp.first -= cmp[r[i]];
		}
		else dp = {0LL, 1};
		//cerr << dp.first << " " << dp.second << endl;

		mini[i] = dp.first;
		cnt[i] = dp.second;
		//cerr << mini[i] << " " << cnt[i] << endl;

		update(l[i], r[i], mini[i] + cmp[l[i]], cnt[i]);
		//cerr << l[i] << " " << r[i] << " " << mini[i] + cmp[l[i]] << " " << cnt[i] << endl;
	}

	int end = queryR(0, maxVal);

	cout << queryDP(0, end - 1).second << endl;

	return 0;
}