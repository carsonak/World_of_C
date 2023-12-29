#include "infix.h"

/**
 * infiX_div - divides
 * @dividend: d
 * @divisor: d
 *
 * Return: string with the results, NULL on failure
 */
uint8_t *infiX_div(uint8_t *dividend, uint8_t *divisor)
{
	size_t len_dend = strlen((char *)dividend), len_sor = strlen((char *)divisor);
	size_t i = 0, len_q = 0, len_rem = 0, byte_sor = 0, byte_dend = 0;
	uint8_t *quotient = NULL, *temp = NULL, *prev = NULL;

	if (len_dend < len_sor || !len_sor)
	{
		strcpy((char *)remain, (char *)dividend);
		return (NULL);
	}
	else if (len_sor == 1)
	{
		if (divisor[0] == '0')
			return (NULL);
	}
	else if (len_dend == 1)
	{
		if (dividend[0] == '0')
		{
			strcpy((char *)remain, (char *)dividend);
			return (NULL);
		}
	}

	len_q = (len_dend - len_sor) + 1;
	quotient = calloc(len_q + 2, sizeof(*quotient));
	if (!quotient)
	{
		perror("Malloc fail");
		return (NULL);
	}

	strncpy((char *)remain, (char *)dividend, len_sor);
	for (i = 0; i < len_q; i++)
	{
		len_rem = strlen((char *)remain);
		if (i > 0 && quotient[i - 1] == '0')
		{
			remain[(len_rem - 1) + i] = dividend[(len_sor - 1) + i];
			len_rem += i;
			remain[len_rem] = '\0';
		}

		if (len_rem > len_sor)
		{
			byte_dend = strtonl((char *)remain, 2);
			byte_sor = strtonl((char *)divisor, 1);
			quotient[i] = (byte_dend / byte_sor) + '0';
			if (quotient[i] > '9')
			{
				byte_dend = strtonl((char *)remain, 3);
				byte_sor = strtonl((char *)divisor, 2);
				quotient[i] = (byte_dend / byte_sor) + '0';
			}
		}
		else if (len_rem == len_sor && strncmp((char *)remain, (char *)divisor, len_sor) >= 0)
			quotient[i] = (remain[0] - '0') / (divisor[0] - '0') + '0';
		else
		{
			quotient[i] = '0';
			continue;
		}

		temp = infiX_mul(divisor, &quotient[i]);
		if (temp)
		{
			prev = remain;
			remain = infiX_sub(remain, temp);
			free(prev);
		}
		else
			return (NULL);

		free(temp);
		temp = NULL;
	}

	return (quotient);
}
