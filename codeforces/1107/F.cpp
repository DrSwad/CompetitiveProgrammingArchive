#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int MAXN = 510;

struct Hungarian { // Returns minimum possible sum of assignment values
	ll n,i,j,k,l,m,p,q,V[MAXN][MAXN],R[MAXN],C[MAXN],M[MAXN],P[MAXN],N[MAXN],U[MAXN];
	Hungarian(ll n) : n(n) {
		for(i=MAXN; i--;) R[i]=C[i]=M[i]=P[i]=N[i]=U[i]=0;
	}
	ll solve() {
		for(i=1; i<=n; ++i) {
			for(j=1; j<=n; ++j) U[j]=N[j]=LLONG_MAX;
			for(M[p=q=0]=i,U[0]=N[0]=LLONG_MAX; M[p]; p=q) {
				for(l=LLONG_MAX,k=M[p],U[p]=0,j=1; j<=n; ++j) if(U[j]) {
					m=V[k][j]-R[k]-C[j];
					if(m<N[j]) N[j]=m,P[j]=p;
					if(l>N[j]) l=N[j],q=j;
				}
				for(j=0; j<=n; ++j) {
					if(U[j]) N[j]-=l;
					else R[M[j]]+=l,C[j]-=l;
				}
			}
			while(p) q=P[p],M[p]=M[q],p=q;
		}
		return -C[0];
	}
};

int n;
ll a[MAXN], b[MAXN], k[MAXN];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld %lld", &a[i], &b[i], &k[i]);
	}

	Hungarian h = Hungarian(n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			h.V[i][j] = - max(0LL, (a[j] - min((ll)i - 1, k[j]) * b[j]));
		}
	}

	printf("%lld\n", -h.solve());

	return 0;
}