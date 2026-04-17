
#include "../../lib.hpp"

typedef unsigned long ulong;


// O(n + n*log(n)) = O(n*log(n))
void __merge(
	vector<ulong> &a,
    vector<ulong> &buf,
	size_t left,
	size_t middle,
	size_t right)
{
	size_t i(left), j(middle), k(left);

	while (i < middle && j < right)
	{
		if (a[i] <= a[j]) buf[k++] = a[i++];
		else              buf[k++] = a[j++];
	}
	while (i < middle)    buf[k++] = a[i++];
	while (j < right)     buf[k++] = a[j++];

	for (int t = left; t < right; ++t)
		a[t] = buf[t];
}

// O(n * log(n))
void __merge_sort(
    vector<ulong>& a,
    vector<ulong>& buf,
    size_t left,
    size_t right)
{
    // [left, right)
    if (right - left <= 1) return;

    size_t mid = left + (right - left) / 2;

    __merge_sort(a, buf, left, mid);
    __merge_sort(a, buf, mid,  right);
            __merge(a, buf, left, mid, right);
}

bool merge_sort(
    vector<ulong>& a)
{
    vector<ulong> buf(a);
    __merge_sort(a, buf, 0, a.size());
    if (!check(a)) return false;
    return true;
}

void find_sums(
    vector<ulong>& a,
    ulong sum)
{
    ulong i     = 0;
	ulong j     = a.size() - 1;

	bool  found = false;

	while (i < j)
	{
		ulong _sum = a[i] + a[j];

		if (_sum == sum)
		{
			cout << ' ' << a[i] << " " << a[j] << "\n";
			found = true;
			++i;
			--j;
		}
		else if (_sum < sum) ++i;
		else                 --j;
	}

	if (!found)
		cout << " no pairs\n";
}


int main()
{
    vector<ulong> a;
    gen_rand_unique(a, 10, 200);

    ulong sum = 0;
    
    cout << "       before sort: " << a << '\n';
    merge_sort(a);
    cout << "        after sort: " << a << '\n';
    cout << "               sum: ";
    cin >> sum;
    cout << "count_sums(a, sum): " << '\n';
    find_sums(a, sum);

    return 0;
}
