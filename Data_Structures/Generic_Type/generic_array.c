#include "generic_types.h"

/*TODO: How to retrieve data from Generic_Array?*/

/*!
 * @brief generic array type.
 */
struct Generic_Array
{
	enum genarr_id type;	  //!< the type of data in the array.
	size_t len;				  //!< number of items in the array.
	union pointer_types data; //!< union of possible types of data pointers.
};

/*!
 * @brief returns a pointer to the Generic_Array of the given type, initialised with data.
 * @param type the type of the Generic_Array.
 * @param data content to initialise the Generic_pointer with.
 * @param len number of items in data.
 * @return pointer to the new Generic_Array, NULL on failure.
 */
Generic_Array *genarr_new(enum genarr_id type, const void *data, const size_t len)
{
	Generic_Array *new_GT = NULL;

	switch (type)
	{
	case STRING:
	{
		const char *s = data; /*!!*/
		const size_t s_len = data ? len : 0;

		new_GT = malloc(sizeof(*new_GT) + (sizeof(*s) * (s_len + 1 /*!!*/)));
		if (!new_GT)
			break; /*TODO: test this.*/

		*new_GT = (Generic_Array){
			.type = STRING, /*!!*/
			.len = s_len,
			.data.str = data ? (char *)new_GT /*!!*/ + sizeof(*new_GT) : NULL,
		};
		memcpy(new_GT->data.str /*!!*/, s, sizeof(*s) * s_len);
		new_GT->data.str[s_len] = 0; /*!!*/
		break;
	}
	case INT_ARR:
	{
		const int *iarr = data; /*!!*/
		const size_t i_len = data ? len : 0;

		new_GT = malloc(sizeof(*new_GT) + (sizeof(*iarr) * i_len));
		if (!new_GT)
			break; /*TODO: test this.*/

		*new_GT = (Generic_Array){
			.type = INT_ARR, /*!!*/
			.len = i_len,
			.data.iarr = data ? (int *)new_GT /*!!*/ + sizeof(*new_GT) : NULL,
		};
		memcpy(new_GT->data.iarr /*!!*/, iarr, sizeof(*iarr) * i_len);
		break;
	}
	case SIZET_ARR:
	{
		const size_t *szarr = data; /*!!*/
		const size_t sz_len = data ? len : 0;

		new_GT = malloc(sizeof(*new_GT) + (sizeof(*szarr) * sz_len));
		if (!new_GT)
			break; /*TODO: test this.*/

		*new_GT = (Generic_Array){
			.type = SIZET_ARR, /*!!*/
			.len = sz_len,
			.data.szarr = data ? (size_t *)new_GT /*!!*/ + sizeof(*new_GT) : NULL,
		};
		memcpy(new_GT->data.szarr /*!!*/, szarr, sizeof(*szarr) * sz_len);
		break;
	}
	case DOUBLE_ARR:
	{
		const double *dbarr = data; /*!!*/
		const size_t db_len = data ? len : 0;

		new_GT = malloc(sizeof(*new_GT) + (sizeof(*dbarr) * db_len));
		if (!new_GT)
			break; /*TODO: test this.*/

		*new_GT = (Generic_Array){
			.type = DOUBLE_ARR, /*!!*/
			.len = db_len,
			.data.dbarr = data ? (double *)new_GT /*!!*/ + sizeof(*new_GT) : NULL,
		};
		memcpy(new_GT->data.dbarr /*!!*/, dbarr, sizeof(*dbarr) * db_len);
		break;
	}
	default:
		new_GT = NULL;
		break;
	}

	return (new_GT);
}

/*!
 * @brief free a Generic_Array from memory.
 * @param ga pointer to the Generic_Array.
 * @return NULL always.
 */
void *genarr_delete(Generic_Array *const ga)
{
	if (!ga)
		return (NULL);

	ga->len = 0;
	free(ga);
	return (NULL);
}

/*!
 * @brief return the enumerated type of the Generic Array.
 * @param ga pointer to the array.
 * @return the enumerated type of the Generic Array, -1 if NULL.
 */
enum genarr_id genarr_type(const Generic_Array *ga)
{
	if (!ga)
		return (-1);

	return (ga->type);
}

/*!
 * @brief return number of items in the array.
 * @param ga pointer to the array.
 * @return number of items in the array, -1 if NULL.
 */
size_t genarr_len(const Generic_Array *ga)
{
	if (!ga)
		return (-1);

	return (ga->len);
}
