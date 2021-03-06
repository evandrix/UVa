#include <bits/stdc++.h>

using namespace std;

/**
 * Fix the position of one 3x3 block at a time, then try all
 * permutations within that block and proceed to the next 3x3-block.
 * Keep a partial remapping of the digits as we go, and break whenever
 * inconsistencies are found.
 */

int b1[9][9], b2[9][9];
int brperm[3], bcperm[3];
int rperm[3][3], cperm[3][3];

bool tryperm(int blockrow, int blockcol, int *digmap)
{
	if (blockcol == 3)
	{
		++blockrow, blockcol = 0;
	}
	if (blockrow == 3)
	{
		return true;
	}
	for (int i = 0; i < 3; ++i)
		if (blockcol == 0 && brperm[i] == -1 ||
				blockcol > 0 && brperm[i] == blockrow)
			for (int j = 0; j < 3; ++j)
				if (blockrow == 0 && bcperm[j] == -1 ||
						blockrow > 0 && bcperm[j] == blockcol)
				{
					int rp[3], cp[3];
					brperm[i] = blockrow;
					bcperm[j] = blockcol;
					for (int k = 0; k < 3; ++k)
					{
						rp[k] = cp[k] = k;
					}
					// Check if any of these permutations have already been fixed.
					if (blockrow > 0)
					{
						memcpy(cp, cperm[blockcol], sizeof(cp));
					}
					if (blockcol > 0)
					{
						memcpy(rp, rperm[blockrow], sizeof(rp));
					}
					do
					{
						do
						{
							// Check that row and column permutations for this block
							// are consistent with the current remapping of the digits.
							bool inconsistent = false;
							int ndigmap[10];
							memcpy(ndigmap, digmap, sizeof(int) * 10);
							for (int r = 0; !inconsistent && r < 3; ++r)
								for (int c = 0; !inconsistent && c < 3; ++c)
								{
									int v1 = b1[3 * blockrow + r][3 * blockcol + c];
									int v2 = b2[3 * i + rp[r]][3 * j + cp[c]];
									if (v2)
									{
										if (ndigmap[v2] && ndigmap[v2] != v1)
										{
											inconsistent = true;
										}
										ndigmap[v2] = v1;
									}
								}
							memcpy(cperm[blockcol], cp, sizeof(cp));
							memcpy(rperm[blockrow], rp, sizeof(rp));
							if (!inconsistent &&
									tryperm(blockrow, blockcol + 1, ndigmap))
							{
								return true;
							}
						} while (blockrow == 0 && next_permutation(cp, cp + 3));
					} while (blockcol == 0 && next_permutation(rp, rp + 3));
					// Restore block permutations
					if (blockcol == 0)
					{
						brperm[i] = -1;
					}
					if (blockrow == 0)
					{
						bcperm[j] = -1;
					}
				}
	return false;
}

int main()
{
	int T, i;
	scanf("%d", &T);
	for (; T--;)
	{
		for (i = 0; i < 81; ++i)
		{
			scanf(" %1d", b1[i / 9] + i % 9);
		}
		for (i = 0; i < 81; ++i)
		{
			scanf(" %1d", b2[i / 9] + i % 9);
		}
		// Only need to check rotation by 90 degrees since additional
		// rotation by 180 degrees can be achieved by the permutations.
		for (i = 0; i < 2; ++i)
		{
			int digmap[10];
			int nb2[9][9];
			for (int r = 0; r < 9; ++r)
				for (int c = 0; c < 9; ++c)
				{
					nb2[r][c] = b2[c][8 - r];
				}
			memcpy(b2, nb2, sizeof(b2));
			memset(brperm, -1, sizeof(brperm));
			memset(bcperm, -1, sizeof(bcperm));
			memset(digmap, 0, sizeof(digmap));
			if (tryperm(0, 0, digmap))
			{
				printf("Yes\n");
				break;
			}
		}
		if (i == 2)
		{
			printf("No\n");
		}
	}
	return 0;
}
