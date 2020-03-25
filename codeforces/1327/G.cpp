#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int A = 14;

struct AhoCorasick {
	vector<vector<int>> trie;
	vector<int> parent, parent_char;
	vector<int> suffix_link;
	vector<vector<int>> suffix_jump;
	vector<bool> cost_at_vis;
	vector<ll> cost_at;
	vector<vector<bool>> cost_jump_vis;
	vector<vector<ll>> cost_jump;

	AhoCorasick() {
		trie.push_back(vector<int>(A, -1));
		parent.push_back(0);
		parent_char.push_back(-1);
		suffix_link.push_back(-1);
		suffix_jump.push_back(vector<int>(A, -1));
		cost_at_vis.push_back(false);
		cost_at.push_back(0);
		cost_jump_vis.push_back(vector<bool>(A, false));
		cost_jump.push_back(vector<ll>(A, 0));
	}
	void insert(const string& s, int cost) {
		int at = 0;
		for (int i = 0; i < s.length(); i++) {
			if (trie[at][s[i] - 'a'] == -1) {
				trie[at][s[i] - 'a'] = trie.size();

				trie.push_back(vector<int>(A, -1));
				parent.push_back(at);
				parent_char.push_back(s[i] - 'a');
				suffix_link.push_back(-1);
				suffix_jump.push_back(vector<int>(A, -1));
				cost_at_vis.push_back(false);
				cost_at.push_back(0);
				cost_jump_vis.push_back(vector<bool>(A, false));
				cost_jump.push_back(vector<ll>(A, 0));
			}
			at = trie[at][s[i] - 'a'];
		}
		cost_at[at] += cost;
	}
	int suffixLink(int at) {
		if (suffix_link[at] != -1) return suffix_link[at];
		if (at == 0 || parent[at] == 0) return suffix_link[at] = 0;
		return suffix_link[at] = suffixJump(suffixLink(parent[at]), parent_char[at]);
	}
	int suffixJump(int at, int ch) {
		if (suffix_jump[at][ch] != -1) return suffix_jump[at][ch];
		if (trie[at][ch] != -1) return suffix_jump[at][ch] = trie[at][ch];
		if (at == 0) return suffix_jump[at][ch] = 0;
		return suffix_jump[at][ch] = suffixJump(suffixLink(at), ch);
	}
	ll costAt(int at) {
		if (cost_at_vis[at]) return cost_at[at];
		cost_at_vis[at] = true;
		return cost_at[at] += costAt(suffixLink(at));
	}
	ll costJump(int at, int ch) {
		if (cost_jump_vis[at][ch]) return cost_jump[at][ch];
		cost_jump_vis[at][ch] = true;
		return cost_jump[at][ch] = costAt(suffixJump(at, ch));
	}
	pair<int, ll> costTraverse(int from, const string& s) {
		int at = from;
		ll tot_cost = 0;
		for (int i = 0; i < s.length(); i++) {
			at = suffixJump(at, s[i] - 'a');
			tot_cost += costAt(at);
		}
		return make_pair(at, tot_cost);
	}
} aho;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int k;
	cin >> k;
	while (k--) {
		string t;
		int cost;
		cin >> t >> cost;
		aho.insert(t, cost);
	}

	string s;
	cin >> s;

	vector<int> q_pos;
	q_pos.push_back(-1);
	for (int i = 0; i < s.length(); i++) if (s[i] == '?') q_pos.push_back(i);
	q_pos.push_back(s.length());

	int tot_q = q_pos.size() - 2;
	int aho_size = aho.trie.size();
	vector<vector<pair<int, ll>>> cost_from(tot_q + 1, vector<pair<int, ll>>(aho_size));

	for (int i = 1; i < q_pos.size(); i++) {
		string sub_s = s.substr(q_pos[i - 1] + 1, q_pos[i] - 1 - q_pos[i - 1]);
		for (int j = 0; j < aho_size; j++) {
			cost_from[i - 1][j] = aho.costTraverse(j, sub_s);
		}
	}

	ll INF = ll(1e18);
	vector<vector<ll>> dp(1 << A, vector<ll>(aho_size, -INF));
	dp[0][cost_from[0][0].x] = cost_from[0][0].y;
	ll ans = -INF;

	for (int mask = 0; mask < 1 << A; mask++) {
		int bits = __builtin_popcount(mask);

		if (bits == tot_q) {
			for (int ends_at = 0; ends_at < aho_size; ends_at++) {
				if (dp[mask][ends_at] != -INF) ans = max(ans, dp[mask][ends_at]);
			}
		}

		if (bits >= tot_q) continue;

		for (int ends_at = 0; ends_at < aho_size; ends_at++) {
			if (dp[mask][ends_at] != -INF) {
				for (int bit = 0; bit < A; bit++) {
					if ((mask & 1 << bit) == 0) {
						int new_mask = mask | 1 << bit;
						int new_from = aho.suffixJump(ends_at, bit);
						int new_end = cost_from[bits + 1][new_from].x;
						ll new_cost = cost_from[bits + 1][new_from].y;
						dp[new_mask][new_end] = max(dp[new_mask][new_end],
							dp[mask][ends_at] + aho.costAt(new_from) + new_cost);
					}
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}