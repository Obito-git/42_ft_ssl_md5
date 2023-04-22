#include "ft_ssl.h"

void exit_error(const char *msg) {
	ft_fprintf(STDERR_FILENO, "%s\n", msg);
	exit(1);
}
