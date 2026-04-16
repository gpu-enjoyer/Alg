
#include "../../lib.hpp"

bool check_updown(
    const vector<size_t>& a)
{
    bool up_exp = false;
    bool up;
    for (int i = 0; i < a.size() - 1; ++i) {
        up_exp = !up_exp;
        if (a[i] == a[i + 1])
            continue;
        up = (a[i] < a[i + 1]);
        if (up_exp && (!up))
            return false;
        if ((!up_exp) && up)
            return false;
    }
    return true;
}

void updown_sort(
    vector<size_t>& a)
{
    int  shift   = 0; 
    bool min_max = true;

    while (shift < a.size() - 1)
    {
        if (min_max)
            for (int i = a.size() - 1; i > shift; --i) {
                if (a[i - 1] > a[i])
                    swap(a[i - 1], a[i]);
            }
        else
            for (int i = a.size() - 1; i > shift; --i) {
                if (a[i - 1] < a[i])
                    swap(a[i - 1], a[i]);
            }
        ++shift;
        min_max = !min_max;
    }
}


int main()
{
    size_t size = 0;
    vector<size_t> a;

    cout << " input size: ";
    cin >> size;

    gen_rand(a, size, 10);

    cout << "before sort: " << a << '\n';
    updown_sort(a);
    cout << " after sort: " << a << '\n';

    if (!check_updown(a)) return 1;
    return 0;
}