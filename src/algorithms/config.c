#include "ft_ssl.h"

/* {(name), (pointer to start function)}
 * start function must be prototyped like "const char *algorithm_name(char *data)"
 * the last array element must be:
 * {NULL, NULL} */

t_hash_algorithm algorithms[] = {
		{"sha256", sha256_start},
		{NULL, NULL}
};

t_algorithm_ptr getAlgorithmByName(const char *name) {
	for (size_t i = 0; algorithms[i].name; i++) {
		if (!algorithms[i].algorithmPtr)
			exit_error(ERR_CONFIG_FUNC(algorithms[i].name));
		if (ft_strcmp(name, algorithms[i].name) == 0)
			return algorithms[i].algorithmPtr;
	}
	return NULL;
}