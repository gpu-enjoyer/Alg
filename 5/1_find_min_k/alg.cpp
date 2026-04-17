
#include "../../lib.hpp"


// quick_sort() разделяет массив на части:
//  меньшие слева, большие справа.

// O(n + n/2 + n/4 + ...) = O(2n) = O(n)


int partition(
	vector<int> &a,
	int left,
	int right,
	int pivot_idx)
{
	int pivot = a[pivot_idx];
	int i = left;

	swap(a[pivot_idx], a[right]);

	for (int j = left; j < right; ++j)
		if (a[j] < pivot) {
			swap(a[i], a[j]);
			++i;
		}

	swap(a[i], a[right]);
	return i;
}

int quick_select(
	vector<int> &a,
	int left,
	int right,
	int k)
{
	while (true)
	{
		if (left == right)
			return a[left];

		int pivotIndex = left + rand() % (right - left + 1);
		pivotIndex = partition(a, left, right, pivotIndex);

		if (k == pivotIndex)
		{
			return a[k];
		}
		else if (k < pivotIndex) right = pivotIndex - 1;
		else                     left  = pivotIndex + 1;
	}
}

int main()
{
	int n, k;

	cout << "n: ";
	cin >> n;

	cout << "k: ";
	cin >> k;

	vector<int> a;
	gen_rand(a, n, 10);

	cout << a << '\n';

	srand(time(nullptr));
	int k_val = quick_select(a, 0, n - 1, k - 1);
	cout << k_val << "\n";

	return 0;
}
