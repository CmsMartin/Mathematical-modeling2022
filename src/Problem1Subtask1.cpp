#include <iostream>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

int N, M;
ll G[510][510], Dist[510][510], Rank[510][510], W[510];

int Solve() {  // 返回核酸检测点位置
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                Dist[i][j] = min(Dist[i][j], Dist[i][k] + Dist[k][j]);
            }
        }
    }

    int ans = 0;
    ll r = INF;
    for (int i = 1; i <= N; i++) {
        ll t = 0;
        for (int j = 1; j <= N; j++) {
            t += Dist[i][j] * W[j];
        }
        if (t < r) ans = i, r = t;
    }

    return ans;

    return;
}