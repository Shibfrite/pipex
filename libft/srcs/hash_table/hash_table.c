#include "hash_table.h"

void hash_table_init(hash_table *ht) {
    ht->size = TABLE_SIZE; // Default size
    ht->hash = hash_multiplication; // Default hash function
    ht->compare = compare_strings; // Default compare function
    ht->resolve_collision = chaining_resolution; // Default collision resolution
    ht->lookup_method = chaining_lookup; // Default lookup method
    ht->table = calloc(ht->size, sizeof(void *));
}

void	hash_table_print(hash_table *ht)
{
	size_t i;

	if (!ht)
		return ;
	printf("Start\n");
	i = 0;
	while (i < TABLE_SIZE)
	{
		printf("\t%zu\t", i);
		node *current = ht->table[i++];
		while (current)
		{
			printf("%s -> ", (char *)current->data);
			current = current->next;
		}
		printf("NULL\n");
	}
	printf("End\n");
}

int hash_table_insert(hash_table *ht, void *data, size_t data_size)
{
	void *new_data;
	int result;

	if (!ht || !data)
		return (-1);
	new_data = malloc(data_size);
	if (!new_data)
		return (-1);
	memcpy(new_data, data, data_size);
	result = ht->resolve_collision(ht, ht->hash(new_data), new_data);
	if (result == -1)
		free(new_data);
	return (result);
}

void *hash_table_lookup(hash_table *ht, const void *key)
{
	size_t	index;

	if (!ht || !key)
		return NULL;
	index = ht->hash(key);
	return (ht->lookup_method(ht, index, key));
}

void *hash_table_delete(hash_table *ht, const void *key)
{
	size_t	index;
	node	*current;
	node	*prev;
	void	*data;

	if (!ht || !key)
		return (NULL);
	index = ht->hash(key);
	current = ht->table[index];
	prev = NULL;
	while (current)
	{
		if (!ht->compare(current->data, key))
		{
			data = current->data;
			if (prev)
				prev->next = current->next;
			else
				ht->table[index] = current->next;
			free(current);
			return (data);
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}
