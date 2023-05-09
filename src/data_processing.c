#include "ft_ssl.h"

void process_data(data_t *data, char *algoname, int flags)
{
	t_hash_algorithm *pAlgorithm = getAlgorithmByName(algoname);
	char *hash = pAlgorithm->algorithmPtr(data->data, data->len);
	if (!hash) {
		ft_fprintf(STDERR_FILENO, "%s\n", ERROR_MALLOC);
		return;
	}
	if (flags & ARG_REVERSE)
		ft_printf("-r detected\n\n");
	if (flags & ARG_QUITE)
		ft_printf("-q detected\n\n");
	ft_printf("%s\n", hash);
	free(hash);
}