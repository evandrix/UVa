#include <bits/stdc++.h>

using namespace std;

struct event
{
	int t, v;
	bool operator<(const event k) const
	{
		return t < k.t;
	}
} e[64808];

char map_[128];

int main()
{
	int h, m, s, N, E, X;
	char c;
	map_['E'] = 1;
	map_['X'] = -1;
	map_['?'] = 0;
	while (scanf("%d", &N) && N)
	{
		E = X = N >> 1;
		event *evt = e;
		for (int i = 0; i < N; ++i)
		{
			scanf("%2d:%2d:%2d %c", &h, &m, &s, &c);
			int t = s + 60 * m + 3600 * h;
			(*evt).t = t;
			(*evt).v = *(map_ + c);
			E -= (c == 'E');
			X -= (c == 'X');
			evt++;
		}
		sort(e, e + N);
		int cnt = 0, ans = 0;
		evt = e;
		for (int i = 0; i < N; ++i)
		{
			cnt += (*evt).v;
			if (!(*evt).v)
			{
				if (E)
				{
					--E, ++cnt;
				}
				else
				{
					--X, --cnt;
				}
			}
			if (cnt > ans)
			{
				ans = cnt;
			}
			evt++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
