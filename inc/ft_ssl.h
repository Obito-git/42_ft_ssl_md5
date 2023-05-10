#ifndef INC_42_FT_SSL_MD5_FT_SSL_H
#define INC_42_FT_SSL_MD5_FT_SSL_H

#include "libft.h"
#include "error_msg.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>

/*  ALGORITHM HEADERS */
#include "sha256.h"

#define ARG_STDIN   	1	// -p will print STDIN string before generated hash
#define ARG_QUITE       2	// -q nothing extra, only hash
#define ARG_REVERSE     4	// -r print hash then src
#define ARG_STRING      8	// -s will take string provided in arg
#define ARG_PURE_STDIN	16	// stdin without provided args

typedef unsigned char uchar;
typedef char *(*t_algorithm_ptr)(const uchar *, size_t len);

typedef struct {
	size_t	len;
	uchar	*data;
	char	*file_name;
} data_t;

typedef struct s_hash_algorithm {
	const char			*name;
	t_algorithm_ptr		algorithmPtr;
} t_hash_algorithm;

/*	config.c */
extern t_hash_algorithm algorithms[];
t_hash_algorithm	*getAlgorithmByName(const char *name);

/*  exit_error.c */
void				exit_error(const char *msg);

/*	source_processing.c */
void				read_stdin(data_t *data);
void				read_file(const char *name, char *algoname, data_t *data);

/*	data_processing.c */
void				process_data(data_t *data, char *algoname, int *flags);


#endif //INC_42_FT_SSL_MD5_FT_SSL_H
