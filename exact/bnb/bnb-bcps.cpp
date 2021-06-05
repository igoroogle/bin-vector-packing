#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

struct Node {
    Node *prev, *next;
    size_t val;
    Node(size_t val) {
        prev = nullptr;
        next = nullptr;
        this->val = val;
    }
};

void destroy(Node*& cur) {
    while (cur != nullptr) {
        Node *next_cur = cur->next;
        delete(cur);
        cur = next_cur;
    }
}

void erase_elem(Node*& st, Node*& cur) {
    if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
    }

    if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
    }

    if (cur == st) {
        st = cur->next;
    }
}

void backup_elem(Node*& st, Node*& cur) {
    if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
    }

    if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
    }

    if (cur->next == st) {
        st = cur;
    }
}

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


void dfbnb(const std::vector<std::vector<long long>>& a, const std::vector<long long>& b,
           std::vector<std::vector<size_t>>& cur_inds, Node*& use_inds,
           std::vector<std::vector<size_t>>& opt_ans) {

    if ((!opt_ans.empty()) && (cur_inds.size() >= opt_ans.size())) {
        return;
    }

    if (use_inds == nullptr) {
        if ((opt_ans.empty()) || (cur_inds.size() < opt_ans.size())) {
            opt_ans = cur_inds;
        }
        return;
    }

    std::vector<long long> cur_val = a[use_inds->val];
    cur_inds.push_back({use_inds->val});

    std::stack<Node*> backup;
    Node *first_use_inds = use_inds;
    erase_elem(use_inds, use_inds);
    Node* cur_it = use_inds;

    bool flag_unique = true;
    while ((!backup.empty()) || (cur_it != nullptr)) {
        if (cur_it != nullptr) {
            if (is_placed(cur_val, a[cur_it->val], b)) {
                backup.push(cur_it);
                cur_inds.back().push_back(cur_it->val);
                push_vector(cur_val, a[cur_it->val]);
                erase_elem(use_inds, cur_it);
            }
            cur_it = cur_it->next;
            continue;
        }

        if (!backup.empty()) {
            flag_unique = false;
            dfbnb(a, b, cur_inds, use_inds, opt_ans);
            if (opt_ans.size() <= cur_inds.size() + 1) {
                while (!backup.empty()) {
                    backup_elem(use_inds, backup.top());
                    cur_inds.back().pop_back();
                    backup.pop();
                }

                backup_elem(use_inds, first_use_inds);
                cur_inds.pop_back();
                return;
            }

            cur_it = backup.top();
            backup.pop();
            backup_elem(use_inds, cur_it);
            cur_inds.back().pop_back();
            pop_vector(cur_val, a[cur_it->val]);
            cur_it = cur_it->next;
        }
    }

    if (flag_unique) {
        dfbnb(a, b, cur_inds, use_inds, opt_ans);
    }

    backup_elem(use_inds, first_use_inds);
    cur_inds.pop_back();
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

    std::vector<std::vector<size_t>> cur_inds, opt_ans;
    Node *use_inds = new Node(0);
    Node *cur = use_inds;
    for (size_t i = 1; i < n; ++i) {
        cur->next = new Node(i);
        cur->next->prev = cur;
        cur = cur->next;
    }

    dfbnb(a, b, cur_inds, use_inds, opt_ans);
    destroy(use_inds);



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
