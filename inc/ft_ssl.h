#ifndef INC_42_FT_SSL_MD5_FT_SSL_H
#define INC_42_FT_SSL_MD5_FT_SSL_H

#include "error_msg.h"
#include <stdlib.h>

#include <stdio.h> //FIXME DELETE
/*  ALGORITHM HEADERS */
#include "sha256.h"

enum ARGS {ARG_SHOW_DATA, ARG_QUITE, ARG_REVERSE, ARG_STRING};

typedef const char *(*algorithm_ptr_t)(char *);

typedef struct s_hash_algorithm {
	const char *name;
	algorithm_ptr_t algorithmPtr;
} t_hash_algorithm;

extern t_hash_algorithm algorithms[];

/*  PROTOTYPES */
size_t	ft_strlen(const char *str);



#endif //INC_42_FT_SSL_MD5_FT_SSL_H
