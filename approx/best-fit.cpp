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

bool comp_vectors(const std::vector<long long>& old_can, const std::vector<long long>& new_can,
                 const std::vector<long long>& was, const std::vector<long long>& b) {
    double tot_old = 0, tot_new = 0;
    for (size_t i = 0; i < b.size(); ++i) {
        tot_old += static_cast<double>(b[i] - was[i] - old_can[i]) / static_cast<double>(b[i]);
        tot_new += static_cast<double>(b[i] - was[i] - new_can[i]) / static_cast<double>(b[i]);
    }
    return tot_new > tot_old;
}


void bestFit(size_t ind, const std::vector<long long>& b, std::vector<std::vector<size_t>>& cur_inds,
             std::vector<std::vector<long long>>& cur_vals, const std::vector<long long>& add) {

    int cur_ind = -1;
    for (size_t i = 0; i < cur_vals.size(); ++i) {
        if (is_placed(cur_vals[i], add, b)) {
            if ((cur_ind == -1) || (comp_vectors(cur_vals[cur_ind], cur_vals[i], add, b))) {
                cur_ind = i;
            }
        }
    }

    if (cur_ind != -1) {
        push_vector(cur_vals[cur_ind], add);
        cur_inds[cur_ind].push_back(ind);
    } else {
        cur_vals.push_back(add);
        cur_inds.push_back({ind});
    }
}


void solve(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& opt_ans) {
    std::vector<std::vector<long long>> cur_vals(1, std::vector<long long>(b.size()));
    opt_ans.push_back({});


    for (size_t i = 0; i < a.size(); ++i) {
        bestFit(i, b, opt_ans, cur_vals, a[i]);
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
