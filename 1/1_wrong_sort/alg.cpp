
#include "../../lib.hpp"

void wrong_sort(
    vector<size_t>& a)
{
    for (int i = 0; i < a.size() - 1; ++i)
        for (int j = i; j < a.size() - 1; ++j)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

int main()
{
    vector<size_t> a{};
    size_t         size(0);

    cout << " input size: ";
    cin >> size;
    if (size <= 0) return 1;

    if (size == 1 || size == 2)
    {
        gen_rand(a, size, 10); // Работает
    }
    else
    {
        a = vector<size_t>(size, 0); // Контрпример
        a[0] = 2;
        a[1] = 1;
    }

    cout << "before sort: " << a;
    wrong_sort(a);
    cout << "    " << (check(a) ? "correct: " : "  wrong: ") << a;

    return 0;
}
