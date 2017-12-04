#include <bits/stdc++.h>
using namespace std;
int n;
char c[1005][1005];
int g[1005][1005];

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", c[i] + 1);
    }
}

void sol(){
    for (int i = 0; i <= n + 1; ++i) {
        c[i][n + 1] = c[i][0] = c[n + 1][i] = c[0][i] = 'X';
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (c[i][j] == 'X') {
                g[i][j] = 5;
            } else {
                int x = 0;
                x|=(1 << g[i-1][j-1]);
                x|=(1 << g[i][j-1]);
                x|=(1 << g[i-1][j]);
                g[i][j] = 0;
                while (x&1) {
                    x >>= 1;
                    ++g[i][j];
                }
            }
            if (c[i][j] == 'K') {
                ans ^= g[i][j];
            }
        }
    }
    if (ans) {
        int win = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (c[i][j] == 'K') {
                    win += (c[i][j-1] != 'X' && (ans^g[i][j]^g[i][j-1]) == 0);
                    win += (c[i-1][j] != 'X' && (ans^g[i][j]^g[i-1][j]) == 0);
                    win += (c[i-1][j-1] != 'X' && (ans^g[i][j]^g[i-1][j-1]) == 0);
                }
            }
        }
        printf("WIN %d\n", win);
    } else {
        printf("LOSE\n");
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        input();
        sol();
    }
    return 0;
}