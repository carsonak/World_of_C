#include "hashmap.h"

static size_t hash_djb2(str_literal str) ATTR_NONNULL;

/**
 * hash_map_create - alloc memory for a hash map.
 * @size: size of the hash map.
 *
 * Return: pointer to the hash map success, NULL on failure.
 */
HashMap *hash_map_create(size_t size)
{
	HashMap *table = size ? calloc(1, sizeof(*table)) : NULL;

	if (table)
	{
		table->size = size;
		table->array = calloc(size, sizeof(*(table->array)));
		if (!table->array)
		{
			free(table);
			table = NULL;
		}
	}

	if (!table)
		perror("Failed to allocate memory for HashMap");

	return (table);
}

/**
 * hash_map_delete - frees memory allocated to a hash table
 * @hm: pointer to a hash table struct
 */
void hash_map_delete(HashMap *hm)
{
	Bucket *front_foot = NULL, *back_foot = NULL;
	size_t i = 0;

	if (!hm)
		return;

	for (i = 0; hm->array && i < hm->size; i++)
	{
		if (!hm->array[i])
			continue;

		front_foot = hm->array[i];
		while (front_foot)
		{
			back_foot = front_foot;
			front_foot = front_foot->next;
			free(back_foot->key);
			free(back_foot->value);
			free(back_foot);
		}
	}

	free(hm->array);
	free(hm);
}

/**
 * hash_djb2 - produces a unique number from a string using djb2 algorithm.
 * @str: the string to hash.
 *
 * Return: an int representing the hash.
 */
static size_t hash_djb2(str_literal str)
{
	size_t hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash);
}

/**
 * get_index - calculates a string's index in a hash table using djb2
 * @key: the string
 * @size: size of the hash table
 *
 * Return: the index for the key
 */
size_t get_index(str_literal key, size_t size)
{
	if (key && size)
		return (hash_djb2(key) % size);

	return (0);
}

/**
 * hash_map_get - retrieves the bucket associated with a key
 * @hm: a pointer to a hashmap struct
 * @key: key of the value
 *
 * Return: pointer to the bucket, NULL if not found
 */
Bucket *hash_map_get(const HashMap *hm, str_literal key)
{
	Bucket *walk = NULL;
	size_t hash = 0;

	if (!hm)
		return (NULL);

	hash = key ? hash_djb2(key) : 0;
	walk = hm->array[get_index(key, hm->size)];
	while (walk)
	{
		if (walk->hash == hash)
			if (!strcmp((const char *)key, walk->key))
				return (walk);

		walk = walk->next;
	}

	return (NULL);
}

/**
 * add_bucket_head - adds a new node to the beginning of a linked list
 * @h: address of the pointer to the first node
 * @val: data to be added
 * @key: more data
 *
 * Return: pointer to the just created node
 */
void *add_bucket_head(Bucket **h, const char *key, const char *val)
{
	Bucket *nw_node = NULL;

	if (!h)
		return (NULL);

	nw_node = calloc(1, sizeof(*nw_node));
	if (!nw_node)
		return (NULL);

	nw_node->hash = key ? hash_djb2((str_literal)key) : 0;
	nw_node->key = strdup(key);
	nw_node->value = strdup(val);
	if ((val && !nw_node->value) || (key && !nw_node->key))
	{
		free(nw_node->value);
		free(nw_node->key);
		free(nw_node);
		return (NULL);
	}

	nw_node->next = *h;
	*h = nw_node;
	return (nw_node);
}

/**
 * hash_map_insert - updates a hash table with an element
 * @hm: pointer to to a hash table struct
 * @key: key of the value
 * @value: data to be added
 *
 * Return: 1 on success, 0 on failure
 */
int hash_map_insert(HashMap *hm, const char *key, const char *value)
{
	size_t id = 0;
	Bucket *b = NULL;

	if (!hm || !hm->size || !hm->array)
		return (0);

	b = hash_map_get(hm, (str_literal)key);
	if (b)
	{
		free(b->value);
		b->value = strdup(value);
		if (value && !b->value)
			return (0);
	}
	else
	{
		id = get_index((str_literal)key, hm->size);
		if (!add_bucket_head(&(hm->array[id]), key, value))
			return (0);
	}

	return (1);
}

/**
 * hash_map_print - prints out all key value pairs of a hash table
 * @hm: pointer to a struct containing information about the struct
 */
void hash_map_print(const HashMap *hm)
{
	Bucket *walk = NULL;
	size_t i = 0;
	char comma = '\0', space = '\0';

	if (!hm)
		return;

	printf("{");
	for (i = 0; i < hm->size; i++)
	{
		if (comma && space)
			break;

		if (!hm->array[i])
			continue;

		walk = hm->array[i];
		while (walk)
		{
			if (comma && space)
			{
				putchar(comma);
				putchar(space);
			}

			printf("'%s': '%s'", walk->key, walk->value);
			comma = ',';
			space = ' ';
			walk = walk->next;
		}
	}

	for (; i < hm->size; i++)
	{
		if (!hm->array[i])
			continue;

		walk = hm->array[i];
		while (walk)
		{
			printf(", '%s': '%s'", walk->key, walk->value);
			walk = walk->next;
		}
	}

	printf("}\n");
}

/**
 * main - Entry point
 *
 * Return: 0
 */
int main(void)
{
	HashMap *hm;
	char *key;
	char *value;

	hm = hash_map_create(1024);
	hash_map_insert(hm, "c", "fun");
	hash_map_insert(hm, "python", "awesome");
	hash_map_insert(hm, "Bob", "and Kris love asm");
	hash_map_insert(hm, "N", "queens");
	hash_map_insert(hm, "Asterix", "Obelix");
	hash_map_insert(hm, "Betty", "Cool");
	hash_map_insert(hm, "98", "Battery Streetz");
	hash_map_print(hm);
	key = strdup("Tim");
	value = strdup("Britton");
	hash_map_insert(hm, key, value);
	key[0] = '\0';
	value[0] = '\0';
	free(key);
	free(value);
	hash_map_print(hm);
	hash_map_insert(hm, "98", "Battery Street");
	hash_map_insert(hm, "hetairas", "Bob");
	hash_map_insert(hm, "hetairas", "Bob Z");
	hash_map_insert(hm, "mentioner", "Bob");
	hash_map_insert(hm, "hetairas", "Bob Z Chu");
	hash_map_print(hm);
	hash_map_delete(hm);
	return (EXIT_SUCCESS);
}
