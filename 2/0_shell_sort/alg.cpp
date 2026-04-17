
#include "../../lib.hpp"
#include <ranges>


/// Ключ к эффективному использованию:
///  рассматривая меньший gap (делая больше проверок за проход),
///   массив должен становиться все более упорядоченным.

/// Если массив уже h2-отсортирован, а потом сделать 
///  проход с шагом h1, то после этого он останется h2-отсортированным и 
///   станет ещё h1-отсортированным.

/// Так массив накапливает порядок, 
///  а финальный проход (gap = 1) заканчивает сортировку.

/// Оптимальные параметры зависят от распределения
///  элементов в массиве.

/// Дискретных формул, описывающих распределения 
///  величин элементов массива, существует столько же, сколько 
///   есть формул для задания последовательности gaps.

/// По сути эта сортровка позволяет учитывать влияние
///  распределения величин в некотором масштабе.

/// Но не позволяет учесть реальные изменения на пересечении масштабов.
///  Стоит рассмотреть рекуррентные последовательности.

/// Оптимизация Пратта (P-adic Numbers):
///  O(n*log^2(n)) в худшем случае.

/// https://en.wikipedia.org/wiki/P-adic_number


vector<size_t> get_gaps(
	size_t lim)
{
	vector<size_t> gaps;
	for (size_t k2 = 1; k2 <= lim; k2 *= 2)
		for (size_t k6 = k2; k6 <= lim; k6 *= 3)
			gaps.push_back(k6);
	sort(gaps.begin(), gaps.end());
	return gaps;
}


bool shell_sort(
	vector<int> &a,
	const size_t lim)
{
	vector<size_t> gaps = get_gaps(lim);
	for (size_t gap : gaps | std::views::reverse) { // c++20
	// Проходим по массиву смещений.
		for (size_t i = gap; i < a.size(); ++i) {
		// insertion_sort()
			int    val = a[i];
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
	const size_t sizes[8] = {1, 2, 3, 100, 1'000, 10'000, 100'000, 1'000'000};
	const size_t repeats  = 3;

	vector<int> a0, a1, a2;
	double      t0, t1, t2;

	for (size_t size : sizes)
	{
		t0 = 0;
		t1 = 0;
		t2 = 0;

		for (size_t r = 0; r < repeats; ++r)
		{
			gen_rand(a0, size);
			a1 = a0;
			a2 = a0;

			// std::sort
			{
				auto start = steady_clock::now();
				std::sort(a0.begin(), a0.end());
				auto end = steady_clock::now();
				t0 += duration<double>(end - start).count();
			}
			// shell_sort, size
			{
				t1 += get_time(shell_sort, a1, a1.size());
			}
			// shell_sort, size/24
			{
				t2 += get_time(shell_sort, a2, std::max(a2.size() / 24, (size_t)1));
			}
		}

		cout
			<< "size ................................. " << size         << '\n'
			<< "time(std) ............................ " << t0 / repeats << '\n'
			<< "time(shell, lim = size) .............. " << t1 / repeats << '\n'
			<< "time(shell, lim = max(size/24, 1)) ... " << t2 / repeats << "\n\n";
	}
}
