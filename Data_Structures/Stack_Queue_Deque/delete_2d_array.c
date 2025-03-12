#include "typedefs.h"
#include <stdlib.h>

/**
 * delete_2D_array - free a 2 dimensional array from memory.
 * @array: a 2 dimensional array.
 * @size: number of columns in the array, should be greater than 0.
 * @free_row: pointer to a function that will be used to free the rows.
 *
 * Return: NULL always.
 */
void *delete_2D_array(void **array, size_t size, delete_func *free_row)
{
	if (!array || size < 1)
		return (NULL);

	for (size_t a_i = 0; a_i < size; ++a_i)
	{
		free_row(array[a_i]);
		array[a_i] = NULL;
	}

	free(array);
	return (NULL);
}
