#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * shash_node_t - Node of a sorted hash table
 * @key: The key, string
 * @value: The value associated with the key
 * @next: A pointer to the next node in the list
 * @prev: A pointer to the previous node in the list
 */
typedef struct shash_node_s 
{
	char *key;
	char *value;
	struct shash_node_s *next;
	struct shash_node_s *prev;
} shash_node_t;

/**
 * shash_table_s - Sorted hash table data structure
 * @size: The size of the array
 * @array: An array of pointers to nodes
 * @shead: A pointer to the first node in the sorted list
 * @stail: A pointer to the last node in the sorted list
 */
typedef struct shash_table_s 
{
	unsigned long int size;
	shash_node_t **array;
	shash_node_t *shead;
	shash_node_t *stail;
} shash_table_t;

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the array
 *
 * Return: A pointer to the new hash table, or NULL if an error occurs
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->array = malloc(size * sizeof(shash_node_t *));
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;
	
	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - Adds an element to a sorted hash table
 * @ht: The hash table to modify
 * @key: The key to insert
 * @value: The value associated with the key
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *node, *temp;
	unsigned long int index;

	if (ht == NULL || key == NULL || value == NULL)
		return (0);

	index = key_index((unsigned char *)key, ht->size);
	temp = ht->array[index];

	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = strdup(value);
			if (temp->value == NULL)
				return (0);
			return (1);
		}
		temp = temp->next;
	}

	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (0);
	
	node->key = strdup(key);
	node->value = strdup(value);
	if (node->key == NULL || node->value == NULL)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (0);
	}

	node->next = ht->array[index];
	ht->array[index] = node;

	if (ht->shead == NULL)
	{
		node->sprev = NULL;
		node->snext = NULL;
		ht->shead = node;
		ht->stail = node;
	}
	else if (strcmp(node->key, ht->shead->key) < 0)
	{
		node->sprev = NULL;
		node->snext = ht->shead;
		ht->shead->sprev = node;
		ht->shead = node;
	}
	else
	{
		temp = ht->shead;
		while (temp->snext != NULL && strcmp(node->key, temp->snext->key) > 0)
			temp = temp->snext;

		node->sprev = temp;
		node->snext = temp->snext;

		if (temp->snext == NULL)
			ht->stail = node;
		else
			temp->snext->sprev = node;

		temp->snext = node;
	}
	return (1);
}

/**
 * shash_table_get - retrieves the value associated with a key
 * @ht: hash table
 * @key: key to retrieve value for
 *
 * Return: value associated with the element, or NULL if key not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int idx;
	shash_node_t *node;

	if (!ht || !key || *key == '\0')
		return (NULL);

	idx = key_index((const unsigned char *)key, ht->size);
	node = ht->shead;
	while (node)
	{
		if (node->key && strcmp(node->key, key) == 0)
			return (node->value);
		node = node->snext;
	}

	return (NULL);
}

/**
 * shash_table_print - prints the hash table using the sorted linked list
 * @ht: hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;

	if (!ht)
		return;

	node = ht->shead;
	printf("{");
	while (node)
	{
		printf("'%s': '%s'", node->key, node->value);
		if (node->snext)
			printf(", ");
		node = node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints the hash tables key/value pairs in reverse
 * order using the sorted linked list
 * @ht: hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;

	if (!ht)
		return;

	node = ht->stail;
	printf("{");
	while (node)
	{
		printf("'%s': '%s'", node->key, node->value);
		if (node->sprev)
			printf(", ");
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - deletes a hash table
 * @ht: hash table to delete
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node, *tmp;

	if (!ht)
		return;

	node = ht->shead;
	while (node)
	{
		tmp = node;
		node = node->snext;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(ht->array);
	free(ht);
}
