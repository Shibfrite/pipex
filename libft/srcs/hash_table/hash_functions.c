#include "hash_table.h"

size_t  hash_multiplication(const void *key)
{
	const char		*str_key;
	size_t			len;
	size_t			i;
	unsigned int	hash_value;

	str_key = (const char *)key;
	len = strnlen(str_key, MAX_NAME);
	hash_value = 0;
	i = 0;
	while (i < len)
	{
		hash_value += str_key[i];
		hash_value *= str_key[i++];
		hash_value %= TABLE_SIZE;
	}
	return (hash_value);
}
