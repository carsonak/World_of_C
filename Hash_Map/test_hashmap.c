#include "hashmap.c"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

HashMap *hm = NULL;

/**
 * setup - initialise some variables
 */
void setup(void)
{
	hm = hash_map_create(1024);
}

/**
 * teardown - clean up variables
 */
void teardown(void)
{
	hash_map_delete(hm);
	hm = NULL;
}

TestSuite(null_inputs, .init = setup, .fini = teardown);

Test(null_inputs, test_insert_nullkey_nullvalue,
	 .description = "insert(NULL, NULL)", .timeout = 0)
{
	Bucket *b = NULL;

	hash_map_insert(hm, NULL, NULL);
	b = hash_map_get(hm, NULL);
	cr_assert();
}
