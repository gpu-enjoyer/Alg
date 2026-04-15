
#include "../../lib.hpp"


vector<size_t> getIntervals(size_t lim)
{
	vector<size_t> gaps;
	for (unsigned long long p2 = 1; p2 <= lim; p2 *= 2)
		for (unsigned long long g = p2; g <= lim; g *= 3)
			gaps.push_back(g);
	sort(gaps.begin(), gaps.end());
	return gaps;
}

// Selection Sort:
//  { (size - max(size % 2, size % 3)) , ... , 6, 4, 3, 2, 1 }
bool shellSort(vector<size_t> &a)
{
	vector<size_t> gaps = getIntervals(a.size());
	size_t         g    = gaps.size();

	while (g-- > 0)
	{
		size_t gap = gaps[g];

		for (size_t i = gap; i < a.size(); ++i)
		{
			size_t tmp = a[i];
			size_t j = i;

			while (j >= gap && a[j - gap] > tmp)
			{
				a[j] = a[j - gap];
				j -= gap;
			}

			a[j] = tmp;
		}
	}

	if (!check(a)) return false;
	return true;
}


int main()
{
	const size_t sizes[6] = {1, 2, 3, 100, 10000, 100000};
	const size_t repeats  = 10;
	const size_t range    = 1000;

	double myTime  = 0;
	double stdTime = 0;

	vector<size_t> a, b;

	for (size_t size : sizes)
	{
		for (size_t r = 0; r < repeats; ++r)
		{
			gen_rand(a, size, range);
			b = a;
			myTime  += getMyTime(a, shellSort);
			stdTime += getStdTime(b);
		}

		cout
			<< "    size = " << size << '\n'
			<< " my time = " << myTime  / repeats << '\n'
			<< "std time = " << stdTime / repeats << "\n\n";
	}
}
