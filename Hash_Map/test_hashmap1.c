#define _POSIX_C_SOURCE 200809L
#include "hashmap.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <json-c/json.h>

#define STR_ARRAY_SIZE (2048)
/**
 * struct str_list - array of strings
 * @len: number of strings in the array
 * @array: an array of strings
 */
struct str_list
{
	size_t len;
	char *array[STR_ARRAY_SIZE];
} keys = {STR_ARRAY_SIZE, {NULL}}, values = {STR_ARRAY_SIZE, {NULL}};

HashMap *hm = NULL;

/**
 * parse_json_list - p
 * @json_file: path to a json file
 * @list: a struct of an array to populate with strings
 *
 * Return: number of strings parsed, -1 on error.
 */
ssize_t parse_json_list(const char *json_file, struct str_list *list)
{
	json_object *node = NULL, *root = json_object_from_file(json_file);
	size_t n = 0, i = 0;

	if (!root || !json_object_is_type(root, json_type_array))
		return (-1);

	n = json_object_array_length(root);
	list->len = 0;
	for (i = 0; i < n && i < STR_ARRAY_SIZE; i++)
	{
		node = json_object_array_get_idx(root, i);
		if (!node)
		{
			json_object_put(root);
			return (-1);
		}

		if (json_object_is_type(node, json_type_string))
		{
			list->array[list->len] = strdup(json_object_get_string(node));
			list->len++;
		}
	}

	json_object_put(root);
	return ((ssize_t)list->len);
}

/**
 * setup - initialise some variables
 */
void setup(void)
{
	hm = hashmap_create(1024);
	parse_json_list(
		"/home/line/Github_Repositories/World_of_C/Hash_Map/random_strings0.json",
		&keys);
	parse_json_list(
		"/home/line/Github_Repositories/World_of_C/Hash_Map/random_strings0.json",
		&values);
}

/**
 * teardown - clean up variables
 */
void teardown(void)
{
	size_t i = 0;

	hashmap_delete(hm);
	hm = NULL;
	for (i = 0; keys.array[i]; i++)
	{
		free(keys.array[i]);
		keys.array[i] = NULL;
	}

	for (i = 0; values.array[i]; i++)
	{
		free(values.array[i]);
		values.array[i] = NULL;
	}

	keys.len = STR_ARRAY_SIZE;
	values.len = STR_ARRAY_SIZE;
}

TestSuite(multiple_inputs, .init = setup, .fini = teardown);

Test(multiple_inputs, test_several_random_keys_and_values,
	 .description = "insert(randomkey, randomvalue) * n", .timeout = 0)
{
	Bucket *b = NULL;
	size_t i = 0;

	for (i = 0; keys.array[i] && values.array[i]; i++)
		hashmap_insert(hm, keys.array[i], values.array[i]);

	for (i = 0; keys.array[i] && values.array[i]; i++)
	{
		b = hashmap_get(hm, (str_literal)keys.array[i]);

		cr_assert(eq(str, b->key, keys.array[i]));
		cr_assert(eq(str, b->value, values.array[i]));
	}
}