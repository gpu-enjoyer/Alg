
#include "../../lib.hpp"


vector<size_t> counts(
	vector<size_t>& a,
	const size_t    K)
{
	vector<size_t> counts(K, 0);
	for (size_t i = 0; i < a.size(); ++i)
		++counts[a[i]];
	return counts;
}

void countsPrefixSum(
	vector<size_t>& counts)
{
	size_t sum = 0;
	for (size_t i = 0; i < counts.size(); ++i) {
		sum += counts[i];
		counts[i] = sum;
	}
}


int main()
{
	size_t N, K, Q;
	cout << "\n{N=size, K=max.val, Q=req.num} <- ";
	cin >> N >> K >> Q;

	vector<size_t> a(N);
	cout << "{array} in {0..K-1}            <- ";
	for (size_t i = 0; i < N; ++i)
		cin >> a[i];

	vector<size_t> sums = counts(a, K);
	countsPrefixSum(sums);

	for (size_t i = 0; i < Q; ++i)
	{
		size_t l, r;
		cout << "\n{l, r} borders in {0..inf}     <- ";
		cin >> l >> r;

		cout << "result                         -> ";
		if (l >= K) 
			cout << 0 << "\n\n";
		else if (l == 0)
			cout << sums[min(r, K - 1)] << "\n\n";
		else
			cout << sums[min(r, K - 1)] - sums[l - 1] << "\n\n";
	}

	return 0;
}
