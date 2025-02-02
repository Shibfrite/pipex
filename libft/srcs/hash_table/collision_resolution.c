#include "hash_table.h"

int chaining_resolution(hash_table *ht, size_t index, void *data)
{
	node *new_node;
	
	if (chaining_lookup(ht, index, data))
		return (-1);
	new_node = malloc(sizeof(node));
	if (!new_node)
		return (-1);  // Memory allocation failed
	new_node->data = data;  // Use the pre-allocated data
	new_node->next = ht->table[index];
	ht->table[index] = new_node;
	return (1);
}

void* chaining_lookup(hash_table *ht, size_t index, const void *key)
{
	node *current = ht->table[index];
	while (current)
	{
		if (!ht->compare(current->data, key))
			return (current->data);
		current = current->next;
	}
	return (NULL);
}
