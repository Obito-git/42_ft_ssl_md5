#include "ft_ssl.h"

static void check_algorithm_name(const char *provided_name) {
	if (!algorithms[0].name) {
		exit_error(ERR_CONFIG_EMPTY);
	}
	for (size_t i = 0; algorithms[i].name; i++) {
		if (!algorithms[i].algorithmPtr)
			exit_error(ERR_CONFIG_FUNC(algorithms[i].name));
		if (ft_strcmp(provided_name, algorithms[i].name) == 0)
			return;
	}
	//ft_fprintf(STDERR_FILENO, "Error. Can't find %s, list of available algorithms:\n", provided_name);
	PRINT_ERR_NOT_FOUND(provided_name);
	for (size_t i = 0; algorithms[i].name; i++) {
		ft_fprintf(STDERR_FILENO, "\t- %s\n", algorithms[i].name);
	}
	exit(1);
}

static int process_args(int ac, char **av, int *flags) {
	int files_count = 0;

	check_algorithm_name(av[1]);

	for (int i = 2; i < ac; i++) {
		size_t arg_len = ft_strlen(av[i]);
		if (av[i][0] == '-' && arg_len > 1) {
			if (av[i][1] == 'p') {
				*flags |= ARG_SHOW_DATA;
			} else if (av[i][1] == 'q') {
				*flags |= ARG_QUITE;
			} else if (av[i][1] == 'r') {
				*flags |= ARG_REVERSE;
			} else if (av[i][1] == 's') {
				*flags |= ARG_STRING;
			} else {
				PRINT_ERR_UNKNOWN_ARG(&av[i][1]);
				exit(1);
			}
		} else if (av[i][0] == '-' && arg_len == 1) {
			exit_error(ERR_USAGE);
		} else {
			files_count++;
		}
	}
	return files_count;
}

int main(int ac, char **av) {
	int flags = 0;

	if (ac < 2)
		exit_error(ERR_USAGE);
	process_args(ac, av, &flags);
	//FIXME DEBUG START
	if (flags == 0)
		ft_printf("No flags detected\n");
	if (flags & ARG_SHOW_DATA)
		ft_printf("-p detected\n");
	if (flags & ARG_STRING)
		ft_printf("-s detected\n");
	if (flags & ARG_REVERSE)
		ft_printf("-r detected\n");
	if (flags & ARG_QUITE)
		ft_printf("-q detected\n");
	//FIXME DEBUG END
}