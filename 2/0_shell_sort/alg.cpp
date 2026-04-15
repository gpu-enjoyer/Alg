
#include "../../lib.hpp"
#include <ranges>

/// Ключ к эффективному использованию:
///  рассматривая меньший gap (делая больше проверок за проход),
///   массив должен становиться все более упорядоченным.

/// Если массив уже h2-отсортирован, а потом сделать 
///  проход с шагом h1, то после этого он останется h2-отсортированным и 
///   станет ещё h1-отсортированным.

/// Из-за этого свойства массив постепенно накапливает порядок, 
///  и финальный проход с gap = 1 заканчивает сортировку.

/// Оптимальные параметры зависят от распределения
///  элементов в массиве.

/// Оптимизация Пратта:
///  O(n*log^2(n)) в худшем случае.


vector<size_t> getGaps(
	size_t lim)
{
	vector<size_t> gaps;
	for (unsigned long long k2 = 1; k2 <= lim; k2 *= 2)
		for (unsigned long long k6 = k2; k6 <= lim; k6 *= 3)
			gaps.push_back(k6);
	sort(gaps.begin(), gaps.end());
	return gaps;
}


bool shellSort(
	vector<size_t> &a,
	const size_t lim)
{
	vector<size_t> gaps = getGaps(lim);
	for (size_t gap : gaps | std::views::reverse) { // c++20
	// Проходим по массиву смещений.
		for (size_t i = gap; i < a.size(); ++i) {
		// insertion_sort()
			size_t val = a[i];
			size_t pos = i;
			while (pos >= gap && a[pos - gap] > val) {
			// Двигаем вакантное место для val.
				a[pos] = a[pos - gap];
				pos -= gap;
			}
			a[pos] = val;
		}
	}
	if (!check(a)) return false;
	return true;
}


int main()
{
	const size_t sizes[6] = {1, 2, 3, 42, 100, 10000};
	const size_t N        = 10;   // num of repeats
	const size_t R        = 1000; // range


	double stdTime     = 0;
	double myTime_lim1 = 0;
	double myTime_lim2 = 0;

	vector<size_t> a, b1, b2;

	for (size_t size : sizes)
	{
		for (size_t r = 0; r < N; ++r)
		{
			gen_rand(a, size, R);
			b1 = a;
			b2 = a;
			stdTime     += getStdTime(a);
			myTime_lim1 += getMyTime(shellSort, b1, b1.size());
			myTime_lim2 += getMyTime(shellSort, b2, std::max(b2.size() / 24, (size_t)1));
		}

		cout
			<< "size ................................ " << size            << '\n'
			<< "T(std) .............................. " << stdTime     / N << '\n'
			<< "T(shell, lim = size) ................ " << myTime_lim1 / N << '\n'
			<< "T(shell, lim = max(size / 24, 1)) ... " << myTime_lim2 / N << "\n\n";
	}
}
