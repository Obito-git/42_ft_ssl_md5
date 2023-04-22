#include "ft_ssl.h"
/*
static int process_args(int ac, char **av, char **file_names, enum Sort *sort, enum Display *display) {
	int files_count = 0;

	for (int i = 1; i < ac; i++) {
		size_t arg_len = ft_strlen(av[i]);
		if (av[i][0] == '-' && arg_len > 1) {
			for (size_t y = 1; y < arg_len; y++) {
				if (av[i][y] == 'a') {
					if (DISPLAY_ALL > *display)
						*display = DISPLAY_ALL;
				} else if (av[i][y] == 'g') {
					if (DISPLAY_EXTERNAL > *display)
						*display = DISPLAY_EXTERNAL;
				} else if (av[i][y] == 'u') {
					if (DISPLAY_UNDEFINED > *display)
						*display = DISPLAY_UNDEFINED;
				} else if (av[i][y] == 'r') {
					if (SORT_REVERSE > *sort)
						*sort = SORT_REVERSE;
				} else if (av[i][y] == 'p') {
					if (SORT_NO > *sort)
						*sort = SORT_NO;
				} else {
					PRINT_UNKNOWN_ARG_ERROR(av[i][y]);
					return -1;
				}
			}
		} else
			file_names[files_count++] = av[i];
	}
	return files_count;
}
 */

int main() {
	printf("%s\n", algorithms[0].name);
	printf("%s\n", (*algorithms[0].algorithmPtr)("Hello from sha256"));
}