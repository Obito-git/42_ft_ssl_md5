#include "ft_ssl.h"

void process_data_debug(const char *debug_msg, char *s, char *algoname, int flags)
{
	(void) flags;
	t_hash_algorithm *pAlgorithm = getAlgorithmByName(algoname);
	if (!pAlgorithm)
		exit_error("ALGO NULL");
	printf("PROCESSED: [src: %s], [data: %s] [res %s]\n", debug_msg, s, pAlgorithm->algorithmPtr(algoname));
}