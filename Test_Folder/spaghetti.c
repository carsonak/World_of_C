#include <stdio.h>
#include <string.h>

/**
 * spaghetti - how many spaghetti?
 * @s: mom's spaghetti
 *
 * Return: number of spaghettis in mom's spaghetti.
 */
int spaghetti(char *s)
{
	unsigned long int i, j, cnt = 0;
	char *tti = "spaghetti";

	for (i = 0; i < strlen(s); i++)
	{
		j = 0;

		while (s[i] == tti[j])
		{
			i++;
			j++;
		}

		if (tti[j] == '\0')
		{
			cnt++;
		}
	}

	return (cnt);
}

/**
 * main - calls spaghetti
 *
 * Return: 0 when succesfull.
 */
int main(void)
{
	char *s = "His palms spaghetti, knees weak, arms spaghetti\nThere\'s vomit on his sweater spaghetti, mom\'s spaghetti\nHe\'s nervous, but on the surface he looks calm spaghetti to drop bombs,\nBut he keeps on spaghetti what he wrote down,\nThe whole crowd goes spaghetti\nHe opens his mouth, but spaghetti won\'t come out\nHe\'s choking how, everybody\'s joking now\nspaghetti run out, time\'s up, over, bloah!\nSnap back to spaghetti, Oh there goes spaghetti\nOh, there goes spaghetti, bloah\nHe\'s so mad, but he won\'t give up spaghetti, no.\n";

	printf("%d\n", spaghetti(s));

	return (0);
}
