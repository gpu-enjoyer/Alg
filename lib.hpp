
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;


bool check(
    const vector<size_t>& a)
{
    for (size_t i = 0; i < a.size() - 1; ++i)
        if (a[i] > a[i + 1]) return false;
    return true;
}

template <typename T>
void gen_rand(
    vector<T>& a,
    size_t size,
    size_t range)
{
    mt19937 mt(time(nullptr));
    a.resize(size);
    for (size_t i = 0; i < a.size(); ++i)
		a[i] = mt() % range;
}

template <typename T>
ostream& operator<<(
    ostream& os,
    const vector<T>& a)
{
    for (size_t i = 0; i < a.size(); ++i)
        os << a[i] << ' ';
    // os << '\n';
    return os;
}

template <typename SortFunc, typename... Args>
double getMyTime(
    SortFunc       mySort,
    vector<size_t> a,
    Args...        args)
{
	auto time0 = steady_clock::now();
	if (!mySort(a, args...)) 
        throw std::runtime_error("Wrong sort");
	auto time1 = steady_clock::now();
	duration<double> time = time1 - time0;
	return time.count();
}

double getStdTime(
    vector<size_t> a)
{
	auto time0 = steady_clock::now();
	sort(a.begin(), a.end());
	auto time1 = steady_clock::now();
	duration<double> time = time1 - time0;
	return time.count();
}
