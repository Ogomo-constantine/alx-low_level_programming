#include "hash_tables.h"
#include <stdio.h>

/**
 * hash_table_create - Create a hash table with a given size.
 * @size: The size of the array that stores the hash table's elements.
 *
 * Return: On success, a pointer to the new hash table. On failure, NULL.
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *ht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

	ht = malloc(sizeof(hash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->array = malloc(sizeof(hash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	return (ht);
}
