#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(1e6) + 10;

struct node {
	int inva;
	node *nxt[26];
	node() {
		inva = 0;
		for (int i = 0; i < 26; i++) nxt[i] = NULL;
	}
};

int n;
node *at_node[N];
int k;
int ans[N];

int dfs(node *at, int path_len, int min_jump, int min_walk) {
	if (at == NULL) return 0;

	int subtree_cnt = at->inva != 0;

	path_len++;
	int curr_ans = path_len + min_walk;

	if (at->inva != 0) {
		curr_ans = min(curr_ans, min_jump);
		ans[at->inva] = curr_ans;

		min_jump++;
		min_jump = min(min_jump, curr_ans + 2);
	}
	else min_jump = min(min_jump, curr_ans + 1);

	min_walk = min(min_walk, curr_ans - path_len);

	for (int i = 0; i < 26; i++) if (at->nxt[i] != NULL) {
		int found = dfs(at->nxt[i], path_len, min_jump, min_walk);
		subtree_cnt += found;
		min_jump += found;
	}

	return subtree_cnt;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	at_node[0] = new node();

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int p;
		char c;
		scanf("%d %c", &p, &c);
		at_node[p]->nxt[c - 'a'] = new node();
		at_node[i] = at_node[p]->nxt[c - 'a'];
	}

	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		int a;
		scanf("%d", &a);
		at_node[a]->inva = i;
	}

	dfs(at_node[0], -1, 1, 0);

	for (int i = 1; i <= k; i++) {
		if (i > 1) printf(" ");
		printf("%d", ans[i]);
	}
	printf("\n");

	return 0;
}