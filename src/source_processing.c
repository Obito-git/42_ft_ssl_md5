#include "ft_ssl.h"
#define READ_SIZE 1024

static char *read_fd(int fd) {
	char buf[READ_SIZE];
	ssize_t bytes_read = 0;
	char *result = ft_strdup("");
	if (!result) {
		close(fd);
		exit_error(ERROR_MALLOC);
	}
	while ((bytes_read = read(fd, buf, READ_SIZE)) > 0) {
		char *tmp = ft_strjoin(result, buf);
		free(result);
		if (!tmp) {
			close(fd);
			exit_error(ERROR_MALLOC);
		}
		result = tmp;
		ft_bzero(buf, READ_SIZE);
	}
	if (bytes_read == -1) {
		close(fd);
		free(result);
		exit_error((const char *) strerror(errno));
	}
	return result;
}

char *read_file(const char *name) {
	int fd = open(name, O_RDONLY);
	if (fd < 0) {
		ft_fprintf(STDERR_FILENO, "%s\n", strerror(errno));
		return NULL;
	}
	
	char *result = read_fd(fd);

	close(fd);
	return result;
}


char *read_stdin() {
	return read_fd(STDIN_FILENO);
}