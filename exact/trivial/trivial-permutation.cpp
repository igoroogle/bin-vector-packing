#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

int next_fit(const std::vector<int>& per,
             const std::vector<std::vector<long long>>& a, const std::vector<long long>& b) {

    int n = per.size(), d = b.size();
    std::vector<long long> cur_cap(d);
    int ans = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            if (cur_cap[j] + a[per[i]][j] > b[j]) {
                ++ans;
                std::fill(cur_cap.begin(), cur_cap.end(), 0LL);
                break;
            }
        }

        for (int j = 0; j < d; ++j) {
            cur_cap[j] += a[per[i]][j];
        }
    }

    return ans;
}

void next_fit_backets(const std::vector<int>& per,
             const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
                std::vector<std::vector<int>>& ans) {

    int n = per.size(), d = b.size();
    std::vector<long long> cur_cap(d);
    ans.clear();
    ans.push_back(std::vector<int>());


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            if (cur_cap[j] + a[per[i]][j] > b[j]) {
                ans.push_back(std::vector<int>());
                std::fill(cur_cap.begin(), cur_cap.end(), 0LL);
                break;
            }
        }

        for (int j = 0; j < d; ++j) {
            cur_cap[j] += a[per[i]][j];
        }
        ans.back().push_back(per[i] + 1);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, d;
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

    std::vector<int> per(n);

    for (int i = 0; i < n; ++i) {
        per[i] = i;
    }

    std::vector<int> best_per = per;
    int ans = n;

    do {
        int can_ans = next_fit(per, a, b);
        if (can_ans < ans) {
            ans = can_ans;
            best_per = per;
        }
    } while (std::next_permutation(per.begin(), per.end()));


    std::cout << ans << '\n';
    std::vector<std::vector<int>> vector_ans;
    next_fit_backets(best_per, a, b, vector_ans);

    for (size_t i = 0; i < vector_ans.size(); ++i) {
        std::cout << "backet " << i + 1 << ":";
        for (auto& cur : vector_ans[i]) {
            std::cout << ' ' << cur + 1;
        }
        std::cout << '\n';
    }
    return 0;
}
