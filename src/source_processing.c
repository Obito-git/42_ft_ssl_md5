#include "ft_ssl.h"
#define READ_SIZE 10240

static void read_fd(int fd, data_t *data) {
	uchar buf[READ_SIZE + 1];
	ssize_t bytes_read;
	
	while ((bytes_read = read(fd, buf, READ_SIZE)) > 0) {
		uchar tmp[data->len + bytes_read];
		
		ft_memcpy(tmp, data->data, data->len);
		ft_memcpy(&tmp[data->len], buf, bytes_read);
		free(data->data);
		data->len += bytes_read;
		data->data = malloc(sizeof(uchar) * data->len + 1); //FIXME malloc prot
		if (!data->data) {
			ft_fprintf(STDERR_FILENO, "%s\n", ERROR_MALLOC);
			data->len = 0;
			return;
		}
		ft_memcpy(data->data, tmp, data->len);
		data->data[data->len] = '\0';
	}
	if (bytes_read == -1) {
		ft_fprintf(STDERR_FILENO, "%s\n", ERROR_MALLOC);
		free(data->data);
		data->data = NULL;
		data->len = 0;
	}
}

void read_file(const char *name, char *algoname, data_t *data) {
	int fd = open(name, O_RDONLY);
	if (fd < 0) {
		ft_fprintf(STDERR_FILENO, "ft_ssl: %s: %s: %s\n", algoname, name, strerror(errno));
		return;
	}
	read_fd(fd, data);
	close(fd);
}

void read_stdin(data_t *data) {
	read_fd(STDIN_FILENO, data);
}