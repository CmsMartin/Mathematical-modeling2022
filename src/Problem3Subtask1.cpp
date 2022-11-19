#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

const double T0 = 1e9, T1 = 0.1, a = 0.9;
const int L = 5, T = 100;

ifstream GIn("Graph.txt");
ofstream Ans("Ans.txt");
ofstream Log("Log.txt");

mt19937 mt;
int Rnd(int L, int R) {
    return L + mt() % (R - L + 1);
}
uniform_real_distribution<double> U(0, 1);

ll G[510][510], Dist[510][510], W[510];

int n, m, k;
int p[510];

ll ans = INF;
int ansp[510];

multiset<ll> g[510];

void add(int u) {
    for (int i = 1; i <= n; i++) {
        g[i].insert(Dist[i][u]);
    }
}
void del(int u) {
    for (int i = 1; i <= n; i++) {
        g[i].erase(Dist[i][u]);
    }
}
ll calc() {
    ll r = 0;
    for (int i = 1; i <= n; i++) {
        r += W[i] * (*g[i].begin());
    }
    return r;
}

void Solve() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            Dist[i][j] = G[i][j];
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                Dist[i][j] = min(Dist[i][j], Dist[i][k] + Dist[k][j]);

    for (int i = 1; i <= n; i++) p[i] = i;
    shuffle(p + 1, p + n + 1, mt);

    double T = T0;
    for (int i = 1; i <= k; i++) add(p[i]);
    ll D = calc();
    while (T > T1) {
        for (int t = 1; t <= L; t++) {
            int &u = p[Rnd(1, k)];
            int &v = p[Rnd(k + 1, n)];
            add(v);
            del(u);
            ll r = calc();
            if (r < D || (U(mt) < exp(-(r - D) / T))) {
                D = r;
                swap(u, v);
            } else {
                add(u);
                del(v);
            }
            Log << D << "\n";
            if (D < ans) {
                ans = D;
                for (int i = 1; i <= k; i++) ansp[i] = p[i];
            }
        }
        T *= a;
    }
    fill(p + k + 1, p + n + 1, 0);
}

int main() {
    mt.seed(chrono::system_clock::now().time_since_epoch().count());

    GIn >> n >> m >> k;
    for (int i = 1; i <= n; i++) GIn >> W[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j) G[i][j] = INF;
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        GIn >> u >> v >> w;
        G[u][v] = w;
        G[v][u] = w;
    }

    for (int i = 1; i <= T; i++) Solve();
    cout << ans << endl;

    for (int i = 1; i <= k; i++) {
        Ans << ansp[i] << " ";
    }
    Ans << "\n";

    return 0;
}