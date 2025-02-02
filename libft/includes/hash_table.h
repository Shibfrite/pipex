#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

// Forward declaration of hash_table
struct hash_table;

// the modular functions used to change the algorithme without altering output
typedef size_t (*hash_function)(const void *key);
typedef int (*compare_function)(const void *a, const void *b);
typedef int (*collision_resolution_function)(struct hash_table *ht, size_t index, void *data);
typedef void* (*lookup_method_function)(struct hash_table *ht, size_t index, const void *key);

// hash table with the modular functions contained within for better accessibility

typedef struct hash_table {
	void **table;
	size_t size;
	hash_function hash;
	compare_function compare;
	collision_resolution_function resolve_collision;
	lookup_method_function lookup_method;
} hash_table;

// node used if collision_resolution needs linked list.
typedef struct node {
	void *data;
	struct node *next;
} node;

// Function prototypes
void hash_table_init(hash_table *ht);
void hash_table_print(hash_table *ht);
int hash_table_insert(hash_table *ht, void *data, size_t data_size);
void *hash_table_lookup(hash_table *ht, const void *key);
void *hash_table_delete(hash_table *ht, const void *key);

// Utility functions
size_t hash_multiplication(const void *key);
int compare_strings(const void *a, const void *b);

// Collision resolution methods with lookup method 
int chaining_resolution(hash_table *ht, size_t index, void *data);
void* chaining_lookup(hash_table *ht, size_t index, const void *key);

#endif

