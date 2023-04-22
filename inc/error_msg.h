//
// Created by Anton on 22/04/2023.
//

#ifndef INC_42_FT_SSL_MD5_ERROR_MSG_H
#define INC_42_FT_SSL_MD5_ERROR_MSG_H

#define ERR_USAGE "Usage: ft_ssl [algorithm name] [options] [filenames...]\n\
 The options are:\n\
  -p                     Display only external symbols\n\
  -q                     Do not sort the symbols\n\
  -r                     Display only undefined symbols\n\
  -s                     Display only undefined symbols"

#define ERR_CONFIG_EMPTY "Config error: can't find any algorithm"

#define ERR_CONFIG_FUNC(name) ("Config error: " #name ": has NULL pointer function")

#define PRINT_ERR_NOT_FOUND(name) ft_fprintf(STDERR_FILENO, "Error. Can't find '%s', list of available algorithms:\n", *(char**)&name)

#define PRINT_ERR_UNKNOWN_ARG(name) ft_fprintf(STDERR_FILENO, "Error. Unknown option \'-%s\'\n\n%s\n", name, ERR_USAGE)


#endif //INC_42_FT_SSL_MD5_ERROR_MSG_H
