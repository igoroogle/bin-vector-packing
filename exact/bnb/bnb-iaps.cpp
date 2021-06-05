#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

bool is_placed(const std::vector<long long>& a,
               const std::vector<long long>& add,
               const std::vector<long long>& b) {

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] + add[i] > b[i]) {
            return false;
        }
    }

    return true;
}

void push_vector(std::vector<long long>& a,
               const std::vector<long long>& add) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] += add[i];
    }
}

void pop_vector(std::vector<long long>& a,
                const std::vector<long long>& add) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] -= add[i];
    }
}


void dfbnb(size_t h, const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& cur_inds, std::vector<std::vector<long long>>& cur_vals,
           std::vector<std::vector<size_t>>& opt_ans) {

    if (h == a.size()) {
        if ((opt_ans.empty()) || (cur_inds.size() < opt_ans.size())) {
            opt_ans = cur_inds;
        }
        return;
    }

    for (size_t i = 0; i < cur_inds.size(); ++i) {
        if (is_placed(cur_vals[i], a[h], b)) {
            cur_inds[i].push_back(h);
            push_vector(cur_vals[i], a[h]);
            dfbnb(h + 1, a, b, cur_inds, cur_vals, opt_ans);
            pop_vector(cur_vals[i], a[h]);
            cur_inds[i].pop_back();
            if ((!opt_ans.empty()) && (cur_inds.size() + 1 >= opt_ans.size())) {
                return;
            }
        }
    }

    cur_inds.push_back({h});
    cur_vals.push_back(a[h]);
    dfbnb(h + 1, a, b, cur_inds, cur_vals, opt_ans);
    cur_vals.pop_back();
    cur_inds.pop_back();
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

    std::vector<std::vector<size_t>> cur_inds, opt_ans;
    std::vector<std::vector<long long>> cur_vals;
    dfbnb(0U, a, b, cur_inds, cur_vals, opt_ans);

    std::cout << opt_ans.size() << '\n';
    for (size_t i = 0; i < opt_ans.size(); ++i) {
        std::cout << "backet " << i + 1 << ":";
        for (size_t j = 0; j < opt_ans[i].size(); ++j) {
            std::cout << ' ' << opt_ans[i][j] + 1;
        }
        std::cout << '\n';
    }
    return 0;
}
