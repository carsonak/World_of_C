#ifndef FAM_H
#define FAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*The following structure will not work as expected as FAMs cannot be nested*/

/**
 * struct Catalogue_nested - array of names
 * @size: length of the catalogue
 * @list: array of strings
 */
struct Catalogue_nested
{
	size_t size;
	struct String list[] ATTR_COUNTED_BY(size);
};

#endif /*FAM_H*/
