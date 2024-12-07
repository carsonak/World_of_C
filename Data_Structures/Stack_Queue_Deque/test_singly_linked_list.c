#include "linked_lists.h"
#include "tau/tau.h"
#include <string.h>
#include <stdlib.h>

static const unsigned int MAX_STRING_SIZE = 256;

static const char original[] = "original";
static const char n1d[] = "one", n2d[] = "two", n3d[] = "three";

/**
 * fail_dup - failing duplicating function.
 * @d: unused.
 *
 * Return: NULL.
 */
static void *fail_dup(void const *const d)
{
	(void)d;
	return (NULL);
}

/**
 * dup_str - makes a copy of a string.
 * @s: pointer to the string.
 *
 * Return: pointer to the new string, NULL on failure.
 */
static char *dup_str(char const *const s)
{
	if (!s)
		return (NULL);

	unsigned int len = 0;

	while (s[len] && len <= MAX_STRING_SIZE)
		++len;

	char *const s_dup = malloc(sizeof(*s_dup) * (len + 1));

	if (s_dup)
	{
		memcpy(s_dup, s, sizeof(*s_dup) * len);
		s_dup[len] = '\0';
	}

	return (s_dup);
}

TAU_MAIN()

/*##############################*/

TEST(node_creation, new_NULL_NULL_returns_NULL)
{
	single_link_node *n = sln_new(NULL, NULL);

	REQUIRE(n != NULL, "sln_new() should return non-null pointer");
	CHECK(sln_get_data(n) == NULL, "data should be NULL");
	CHECK(sln_get_next(n) == NULL, "pointer to next node should be NULL");
	free(n);
}

TEST(node_creation, new_d_NULL_returns_node_with_unchanged_d_pointer)
{
	char input[] = "input";
	single_link_node *n = sln_new(input, NULL);

	REQUIRE(n != NULL, "sln_new() should return non-null pointer");
	CHECK(sln_get_data(n) == input, "data should point to the same object");
	CHECK(sln_get_next(n) == NULL, "pointer to next node should be NULL");
	free(n);
}

TEST(node_creation, new_NULL_f_returns_NULL)
{
	single_link_node *n = sln_new(NULL, (dup_func *)dup_str);

	REQUIRE(n != NULL, "sln_new() should return non-null pointer");
	CHECK(sln_get_data(n) == NULL, "data should be NULL");
	CHECK(sln_get_next(n) == NULL, "pointer to next node should be NULL");
	free(n);
}

TEST(node_creation, new_d_f_returns_correct_node)
{
	char input[] = "input";
	single_link_node *n = sln_new(input, (dup_func *)dup_str);

	REQUIRE(n != NULL, "sln_new() should return non-null pointer");
	char *const output = sln_get_data(n);

	CHECK(output != input, "data should point to a duplicated object");
	CHECK_STREQ(output, input, "duplicated data should be equal to input");
	CHECK(sln_get_next(n) == NULL, "pointer to next node should be NULL");
	free(output);
	free(n);
}

TEST(node_creation, new_d_faildup_returns_NULL)
{
	char input[] = "input";
	single_link_node *n = sln_new(input, fail_dup);

	REQUIRE(n == NULL, "sln_new() should return NULL if data duplication fails");
}

/*######################################*/

TEST(data_get, get_data_handles_NULL)
{
	CHECK(sln_get_data(NULL) == NULL, "should not process NULL");
}

TEST(data_get, get_data_returns_correct_data)
{
	char input[] = "input";
	single_link_node *n1 = sln_new(input, NULL);

	REQUIRE(n1 != NULL, "sln_new() should return non-null pointer");
	CHECK(sln_get_data(n1) == input, "data should point to the same object");
	free(n1);
}

TEST(data_get, get_data_returns_correct_duplicated_data)
{
	char input[] = "input";
	single_link_node *n1 = sln_new(input, (dup_func *)dup_str);

	REQUIRE(n1 != NULL, "sln_new() should return non-null pointer");
	char *const curr_data = sln_get_data(n1);

	CHECK(curr_data != input, "data should point to a duplicated object");
	CHECK_STREQ(curr_data, input, "duplicated object should be equal to input");
	free(curr_data);
	free(n1);
}

