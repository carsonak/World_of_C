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
	int g = 0, h = 0, area = 0, width = 0, length = 0;

	for (g = 0; g < heightSize; g++)
	{
		for (h = heightSize - 1; h > g; h--)
		{
			if (height[g] < height[h])
				width = height[g];
			else
				width = height[h];

			length = h - g;
			if (width * length > area)
				area = width * length;
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
	int arr[] = {1, 2, 1, 4, 6, 7, 3, 8, 2, 9, 3, 8, 5}; /*42*/
	/*int arr[] = {1, 2, 4, 3};*/						 /*4*/
	/*int arr[] = {1, 2, 1};*/							 /*2*/

	printf("%d\n", maxArea(arr, sizeof(arr) / sizeof(arr[0])));
	return (0);
}
