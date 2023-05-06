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

#define ARG_STDIN   	1 // -p will print STDIN string before generated hash
#define ARG_QUITE       2 // -q nothing extra, only hash
#define ARG_REVERSE     4 // -r print hash then src
#define ARG_STRING      8 // -s will take string provided in arg

typedef const char *(*t_algorithm_ptr)(char *);

typedef struct s_hash_algorithm {
	const char *name;
	t_algorithm_ptr algorithmPtr;
} t_hash_algorithm;

extern t_hash_algorithm algorithms[];

/*  PROTOTYPES */
void exit_error(const char *msg);
t_hash_algorithm *getAlgorithmByName(const char *name);
char *read_stdin();
char *read_file(const char *name);


//FIXME delete
void process_data_debug(const char *debug_msg, char *s, int flags);


#endif //INC_42_FT_SSL_MD5_FT_SSL_H
