#include <bits/stdc++.h>

using namespace std;

char dp[35][35][6006];
int op[105], num[105], nidx = 0, oidx = 0;
int diff[6006] = {};

void dfs(int idx, int right, int sum, int flip)
{
	if (idx == nidx)
	{
		diff[sum + 3000] = 1;
		return;
	}
	if (dp[idx][right][sum + 3000])
		return;
	dp[idx][right][sum + 3000] = 1;
	// no operator
	dfs(idx + 1, right, sum + flip * op[idx] * num[idx], flip);
	if (op[idx] == -1)// add -(number
		dfs(idx + 1, right + 1, sum + (-flip) * num[idx], -flip);
	if (right >= 1)
	{// (-##### add )[+|-]
		//no operator
		dfs(idx + 1, right - 1, sum + (-flip) * op[idx] * num[idx], -flip);
		// add -(number
		if (op[idx] == -1)
			dfs(idx + 1, right, sum + flip * num[idx], flip);
	}
}

int main()
{
	char cmd[1005];
	int i, j, k;
	while (gets(cmd))
	{
		int len = strlen(cmd);
		op[0] = 1;
		nidx = 0, oidx = 1;
		for (i = 0; i < len;)
		{
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] >= '0' && cmd[i] <= '9')
			{
				int tmp = 0;
				while (cmd[i] >= '0' && cmd[i] <= '9')
					tmp = tmp * 10 + cmd[i] - '0', i++;
				num[nidx++] = tmp;
			}
			else if (cmd[i] == '+' || cmd[i] == '-')
			{
				if (cmd[i] == '+')
					op[oidx++] = 1;
				else
					op[oidx++] = -1;
				i++;
			}
		}
		memset(dp, 0, sizeof(dp));
		memset(diff, 0, sizeof(diff));
		dfs(0, 0, 0, 1);
		int ret = 0;
		for (i = 0; i <= 6000; i++)
			ret += diff[i];
		printf("%d\n", ret);
	}
	return 0;
}