/*######################################*/

struct data_swap
{
	single_link_node *n1;
};

TEST_F_SETUP(data_swap)
{
	tau->n1 = sln_new((char *const)original, NULL);
	REQUIRE(tau->n1 != NULL, "sln_new() should return non-null pointer");
}

TEST_F_TEARDOWN(data_swap) { free(tau->n1); }

TEST(data_swap, swap_NULL_NULL_NULL)
{
	CHECK(sln_swap_data(NULL, NULL, NULL) == NULL,
		  "should not swap NULL pointer");
	CHECK(sln_swap_data(NULL, "NULL", NULL) == NULL,
		  "should not swap NULL pointer");
	CHECK(sln_swap_data(NULL, NULL, fail_dup) == NULL,
		  "should not swap NULL pointer");
	CHECK(sln_swap_data(NULL, "NULL", fail_dup) == NULL,
		  "should not swap NULL pointer");
}

TEST_F(data_swap, swap_n_d_NULL)
{
	char input[] = "input";

	CHECK(sln_swap_data(tau->n1, input, NULL) == original,
		  "should return old data");
	CHECK(sln_get_data(tau->n1) == input, "data is equal to the input");
}

TEST_F(data_swap, swap_n_NULL_NULL_nullifies_data)
{
	CHECK(sln_swap_data(tau->n1, NULL, NULL) == original,
		  "should return old data");
	CHECK(sln_get_data(tau->n1) == NULL, "data should be NULL");
}

TEST_F(data_swap, swap_n_d_faildup_returns_NULL)
{
	CHECK(sln_swap_data(tau->n1, "input", fail_dup) == NULL,
		  "should return NULL on failure to duplicate");
	CHECK(sln_get_data(tau->n1) == original, "data should be unchanged");
}

TEST_F(data_swap, swap_n_d_f)
{
	char *const input = "input";

	CHECK(sln_swap_data(tau->n1, input, (dup_func *)dup_str) == original,
		  "should return old data");
	char *const curr_data = sln_get_data(tau->n1);

	CHECK(curr_data != input, "data should be duplicated");
	CHECK_STREQ(curr_data, input, "data should be equal to input");
	free(curr_data);
}

/*######################################*/

struct node_insertion
{
	single_link_node *n1, *n2, *n3;
};

TEST_F_SETUP(node_insertion)
{
	tau->n1 = sln_new((char *const)n1d, NULL);
	REQUIRE(tau->n1 != NULL, "sln_new() should return non-null pointer");
	tau->n2 = sln_new((char *const)n2d, NULL);
	REQUIRE(tau->n2 != NULL, "sln_new() should return non-null pointer");
	tau->n3 = sln_new((char *const)n3d, NULL);
	REQUIRE(tau->n3 != NULL, "sln_new() should return non-null pointer");
}

TEST_F_TEARDOWN(node_insertion)
{
	free(tau->n1);
	free(tau->n2);
	free(tau->n3);
}

TEST(node_insertion, insert_NULLs)
{
	CHECK(sln_insert_after(NULL, NULL) == NULL, "nothing is done");
	CHECK(sln_insert_before(NULL, NULL) == NULL, "nothing is done");
}

