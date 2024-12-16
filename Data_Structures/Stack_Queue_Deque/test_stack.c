#include "stack.h"
#include "tau/tau.h"
#include <string.h> /* memcpy */
#include <stdlib.h> /* free */

#define MAX_STRING_LENGTH ((unsigned int)256)

static char n1d[] = "one"; /*, n2d[] = "two", n3d[] = "three";*/

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
 * @str: pointer to the string.
 *
 * Return: pointer to the new string, NULL on failure.
 */
static void *dup_str(void const *const str)
{
	char const *const s = str;

	if (!s)
		return (NULL);

	unsigned int len = 0;

	while (s[len] && len <= MAX_STRING_LENGTH)
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

TEST(stack_creation, new_returns_empty_stack)
{
	stack *s = stk_new();

	REQUIRE(s, "new returns non-null");
	CHECK(stk_len(s) == 0, "there should be 0 items in the stack");
	CHECK(stk_peek(s) == NULL, "there should be no item at the top of the stack");

	free(s);
}

struct adding_items
{
	stack *s;
	single_link_node *n1, *n2;
};

TEST_F_SETUP(adding_items)
{
	tau->s = stk_new();
	REQUIRE(tau->s, "failed to create stack");
}

TEST_F_TEARDOWN(adding_items)
{
	free(tau->s);
	free(tau->n1);
	free(tau->n2);
}

TEST(adding_items, push_invalid_args)
{
	CHECK(stk_push(NULL, NULL, NULL) == NULL, "pointer to stack is required");
	CHECK(stk_push(NULL, n1d, NULL) == NULL, "pointer to stack is required");
	CHECK(stk_push(NULL, NULL, dup_str) == NULL, "pointer to stack is required");
	CHECK(stk_push(NULL, n1d, dup_str) == NULL, "pointer to stack is required");
}

TEST_F(adding_items, push_one_faildup)
{
	REQUIRE(stk_push(tau->s, n1d, fail_dup) == NULL, "push returns NULL on failure");
	CHECK(stk_len(tau->s) == 0, "number of items in the stack should be unchanged");
	CHECK(stk_peek(tau->s) == NULL, "top of the stack should be unchanged");
}

TEST_F(adding_items, push_one)
{
	tau->n1 = stk_push(tau->s, n1d, NULL);
	REQUIRE(tau->n1, "push returns pointer to the added node");

	CHECK(stk_len(tau->s) == 1, "there should be only one item in the stack");
	CHECK(stk_peek(tau->s) == n1d, "top should point to the new node");
}

TEST_F(adding_items, push_one_dupfunc)
{
	tau->n1 = stk_push(tau->s, n1d, dup_str);
	REQUIRE(tau->n1, "push returns pointer to the added node");

	CHECK(stk_len(tau->s) == 1, "there should be only one item in the stack");
	char *d = stk_peek(tau->s);
	CHECK_STREQ(d, n1d, "top should point to the new node");
	free(d);
}
