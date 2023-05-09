#include "libft.h"

char *ft_strtobinstr(char *str) {
	size_t	len;
	char	*bin_str;
	char 	*p;

	len = ft_strlen(str);
	bin_str = malloc(len * 8 + 1);
	if (bin_str == NULL)
		return NULL;
	p = bin_str;
	for (size_t i = 0; i < len; i++) {
		for (int j = 7; j >= 0; j--) {
			if ((str[i] >> j) & 1) {
				*p = '1';
			} else {
				*p = '0';
			}
			p++;
		}
	}
	return bin_str;
}