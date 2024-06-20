#include "FAM.h"

/*This code does not work as expected as FAMs can't be nested.*/

/**
 * main - FAM struct nesting an FAM struct
 *
 * Return: 0
 */
int main(void)
{
	char *my_str = "NULL";
	size_t i = 0, cat_len = 10, s_len = strlen(my_str) + 1;
	struct Catalogue_nested *cat = NULL;

	cat = malloc(sizeof(*cat) + (sizeof(*cat->list) + (sizeof(*cat->list->str) * s_len)) * cat_len);

	printf("sizeof(struct Catalogue_nested): %zu\n", sizeof(*cat));
	printf("sizeof(struct String): %zu\n", sizeof(struct String));
	cat->size = cat_len;
	for (; i < cat->size; i++)
	{
		cat->list[i].len = s_len;
		strcpy(cat->list[i].str, my_str);
	}

	for (i = 0; i < cat->size; i++)
	{
		printf("cat.list[%ld]\n", i);
		printf("len: %ld\n", cat->list[i].len);
		printf("str: %s\n", cat->list[i].str);
	}

	free(cat);
	return (0);
}
