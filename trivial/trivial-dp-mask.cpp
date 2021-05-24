#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

bool is_placed(unsigned mask, const std::vector<std::vector<long long>>& a, const std::vector<long long>& b) {
    unsigned n = a.size(), d = b.size();
    std::vector<long long> cur_cap(d);

    for (unsigned i = 0; i < n; ++i) {
        if (!(mask & (1U << i))) {
            continue;
        }

        for (int j = 0; j < d; ++j) {
            cur_cap[j] += a[i][j];
            if (cur_cap[j] > b[j]) {
                return false;
            }
        }
    }

    return true;
}



int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    unsigned n, d;
    std::cin >> n >> d;
    std::vector<std::vector<long long>> a(n, std::vector<long long>(d));
    std::vector<long long> b(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            std::cin >> a[i][j];
        }
    }

    for (int i = 0; i < d; ++i) {
        std::cin >> b[i];
    }

    std::vector<int> dp(1U << n), prev(1U << n), placed(1U << n);

    for (unsigned mask = 1; mask < (1U << n); ++mask) {
        placed[mask] = is_placed(mask, a, b);
    }

    dp[0] = 0;
    for (unsigned mask = 1; mask < (1U << n); ++mask) {
        if (placed[mask]) {
            dp[mask] = 1;
            prev[mask] = mask;
            continue;
        }

        dp[mask] = n + 1;
        for (unsigned submask = ((mask - 1U) & mask); submask != 0U; submask = ((submask - 1U) & mask)) {
            if (!placed[submask]) {
                continue;
            }

            if (dp[submask] + dp[submask ^ mask] < dp[mask]) {
                dp[mask] = dp[submask] + dp[submask ^ mask];
                prev[mask] = submask;
            }
        }
    }

    unsigned mask = (1U << n) - 1;
    std::cout << dp[mask] << '\n';
    for (int i = 0; i < dp[(1U << n) - 1]; ++i) {
        std::cout << "backet " << i + 1 << ":";
        unsigned submask = prev[mask];
        for (unsigned j = 0; j < n; ++j) {
            if ((1U << j) & submask) {
                std::cout << ' ' << j + 1;
            }
        }
        std::cout << '\n';
        mask ^= submask;
    }
    return 0;
}
