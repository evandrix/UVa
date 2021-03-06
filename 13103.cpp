#include <bits/stdc++.h>

using namespace std;

int main()
{
	long long N;
	int K, A[128];
	while (scanf("%lld %d", &N, &K) == 2)
	{
		for (int i = 0; i < K; i++)
			scanf("%d", &A[i]);
		sort(A, A + K);

		int one = 0;
		for (int i = 0; i < K; i++)
		{
			if ((N >> A[i]) & 1)
			{
				one++;
				N ^= 1LL << A[i];
			}
		}
		long long ret = 0;
		for (int i = (1 << K) - 1; i >= 0; i--)
		{
			if (__builtin_popcount(i) != one)
				continue;
			long long tN = N;
			for (int j = 0; j < K; j++)
			{
				if ((i >> j) & 1)
					tN |= 1LL << A[j];
			}
			if (tN % 7 == 0)
				ret = max(ret, tN);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
