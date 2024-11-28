#ifndef FAM_H
#define FAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> /*offsetof*/

#define report(x) printf(#x ": %zu\n", x)

#if __has_attribute(counted_by)
#define ATTR_COUNTED_BY(member) __attribute__((counted_by(member)))
#else
#define ATTR_COUNTED_BY(member)
#endif

/**
 * struct String - string
 * @len: length
 * @str: char pointer
 */
struct String
{
	size_t len;
	char str[] ATTR_COUNTED_BY(len);
};

/*According to ISO C11: Structs with Flexible Array Members cannot be */
/*contained in arrays or other structs.*/

#endif /*FAM_H*/
