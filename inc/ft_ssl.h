#ifndef INC_42_FT_SSL_MD5_FT_SSL_H
#define INC_42_FT_SSL_MD5_FT_SSL_H

#include "libft.h"
#include "error_msg.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <stdio.h> //FIXME DELETE
/*  ALGORITHM HEADERS */
#include "sha256.h"

#define ARG_STDIN   	1	// -p will print STDIN string before generated hash
#define ARG_QUITE       2	// -q nothing extra, only hash
#define ARG_REVERSE     4	// -r print hash then src
#define ARG_STRING      8	// -s will take string provided in arg

#define BITS_IN_BYTE 8

typedef unsigned char uchar;
typedef char *(*t_algorithm_ptr)(const uchar *, size_t len);

typedef struct s_hash_algorithm {
	const char			*name;
	t_algorithm_ptr		algorithmPtr;
} t_hash_algorithm;

typedef struct {
	size_t	len;
	uchar	*data;
} data_t;

extern t_hash_algorithm algorithms[];

/*  PROTOTYPES */
void exit_error(const char *msg);
t_hash_algorithm *getAlgorithmByName(const char *name);
void read_stdin(data_t *data);
void read_file(const char *name, data_t *data);


//FIXME delete
void process_data(data_t *data, char *algoname, int flags);


#endif //INC_42_FT_SSL_MD5_FT_SSL_H
