/**
 * Author: Niklas Leinert
 * License: MIT
 * Source: me
 * Description: Grid Hashing
 */

#pragma once

struct GridHasher {
    int P, Q, MOD;
    std::vector<std::vector<int>> h;
    std::vector<int> powP, powQ;

    GridHasher(const std::vector<std::string>& grid, int _P, int _Q, int _MOD) {
        P = _P;
        Q = _Q;
        MOD = _MOD;
        int n = (int) grid.size();
        int m = (int) grid[0].size();
        h.assign(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                h[i][j] = 1LL * Q * h[i - 1][j] % MOD;
                h[i][j] = (h[i][j] + 1LL * P * h[i][j - 1]) % MOD;
                h[i][j] = (h[i][j] - 1LL * P * Q % MOD * h[i - 1][j - 1]) % MOD;
                h[i][j] = (h[i][j] + (grid[i - 1][j - 1] - 'a' + 1) + MOD) % MOD;
            }
        }
        powP.assign(m + 1, 1); powQ.assign(n + 1, 1);
        for (int i = 1; i <= m; ++i) 
            powP[i] = 1LL * powP[i - 1] * P % MOD;
        for (int i = 1; i <= n; ++i) 
            powQ[i] = 1LL * powQ[i - 1] * Q % MOD;
    }

    int getHash(int a, int b, int x, int y) {
        int ans = h[x][y];
        ans = (ans - 1LL * powQ[x - a] * h[a][y]) % MOD;
        ans = (ans - 1LL * powP[y - b] * h[x][b]) % MOD;
        ans = (ans + 1LL * powQ[x - a] * powP[y - b] % MOD * h[a][b]) % MOD;
        if (ans < 0) ans += MOD;
        return ans;
    }
};
