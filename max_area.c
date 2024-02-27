#include <stdio.h>

/**
 * maxArea - finds the max area between two lines inside a graph
 * @height: int array (the graph)
 * @heightSize: length of the int array
 *
 * Return: max area
 */
int maxArea(int *height, int heightSize)
{
	int g = 0, max_mid = 0;
	int mA_right = heightSize - 1, mA_left = 0, area = 0;

	/*Find the largest value in the array*/
	for (g = 0; g < heightSize; g++)
		if (height[g] > height[max_mid])
			max_mid = g;

	if (height[max_mid] == 0)
		return (0);

	/*Check the left side of the array*/
	for (g = 0; g < max_mid; g++)
	{
		if (height[g] * (max_mid - g) > area)
		{
			mA_left = g;
			area = height[mA_left] * (max_mid - mA_left);
		}
	}

	/*Check the right side of the array*/
	area = 0;
	for (g = max_mid + 1; g < heightSize; g++)
	{
		if (height[g] * (g - max_mid) > area)
		{
			mA_right = g;
			area = height[mA_right] * (mA_right - max_mid);
		}
	}

	return (area);
}

/**
 * main - Entry point
 *
 * Return: 0
 */
int main(void)
{
	int arr[] = {1, 2, 1};

	printf("%d\n", maxArea(arr, sizeof(arr) / sizeof(arr[0])));
	return (0);
}
