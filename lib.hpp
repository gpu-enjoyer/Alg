
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;


template <typename T>
bool check(
    const vector<T>& a)
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
void gen_rand(
    vector<T>& a,
    size_t size)
{
    mt19937 mt(time(nullptr));
    a.resize(size);
    for (size_t i = 0; i < a.size(); ++i)
		a[i] = mt();
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


template <
    typename  SortFunc,
    typename  T,
    typename... Args
>
double getTime(
    SortFunc   sort_func,
    vector<T>  a,
    Args...    args)
{
	auto time0 = steady_clock::now();
	if (!sort_func(a, args...)) 
        throw std::runtime_error("Wrong sort");
	auto time1 = steady_clock::now();
	duration<double> time = time1 - time0;
	return time.count();
}




// getStdTime(std::sort, a)
// getStdTime(std::stable_sort, a)
// template <
//     typename SortFunc,
//     typename T
// >
// double getStdTime(
//     SortFunc  sort_func,
//     vector<T> a)
// {
//     return getTime(sort_func, a, a.begin(), a.end());
// }



// template<string, T>
// struct Line
// {
// 	string _txt  = "txt";
// 	T      _var  = 0;
// 	Line(string t, T v): _txt(t), _var(v) {}
// 	Line() = default;
// };

// struct Message
// {
// 	int   l_num = 4;
// 	Line* lines = new Line[l_num];
//  Message();
// };