TEST_F(node_insertion, insert_after_NULL)
{
	REQUIRE(sln_insert_after(NULL, tau->n2) == tau->n2,
			"the newly inserted node should be n2");
	CHECK(sln_get_next(tau->n2) == NULL, "n2 next should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "data should be unchanged");
}

TEST_F(node_insertion, insert_NULL_after)
{
	REQUIRE(sln_insert_after(tau->n1, NULL) == tau->n1,
			"the newly inserted node should be n1");
	CHECK(sln_get_next(tau->n1) == NULL, "n1 next should be unchanged");
	CHECK(sln_get_data(tau->n1) == n1d, "data should be unchanged");
}

TEST_F(node_insertion, insert_after_1_node)
{
	REQUIRE(sln_insert_after(tau->n1, tau->n2) == tau->n2,
			"the newly inserted node should be n2");
	CHECK(sln_get_next(tau->n2) == NULL, "n2 next should be unchanged");
	CHECK(sln_get_next(tau->n1) == tau->n2, "n1 next should be n2");
	CHECK(sln_get_data(tau->n1) == n1d, "n1 data should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "n2 data should be unchanged");
}

TEST_F(node_insertion, insert_after_2_nodes)
{
	single_link_node *output = sln_insert_after(tau->n1, tau->n2);

	REQUIRE(output == tau->n2, "the newly inserted node should be n2");
	output = sln_insert_after(tau->n2, tau->n3);
	REQUIRE(output == tau->n3, "the newly inserted node should be n3");
	CHECK(sln_get_next(tau->n3) == NULL, "n3 next should be unchanged");
	CHECK(sln_get_next(tau->n2) == tau->n3, "n2 next should be n3");
	CHECK(sln_get_next(tau->n1) == tau->n2, "n1 next should be n2");
	CHECK(sln_get_data(tau->n1) == n1d, "n1 data should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "n2 data should be unchanged");
	CHECK(sln_get_data(tau->n3) == n3d, "n3 data should be unchanged");
}

TEST_F(node_insertion, insert_after_between_2_nodes)
{
	single_link_node *output = sln_insert_after(tau->n1, tau->n3);

	REQUIRE(output == tau->n3, "the newly inserted node should be n3");
	output = sln_insert_after(tau->n1, tau->n2);
	REQUIRE(output == tau->n2, "the newly inserted node should be n2");
	CHECK(sln_get_next(tau->n3) == NULL, "n3 next should be unchanged");
	CHECK(sln_get_next(tau->n2) == tau->n3, "n2 next should be n3");
	CHECK(sln_get_next(tau->n1) == tau->n2, "n1 next should be n2");
	CHECK(sln_get_data(tau->n1) == n1d, "n1 data should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "n2 data should be unchanged");
	CHECK(sln_get_data(tau->n3) == n3d, "n3 data should be unchanged");
}

TEST_F(node_insertion, insert_before_NULL)
{
	REQUIRE(sln_insert_before(NULL, tau->n2) == tau->n2,
			"the newly inserted node should be n2");
	CHECK(sln_get_next(tau->n2) == NULL, "n2 next should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "data should be unchanged");
}

TEST_F(node_insertion, insert_NULL_before)
{
	REQUIRE(sln_insert_before(tau->n1, NULL) == tau->n1,
			"the newly inserted node should be n1");
	CHECK(sln_get_next(tau->n1) == NULL, "n1 next should be unchanged");
	CHECK(sln_get_data(tau->n1) == n1d, "data should be unchanged");
}

TEST_F(node_insertion, insert_before_1_node)
{
	REQUIRE(sln_insert_before(tau->n1, tau->n2) == tau->n2,
			"the newly inserted node should be n2");
	CHECK(sln_get_next(tau->n1) == NULL, "n1 next should be unchanged");
	CHECK(sln_get_next(tau->n2) == tau->n1, "n2 next should be n1");
	CHECK(sln_get_data(tau->n1) == n1d, "n1 data should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "n2 data should be unchanged");
}

TEST_F(node_insertion, insert_before_2_nodes)
{
	single_link_node *output = sln_insert_before(tau->n1, tau->n2);

	REQUIRE(output == tau->n2, "the newly inserted node should be n2");
	output = sln_insert_before(tau->n2, tau->n3);
	REQUIRE(output == tau->n3, "the newly inserted node should be n3");
	CHECK(sln_get_next(tau->n1) == NULL, "n1 next should be unchanged");
	CHECK(sln_get_next(tau->n2) == tau->n1, "n2 next should be n1");
	CHECK(sln_get_next(tau->n3) == tau->n2, "n3 next should be n2");
	CHECK(sln_get_data(tau->n1) == n1d, "n1 data should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "n2 data should be unchanged");
	CHECK(sln_get_data(tau->n3) == n3d, "n3 data should be unchanged");
}

TEST_F(node_insertion, insert_before_between_2_nodes)
{
	single_link_node *output = sln_insert_before(tau->n1, tau->n3);

	REQUIRE(output == tau->n3, "the newly inserted node should be n3");
	output = sln_insert_before(tau->n1, tau->n2);
	REQUIRE(output == tau->n2, "the newly inserted node should be n2");
	CHECK(sln_get_next(tau->n1) == NULL, "n1 next should be unchanged");
	CHECK(sln_get_next(tau->n2) == tau->n1, "n2 next should be n1");
	CHECK(sln_get_next(tau->n3) == tau->n2, "n3 next should be n2");
	CHECK(sln_get_data(tau->n1) == n1d, "n1 data should be unchanged");
	CHECK(sln_get_data(tau->n2) == n2d, "n2 data should be unchanged");
	CHECK(sln_get_data(tau->n3) == n3d, "n3 data should be unchanged");
}

/*####################################**/

struct node_deletion
{
	single_link_node *n1, *n2, *n3;
};

TEST_F_SETUP(node_deletion)
{
	tau->n1 = sln_new((char *const)n1d, NULL);
	REQUIRE(tau->n1 != NULL, "sln_new() should return non-null pointer");
	tau->n2 = sln_new((char *const)n2d, NULL);
	REQUIRE(tau->n2 != NULL, "sln_new() should return non-null pointer");
	tau->n3 = sln_new((char *const)n3d, NULL);
	REQUIRE(tau->n3 != NULL, "sln_new() should return non-null pointer");

	/*n1->n2->n3*/
	sln_insert_after(sln_insert_after(tau->n1, tau->n2), tau->n3);
}

TEST_F_TEARDOWN(node_deletion)
{
	free(tau->n1);
	free(tau->n2);
	free(tau->n3);
}

TEST(node_deletion, remove_NULL)
{
	CHECK(sln_remove(NULL) == NULL, "nothing should be done");
}

TEST(node_deletion, remove_n)
{
	single_link_node *n1 = sln_new((char *const)original, NULL);

	CHECK(sln_remove(n1) == original,
		  "node should be freed and its data returned");
}

TEST_F(node_deletion, remove_first_node_in_list)
{
	CHECK(sln_remove(tau->n1) == n1d, "data returned should be n1's");
	tau->n1 = NULL;
	CHECK(sln_get_next(tau->n2) == tau->n3, "n2 next should be n3");
	CHECK(sln_get_next(tau->n3) == NULL, "n3 next should be unchanged");
}

TEST_F(node_deletion, remove_middle_node_in_list)
{
	CHECK(sln_remove(tau->n2) == n2d, "data returned should be n2's");
	tau->n2 = NULL;
	CHECK(sln_get_next(tau->n1) == tau->n3, "n1 next should be n3");
	CHECK(sln_get_next(tau->n3) == NULL, "n3 next should be unchanged");
}

TEST_F(node_deletion, remove_last_node_in_list)
{
	CHECK(sln_remove(tau->n3) == n3d, "data returned should be n3's");
	tau->n3 = NULL;
	CHECK(sln_get_next(tau->n1) == tau->n2, "n1 next should be n2");
	CHECK(sln_get_next(tau->n2) == NULL, "n2 next should be NULL");
}

TEST_F(node_deletion, remove_first_node_of_2_in_list)
{
	sln_remove(tau->n3);
	tau->n3 = NULL;

	CHECK(sln_remove(tau->n1) == n1d, "data returned should be n1's");
	tau->n1 = NULL;
	CHECK(sln_get_next(tau->n2) == NULL, "n2 next should be unchanged");
}

TEST_F(node_deletion, remove_second_node_of_2_in_list)
{
	sln_remove(tau->n3);
	tau->n3 = NULL;

	CHECK(sln_remove(tau->n2) == n2d, "data returned should be n2's");
	tau->n2 = NULL;
	CHECK(sln_get_next(tau->n1) == NULL, "n1 next should be NULL");
}

TEST(node_deletion, clear_NULL)
{
	/*Should produce no leaks or UB.*/
	sll_clear(NULL, NULL);
}

TEST_F(node_deletion, clear_sll)
{
	/*Should produce no leaks or UB.*/
	sll_clear(tau->n1, NULL);
	tau->n1 = NULL;
	tau->n2 = NULL;
	tau->n3 = NULL;
}
