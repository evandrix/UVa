#include <bits/stdc++.h>

using namespace std;

int v[128], p[128], idx[128];

bool cmp(int a, int b)
{
	return v[a] > v[b] || (v[a] == v[b] && a < b);
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, q, sum = 0;
		scanf("%d %d", &q, &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &v[i]);
			sum += v[i];
			p[i] = 0;
			idx[i] = i;
		}
		if (sum < q)
		{
			puts("IMPOSSIBLE");
		}
		else
		{
			sort(idx, idx + n, cmp);
			while (q)
			{
				int cp;
				for (cp = n; cp--;)
					if (v[idx[cp]])
					{
						break;
					}
				int pm = 0, qp = v[idx[cp]], tp = qp * (++cp);
				if (tp > q)
				{
					qp = q / cp;
					pm = q % cp;
					tp = q;
				}
				for (int i = 0; i < cp; ++i)
				{
					int x = idx[i];
					if (v[x] > 0)
					{
						p[x] += qp;
						v[x] -= qp;
						if (pm && v[x])
						{
							p[x]++, v[x]--, pm--;
						}
					}
				}
				q -= tp;
			}
			for (int i = 0; i < n; ++i)
			{
				if (i)
				{
					putc(32, stdout);
				}
				printf("%d", p[i]);
			}
			putc(10, stdout);
		}
	}
	return 0;
}
