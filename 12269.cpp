#include <bits/stdc++.h>

using namespace std;

const int NN = 1048;
double x[NN], y[NN];
int main()
{
	int nx, ny;
	double w;
	while (scanf("%d %d %lf", &nx, &ny, &w) == 3 && (nx || ny))
	{
		for (int i = 0; i < nx; ++i)
		{
			scanf("%lf", &x[i]);
		}
		for (int i = 0; i < ny; ++i)
		{
			scanf("%lf", &y[i]);
		}
		sort(x, x + nx);
		sort(y, y + ny);
		w /= 2.0;
		if (x[0] - w > 0 || y[0] - w > 0 || x[nx - 1] + w < 75 || y[ny - 1] + w < 100)
		{
			puts("NO");
		}
		else
		{
			bool ok = 1;
			double r = 0;
			for (int i = 0; ok && i < nx; ++i)
			{
				ok &= !(x[i] - w > r);
				r = x[i] + w;
			}
			r = 0;
			for (int i = 0; ok && i < ny; ++i)
			{
				ok &= !(y[i] - w > r);
				r = y[i] + w;
			}
			if (ok)
			{
				puts("YES");
			}
			else
			{
				puts("NO");
			}
		}
	}
	return 0;
}
