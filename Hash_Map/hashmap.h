#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>

#if __has_attribute(nonnull)
#define ATTR_NONNULL __attribute__((nonnull))
#else
#define ATTR_NONNULL
#endif

typedef const unsigned char *str_literal;

/**
 * struct Bucket - bucket of a hash table
 * @key:
 */
typedef struct Bucket
{
    size_t hash;
    char *key;
    char *value;
    struct Bucket *next;
} Bucket;

/**
 * struct HashMap - a hash table
 * @size: number of slots in the hash table
 * @array: the hash table
 */
typedef struct HashMap
{
    size_t size;
    Bucket **array;
} HashMap;

#endif /*HASHMAP_H*/
