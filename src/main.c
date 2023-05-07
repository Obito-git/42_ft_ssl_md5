#include "ft_ssl.h"

static void check_algorithm_name(const char *provided_name) {
	if (!algorithms[0].name) {
		exit_error(ERR_CONFIG_EMPTY);
	}
	if (getAlgorithmByName(provided_name))
		return;
	PRINT_ERR_NOT_FOUND(provided_name);
	for (size_t i = 0; algorithms[i].name; i++) {
		ft_fprintf(STDERR_FILENO, "\t- %s\n", algorithms[i].name);
	}
	exit(1);
}

static int process_args(int ac, char **av, int *flags) {
	int file_index;

	check_algorithm_name(av[1]);

	for (file_index = 2; file_index < ac; file_index++) {
		size_t arg_len = ft_strlen(av[file_index]);
		if (av[file_index][0] == '-' && arg_len > 1) {
			if (av[file_index][1] == 'p') {
				*flags |= ARG_STDIN;
			} else if (av[file_index][1] == 'q') {
				*flags |= ARG_QUITE;
			} else if (av[file_index][1] == 'r') {
				*flags |= ARG_REVERSE;
			} else if (av[file_index][1] == 's') {
				*flags |= ARG_STRING;
			} else if (av[file_index][1] == 'd') {
				*flags |= ARG_DEBUG;
			} else {
				PRINT_ERR_UNKNOWN_ARG(&av[file_index][1]);
				exit(1);
			}
		} else if (av[file_index][0] == '-' && arg_len == 1) {
			exit_error(ERR_USAGE);
		} else {
			break;
		}
	}
	return file_index;
}

int main(int ac, char **av) {
	int flags = 0;
	int file_index;

	if (ac < 2)
		exit_error(ERR_USAGE);
	file_index = process_args(ac, av, &flags);
	char *algo_name = av[1]; //FIXME ME DOESN'T PRETTY


	//FIXME DEBUG START
	if (flags == 0)
		ft_printf("No flags detected\n\n");
	if (flags & ARG_STDIN)
		ft_printf("-p detected\n\n");
	if (flags & ARG_STRING)
		ft_printf("-s detected\n\n");
	if (flags & ARG_REVERSE)
		ft_printf("-r detected\n\n");
	if (flags & ARG_QUITE)
		ft_printf("-q detected\n\n");
	//FIXME DEBUG END


	if (file_index == ac || flags & ARG_STDIN) {
		char *data = read_stdin();
		process_data_debug("from stdin", data, algo_name, flags);
		free(data);
	}
	if (flags & ARG_STRING) {
		process_data_debug("from arg", av[file_index++], algo_name, flags);
	}
	for (; file_index < ac; file_index++) {
		char *data = read_file(av[file_index]);
		if (data)
			process_data_debug("from file", data, algo_name, flags);
		free(data);
	}
}