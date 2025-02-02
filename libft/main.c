#include "hash_table.h"

int main()
{
	hash_table ht;
	hash_table_init(&ht, TABLE_SIZE, hash_multiplication, compare_strings, chaining_resolution, chaining_lookup);
		hash_table_print(&ht);

	char *names[] = {"Jacob", "Kate", "Mpho", "Sarah", "Edna", "Maren", "Eliza", "Robert", "Jane"};
	for (int i = 0; i < 9; i++)
	{
		hash_table_insert(&ht, names[i], strlen(names[i]) + 1);
	}
	hash_table_print(&ht);

	char *tmp = hash_table_lookup(&ht, "Mpho");
	if (!tmp)
		printf("Not found.\n");
	else
		printf("Found %s.\n", tmp);

	tmp = hash_table_lookup(&ht, "George");
	if (!tmp)
		printf("Not found.\n");
	else
		printf("Found %s.\n", tmp);

	hash_table_delete(&ht, "Mpho");
	hash_table_print(&ht);

	return (0);
}
