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


void nextFit(size_t ind, const std::vector<long long>& b, std::vector<std::vector<size_t>>& cur_inds,
             std::vector<long long>& cur_val, const std::vector<long long>& add) {
    if (is_placed(cur_val, add, b)) {
        push_vector(cur_val, add);
        cur_inds.back().push_back(ind);
    } else {
        cur_val = add;
        cur_inds.push_back({ind});
    }
}


void solve(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& opt_ans) {
    std::vector<long long> cur_val(b.size());
    opt_ans.push_back({});

    for (size_t i = 0; i < a.size(); ++i) {
        nextFit(i, b, opt_ans, cur_val, a[i]);
    }
}



int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
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

    std::vector<std::vector<size_t>> opt_ans;
    solve(a, b,opt_ans);

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
