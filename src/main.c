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
	data_t data;
	data.data = NULL;
	data.len = 0;

	if (ac < 2)
		exit_error(ERR_USAGE);
	file_index = process_args(ac, av, &flags);

	if (file_index == ac || flags & ARG_STDIN) {
		read_stdin(&data);
		if (data.data)
			process_data(&data, av[1], flags);
		free(data.data);
	}
	if (flags & ARG_STRING) {
		data.data = (uchar *) av[file_index];
		data.len = ft_strlen(av[file_index++]);
		process_data(&data, av[1], flags);
	}
	for (; file_index < ac; file_index++) {
		data.data = NULL;
		data.len = 0;
		read_file(av[file_index], &data);
		if (data.data)
			process_data(&data, av[1], flags);
		free(data.data);
	}
}