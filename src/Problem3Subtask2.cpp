#include <bits/stdc++.h>
using namespace std;
const int MAXN = 510;

int N, M, K;
bitset<MAXN> A[MAXN], U;
long long W[MAXN];
long long G[MAXN][MAXN];
int Id[MAXN];
bitset<MAXN> Ans;

bool Check(long long x) {
    for (int i = 1; i <= N; i++) {
        Id[i] = i;
    }
    vector<int> S;
    bitset<MAXN> C;
    for (int i = 1; i <= N; i++) A[i].reset();
    random_shuffle(Id + 1, Id + 1 + N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (W[Id[i]] * G[Id[i]][j] <= x) {
                A[Id[i]][j] = true;
            }
        }
    }
    while (C != U) {
        pair<int, int> Max = {0, 0};
        for (int i = 1; i <= N; i++) {
            int x = 0;
            for (int j = 1; j <= N; j++) {
                if (A[Id[i]][j] == 1 && C[j] == 0) {
                    x++;
                }
            }
            if (x > Max.first) {
                Max = {x, Id[i]};
            }
        }
        C = C | A[Max.second];
        S.push_back(Max.second);
        if (S.size() > K) return false;
    }
    Ans.reset();
    for (int i : S) Ans[i] = true;
    return true;
}

int main() {
    srand(time(0)); 
    scanf("%d %d %d", &N, &M, &K);
    memset(G, 0x3f, sizeof G);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &W[i]);
        W[i]++;
        G[i][i] = 0;
        U[i] = true;
        Id[i] = i;
    }
    for (int i = 1; i <= M; i++) {
        static int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        G[u][v] = w;
        G[v][u] = w;
    }
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                G[i][j] = min(G[i][k] + G[k][j], G[i][j]);
            }
        }
    }
    long long l = 1, r = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            r = max(r, W[i] * G[i][j]);
        }
    }
    while (l <= r) {
        long long mid = l + r >> 1;
        if (Check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    for (int i = 1; i <= N; i++) {
        if (Ans[i]) {
            cout << i << " ";
        }
    }
    return 0;
}