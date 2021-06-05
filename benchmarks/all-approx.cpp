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

void firstFit(size_t ind, const std::vector<long long>& b, std::vector<std::vector<size_t>>& cur_inds,
              std::vector<std::vector<long long>>& cur_vals, const std::vector<long long>& add) {

    int cur_ind = -1;
    for (size_t i = 0; i < cur_vals.size(); ++i) {
        if (is_placed(cur_vals[i], add, b)) {
            cur_ind = i;
            break;
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

bool comp_vectorsBestFit(const std::vector<long long>& old_can, const std::vector<long long>& new_can,
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
            if ((cur_ind == -1) || (comp_vectorsBestFit(cur_vals[cur_ind], cur_vals[i], add, b))) {
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

bool comp_vectorsWorstFit(const std::vector<long long>& old_can, const std::vector<long long>& new_can,
                  const std::vector<long long>& was, const std::vector<long long>& b) {
    double tot_old = 0, tot_new = 0;
    for (size_t i = 0; i < b.size(); ++i) {
        tot_old += static_cast<double>(was[i] + old_can[i]) / static_cast<double>(b[i]);
        tot_new += static_cast<double>(was[i] + new_can[i]) / static_cast<double>(b[i]);
    }
    return tot_new > tot_old;
}


void worstFit(size_t ind, const std::vector<long long>& b, std::vector<std::vector<size_t>>& cur_inds,
              std::vector<std::vector<long long>>& cur_vals, const std::vector<long long>& add) {

    int cur_ind = -1;
    for (size_t i = 0; i < cur_vals.size(); ++i) {
        if (is_placed(cur_vals[i], add, b)) {
            if ((cur_ind == -1) || (comp_vectorsWorstFit(cur_vals[cur_ind], cur_vals[i], add, b))) {
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


void solveNextFit(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& opt_ans) {
    std::vector<long long> cur_val(b.size());
    opt_ans.push_back({});

    for (size_t i = 0; i < a.size(); ++i) {
        nextFit(i, b, opt_ans, cur_val, a[i]);
    }
}

void solveFirstFit(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& opt_ans) {
    std::vector<std::vector<long long>> cur_vals(1, std::vector<long long>(b.size()));
    opt_ans.push_back({});


    for (size_t i = 0; i < a.size(); ++i) {
        firstFit(i, b, opt_ans, cur_vals, a[i]);
    }
}

void solveBestFit(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& opt_ans) {
    std::vector<std::vector<long long>> cur_vals(1, std::vector<long long>(b.size()));
    opt_ans.push_back({});


    for (size_t i = 0; i < a.size(); ++i) {
        bestFit(i, b, opt_ans, cur_vals, a[i]);
    }
}

void solveWorstFit(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& opt_ans) {
    std::vector<std::vector<long long>> cur_vals(1, std::vector<long long>(b.size()));
    opt_ans.push_back({});


    for (size_t i = 0; i < a.size(); ++i) {
        worstFit(i, b, opt_ans, cur_vals, a[i]);
    }
}





int main() {
    freopen("test.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    std::cin >> t;
    for (int cur_test = 1; cur_test <= t; ++cur_test) {
        unsigned n, d;
        std::cin >> n >> d;
        std::vector<std::vector<long long>> a(n, std::vector<long long>(d));
        std::vector<long long> b(d);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < d; ++j) {
                std::cin >> a[i][j];
            }
        }

        for (int i = 0; i < d; ++i) {
            std::cin >> b[i];
        }

        std::vector<std::vector<size_t>> opt_ans;

        opt_ans.clear();
        solveNextFit(a, b, opt_ans);
        size_t opt_next_fit = opt_ans.size();

        opt_ans.clear();
        solveFirstFit(a, b, opt_ans);
        size_t opt_first_fit = opt_ans.size();

        opt_ans.clear();
        solveBestFit(a, b, opt_ans);
        size_t opt_best_fit = opt_ans.size();

        opt_ans.clear();
        solveWorstFit(a, b, opt_ans);
        size_t opt_worst_fit = opt_ans.size();

        std::cout << "test " << cur_test << "  & " << n << " & " << d << " & " << b[0] << " & ";
        std::cout << opt_next_fit << " & " << opt_first_fit << " & " << opt_best_fit << " & ";
        std::cout << opt_worst_fit << " & " << std::min(std::min(opt_next_fit, opt_first_fit),
                                                        std::min(opt_best_fit, opt_worst_fit)) << "\\\\" << std::endl;
    }

    return 0;
}
