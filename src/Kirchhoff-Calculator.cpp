#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;

const int MAXN = 205;
const double INF = 1e20;	
const double eps = 1e-5;
int inline read(){
	int x = 0, f = 0; char ch = getchar();
	while(ch < '0' || ch > '9') f ^= (ch == '-'), ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

int n, m, k, q;
bool vis[MAXN];
double R[MAXN][MAXN];     // R[u][v] = 1 / R_{uv}
double matx[MAXN][MAXN] = {1}, t[MAXN];

signed main(){
	puts("Kirchhoff Calculator, see https://www.luogu.com.cn/problem/P2011");
	puts("Please number the nodes in the circuit, 0-n, node 0 is the battery negative, which means U0 = 0V");
	puts("input the number of the node (n): "); n = read();
	puts("Then input the number of resistances (m): "); m = read();
	puts("There are some battery in some nodes, which means Ux is certain:");  k = read();
	puts("then input the k certain node and it's voltage: ");
	for(int i = 1; i <= k; ++i) {
		int id = read(), U = read(); vis[id] = true;
		matx[id][id] = 1.0; matx[id][n + 1] = (double)U;
	}
	puts("finally input the resistances and which node it connect with, like \"u v r\""); 
	for(int i = 1; i <= m; ++i){
		int u = read(), v = read(), r = read();
		R[u][v] += 1.0 / r; R[v][u] += 1.0 / r;
	}
	
	for(int i = 1; i <= n; ++i){
		if(vis[i]) continue; else vis[i] = true;
		for(int j = 0; j <= n; ++j){
			if(j == i) continue;
			matx[i][j] -= R[i][j]; matx[i][i] += R[i][j];
		}
	}
	
	for(int i = 0, maxx; i <= n; ++i){
		maxx = i;
		for(int j = i + 1; j <= n; ++j)
			if(fabs(matx[j][i]) > fabs(matx[maxx][i])) maxx = j;
		memcpy(t, matx[i], sizeof(double) * (n + 2));
		memcpy(matx[i], matx[maxx], sizeof(double) * (n + 2));
		memcpy(matx[maxx], t, sizeof(double) * (n + 2));
		
		for(int k = 0; k <= n; ++k){
			if(k == i) continue;
			double d = matx[k][i] / matx[i][i];
			for(int j = i; j <= n + 1; ++j)
				matx[k][j] -= d * matx[i][j];
		}
	}

	puts("\n\nresult: ");
	puts("Node Voltage:");
	for(int i = 1; i <= n; ++i) printf("%.4lld %.7lf\n", i, matx[i][n + 1] / matx[i][i]);
	return 0;
}
