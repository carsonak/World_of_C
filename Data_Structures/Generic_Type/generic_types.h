#ifndef GENERIC_TYPE_H
#define GENERIC_TYPE_H

#include <stdlib.h>
#include <string.h>

typedef struct Generic_Type Generic_Type;

/*!
 * @brief enumeration of Generic_Type types.
 */
enum gentyp_id
{
	CHAR,
	INT,
	SIZET,
	DOUBLE,
};

typedef struct Generic_Array Generic_Array;

/*!
 * @brief numeration of Generic_Array types.
 */
enum genarr_id
{
	STRING,
	INT_ARR,
	SIZET_ARR,
	DOUBLE_ARR,
};

/*!
 * @brief union of different pointers.
 */
union pointer_types
{
	char *str;
	int *iarr;
	size_t *szarr;
	double *dbarr;
};

#endif /*GENERIC_TYPE_H*/
