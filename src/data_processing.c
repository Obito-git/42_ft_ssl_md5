#include "ft_ssl.h"

static void process_quite(data_t *data, int *flags, char *hash) {
	if (*flags & ARG_STDIN) {
		ft_printf("%s\n", data->data);
		*flags ^= ARG_STDIN;
	}
	ft_printf("%s\n", hash);	
}
static void process_pure_stdin(int *flags, char *hash) {
	ft_printf("(stdin)= %s\n", hash);
	*flags ^= ARG_PURE_STDIN;
}
static void process_stdin(data_t *data, int *flags, char *hash) {
	ft_printf("(\"%s\")= %s\n", data->data, hash);
	*flags ^= ARG_STDIN;
}
static void process_string(data_t *data, char *algoname, int *flags, char *hash) {
	if (*flags & ARG_REVERSE)
		ft_printf("%s \"%s\"\n", hash, data->data);
	else
		ft_printf("%s (\"%s\") = %s\n", algoname, data->data, hash);
	*flags ^= ARG_STRING;
}

void process_data(data_t *data, char *algoname, int *flags)
{
	t_hash_algorithm *pAlgorithm = getAlgorithmByName(algoname);
	char *hash = pAlgorithm->algorithmPtr(data->data, data->len);
	if (!hash) {
		ft_fprintf(STDERR_FILENO, "%s\n", ERROR_MALLOC);
		return;
	}
	size_t i = data->len - 1;
	for (; i && data->data[i] == '\n'; i--)
		data->data[i] = '\0';
	if (i == 0 && data->data[i] == '\n')
		data->data[i] = '\0';
	
	if (*flags & ARG_QUITE) {
		process_quite(data, flags, hash);
	} else if (*flags & ARG_PURE_STDIN) {
		process_pure_stdin(flags, hash);
	} else if (*flags & ARG_STDIN) {
		process_stdin(data, flags, hash);
	} else if (*flags & ARG_STRING) {
		process_string(data, algoname, flags, hash);
	} else if (*flags & ARG_REVERSE) {
		ft_printf("%s %s\n", hash, data->file_name);
	} else {
		ft_printf("%s (%s) = %s\n", algoname, data->file_name, hash);
	}
	free(hash);
}