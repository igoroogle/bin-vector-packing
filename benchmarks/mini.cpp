#include <iostream>
#include <random>

const std::vector<int> B = {100};
const std::vector<int> D = {5, 6, 7, 8, 9, 13, 22, 30, 44, 50, 55};
const std::vector<int> NUM_OF_ITEMS = {3, 5, 6, 8, 10, 12};
int main()
{
    freopen("test2.txt", "w", stdout);
    std::mt19937 gen(-430238454);
    std::uniform_int_distribution<> small(1, B[0] - 1);
    std::uniform_int_distribution<> middle(1, B[1] - 1);
    std::cout << B.size() * D.size() * NUM_OF_ITEMS.size() << '\n'; //total tests
    for (size_t cur_items = 0; cur_items < NUM_OF_ITEMS.size(); ++cur_items) {
        int n = NUM_OF_ITEMS[cur_items];
        for (size_t cur_d = 0; cur_d < D.size(); ++cur_d) {
            int d = D[cur_d];


            //gen small
            std::cout << n << ' ' << d << '\n';
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < d - 1; ++j) {
                    std::cout << small(gen) << ' ';
                }
                std::cout << small(gen) << '\n';
            }

            for (int i = 0; i < d - 1; ++i) {
                std::cout << B[0] << ' ';
            }
            std::cout << B[0] << '\n';
        }
    }
}