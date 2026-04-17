
#include "../../lib.hpp"

// O(n + n*log(n)) = O(n*log(n))

bool   merge_sort(); // n log(n)
size_t count_sums(); // n


int main()
{
    vector<size_t> a;
    gen_rand_unique(a, 10, 20);
    cout << a << '\n';

    return 0;
}
