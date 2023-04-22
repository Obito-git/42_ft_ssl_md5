#include "ft_ssl.h"

/* {(name), (pointer to start function)}
 * start function must be prototyped like "const char *algorithm_name(char *data)"
 * the last array element must be:
 * {NULL, NULL} */

t_hash_algorithm algorithms[] = {
		{"sha256", sha256_start},
		{NULL, NULL}
};