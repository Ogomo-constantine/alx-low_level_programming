#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * key_index - gives the index of a key.
 * @key: the key to hash.
 * @size: size of the hash table array.
 * Return: index at which the key/value pair should be stored in the array
 *         of the hash table.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int hash;

	hash = hash_djb2(key);
	return (hash % size);
}
