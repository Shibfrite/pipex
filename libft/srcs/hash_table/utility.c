#include "hash_table.h"

int compare_strings(const void *a, const void *b)
{
	return (strncmp((const char *)a, (const char *)b, MAX_NAME));
}
