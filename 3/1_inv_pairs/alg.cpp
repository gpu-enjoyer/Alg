
#include "../../lib.hpp"


// В худшем случае массив (n)
//  разделяется на log(n) уровнях:
//   на каждом уровне O(n) операций.


size_t __merge_count(
	vector<int> &a,
	vector<int> &buf,
	size_t left,
	size_t middle,
	size_t right)
{
	size_t
		i(left),
		j(middle),
		k(left),
		inv(0);

	// Массив разделен на два отсортированных.

	while (i < middle && j < right)
	{
		if (a[i] <= a[j])
		{
			// Не инверсия
			buf[k++] = a[i++];
		}
		else
		{
			buf[k++] = a[j++];
			// Все большие значения – тоже инверсии:
			inv += (middle - i);
		}
	}

	// Либо i, либо j останавливается.
	//  Для кого-то из них:
	while (i < middle) buf[k++] = a[i++];
	while (j < right)  buf[k++] = a[j++];

	for (size_t t = left; t < right; ++t)
		a[t] = buf[t];

	// Теперь a[ left .. right ] отсортирован.

	return inv;
}

size_t __count_invs(
	vector<int> &a,
	vector<int> &buf,
	size_t left,
	size_t right)
{
	if (right - left <= 1) return 0;

	// Стоит рассмотреть различные pos
	size_t pos = left + (right - left) / 2;
	size_t inv = 0;

	inv +=  __count_invs(a, buf, left, pos        );
	inv +=  __count_invs(a, buf, pos,  right      );
	inv += __merge_count(a, buf, left, pos,  right);

	return inv;
}

size_t count_invs(
	vector<int> &a)
{
	vector<int> buf(a.size());
	return      __count_invs(a, buf, 0, a.size());
}


int main()
{
	vector<int> a(10);
	gen_rand(a, a.size(), 30);

	cout << "\n{" << a << "}\n" 
		<< " count_invs(a) = " << count_invs(a) << "\n\n";

	return 0;
}
