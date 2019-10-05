#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 12, MAX_DIV = 1e6 + 5;

int n;
ll a[N];
bool dp[1 << N][1 << N];
int p_fact[N];
ll ans;

bool doesContain(int i, int mask) {
	ll x = a[i];
	for (int i = 0; i < n; i++) {
		if (mask & (1 << i)) {
			if (x % a[i] != 0)
				return false;

			x /= a[i];
		}
	}

	return true;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];

		ll x = a[i];
		for (int divi = 2; divi < min(x, (ll)MAX_DIV); divi++) {
			while (x % divi == 0) {
				p_fact[i]++;
				x /= divi;
			}
		}
		p_fact[i] += (x > 1);
	}

	for (int mask = 1; mask < 1 << n; mask++) {
		for (int up_mask = mask; up_mask > 0; up_mask = (up_mask - 1) & mask) {
			int down_mask = mask ^ up_mask;
			if (down_mask == 0) {
				dp[up_mask][down_mask] = true;
				continue;
			}

			int up_lsb = 1 << __builtin_ctz(up_mask);
			int up_rest = up_mask ^ up_lsb;
			if (up_rest != 0) {
				int down_mask1 = down_mask;
				do {
					int down_mask2 = down_mask ^ down_mask1;

					dp[up_mask][down_mask] = dp[up_mask][down_mask] || (dp[up_lsb][down_mask1] && dp[up_rest][down_mask2]);
					down_mask1 = (down_mask1 - 1) & down_mask;
				} while (down_mask1 != down_mask);
			}
			else {
				ll x;
				for (x = 0; x < n; x++) {
					if (up_lsb == 1 << x) break;
				}

				int down_mask1 = down_mask;
				do {
					int down_mask2 = down_mask ^ down_mask1;

					dp[up_mask][down_mask] = dp[up_mask][down_mask] || (doesContain(x, down_mask1) && dp[down_mask1][down_mask2]);
					down_mask1 = (down_mask1 - 1) & down_mask;
				} while (down_mask1 != down_mask);
			}
		}
	}

	int tot_p_fact = 0;
	for (int i = 0; i < n; i++) tot_p_fact += p_fact[i];

	int reduce_p_fact = -1;
	for (int up = 1; up < 1 << n; up++) {
		int down = ((1 << n) - 1) ^ up;
		if (dp[up][down]) {
			int curr_reduce = 0;
			for (int bit = 0; bit < n; bit++) {
				if (down & (1 << bit)) curr_reduce += p_fact[bit];
			}

			curr_reduce -= (up & (up - 1)) != 0;

			reduce_p_fact = max(reduce_p_fact, curr_reduce);
		}
	}

	ans = tot_p_fact - reduce_p_fact;

	for (int i = 0; i < n; i++) {
		bool isComposite = p_fact[i] > 1;
		ans += isComposite;
	}

	cout << ans << endl;

	return 0;
}