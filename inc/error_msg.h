//
// Created by Anton on 22/04/2023.
//

#ifndef INC_42_FT_SSL_MD5_ERROR_MSG_H
#define INC_42_FT_SSL_MD5_ERROR_MSG_H

#define ERR_USAGE "Usage: ft_ssl [algorithm name] [options] [string, filename...]\n\
 The options are:\n\
  -p                     echo STDIN to STDOUT and append the checksum to STDOUT\n\
  -q                     quiet mode\n\
  -r                     reverse the format of the output.\n\
  -s                     print the sum of the given string"

#define ERR_CONFIG_EMPTY "Config error: can't find any algorithm"

#define ERR_CONFIG_FUNC(name) ("Config error: " #name ": has NULL pointer function")

#define PRINT_ERR_NOT_FOUND(name) ft_fprintf(STDERR_FILENO, "%s\n\nError. Can't find '%s', list of available algorithms:\n", ERR_USAGE, *(char**)&name)

#define PRINT_ERR_UNKNOWN_ARG(name) ft_fprintf(STDERR_FILENO, "Error. Unknown option \'-%s\'\n\n%s\n", name, ERR_USAGE)

#define ERROR_MALLOC "Error. Can't allocate memory"


#endif //INC_42_FT_SSL_MD5_ERROR_MSG_H
