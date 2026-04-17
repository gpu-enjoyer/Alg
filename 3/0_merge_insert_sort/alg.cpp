

#include "../../lib.hpp"


//
//      (!)  Сортировка всех (n/m) массивов
//            длины (m) асимтотически занимает
//             в среднем O(n*m)
//
// (Док-во)  insertion_sort(m) = O(m^2)
//            (n/m) * O(m^2)    = O(n*m)
//

//           n * log(n / m)
//            = (число операций при слиянии) 
//             * (высота дерева разбиений каждого подмассива)
//
//           "Наибольшее значение m как функции от n, при 
//            котором модифицированный алгоритм выполняется 
//             за столько же, сколько сортировка слиянием?"
// 
//           O(n*m + n*log(n/m)) = O(n*log(n))
//            => m(n) = log(n)
//           
//           Другие аналитические функции дают худшую асимптотику.
//           
//           Если рассмотреть m(n) = const = o(log(n)),
//            асимптотика будет та же.
//             


bool __insertion_sort(
	vector<int> &a,
	int left,
	int right)
{
	for (int i = left + 1; i < right; ++i)
	{
		int max = a[i];
		int j   = i - 1;

		// Освобождаем место, пока 'a[j]' больше 'max',
		//  либо пока 'j' не дойдет до 'left'

		while (left <= j && a[j] > max)
		{
			a[j + 1] = a[j]; // 
			--j;
		}

		//  a[j] == a[j + 1]
		//  a[j] <= max

		a[j + 1] = max;
	}

	if (!check(a)) return false;
	return true;
}


void __merge(
	vector<int> &a,
	int left,
	int middle,
	int right,
	vector<int> &buf)
{
	int i(left), j(middle), k(left);

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

bool __merge_insertion_sort(
	vector<int>  &a,
	const int    left,
	const int    right,
	const size_t m,
	vector<int>  &buf)
{
	int len = right - left;

	if (len <= 1) return true;
	if (len <= m) return __insertion_sort(a, left, right);

	int pos = left + len / 2;

	__merge_insertion_sort(a, left, pos,   m,     buf);
	__merge_insertion_sort(a, pos,  right, m,     buf);
	               __merge(a, left, pos,   right, buf);

	if (!check(a)) return false;
	return true;
}

bool merge_insertion_sort(
	vector<int> &a,
	size_t      m)
{
	vector<int> buf(a);
	return __merge_insertion_sort(a, 0, (int)a.size(), m, buf);
}



int main()
{
	const size_t sizes[3]      = {1'000, 10'000, 100'000};
	const size_t thresholds[6] = {10, 300, 500, 1'000, 9'999, 50'000};
	const size_t repeats       = 3;


	for (size_t s : sizes)
	{
		vector<int>  base;
		vector<int>  a0, a1, a2;
		double       t0, t1, t2;

		cout << "SIZE = " << s << ": \n\n";

		for (size_t m : thresholds)
		{
			t0 = 0; t1 = 0; t2 = 0;

			for (int r = 0; r < repeats; ++r)
			{
				gen_rand(base, s);

				a0 = base;
				a1 = base;
				a2 = base;

				// std::sort
				{
					auto start = steady_clock::now();
					std::sort(a0.begin(), a0.end());
					auto end = steady_clock::now();
					t0 += duration<double>(end - start).count();
				}

				// std::stable_sort (сохраняет порядок)
				{
					auto start = steady_clock::now();
					std::stable_sort(a1.begin(), a1.end());
					auto end = steady_clock::now();
					t1 += duration<double>(end - start).count();
				}

				// merge_insertion_sort
				t2 += get_time(merge_insertion_sort, a2, m);
			}

			cout
				<< " T(merge_ins, m = " 
				<< (m < 10    ? " " : "")
				<< (m < 100   ? " " : "")
				<< (m < 1000  ? " " : "")
				<< (m < 10000 ? " " : "")
				<< m << ") .. " 
				<< t2 / repeats << '\n';
		}
		cout
			<< " T(std) ................... " << t0 / repeats << '\n'
			<< " T(stable) ................ " << t1 / repeats << "\n\n";
	}
}
