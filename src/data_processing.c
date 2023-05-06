#include "ft_ssl.h"

void process_data_debug(const char *debug_msg, char *s, int flags) {
	(void) flags;
	printf("PROCESSED: [src: %s], [data: %s]\n", debug_msg, s);
}