/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:09:30 by amyroshn          #+#    #+#             */
/*   Updated: 2021/12/06 15:24:37 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef struct s_arg
{
	char	type;
	void	*content;
}				t_arg;

int		ft_printf(const char *s, ...);
int		ft_fprintf(int fd, const char *s, ...);
size_t	parse(int fd, va_list *ar, char *str);
size_t	print_pattern(char type, void *var_content, int fd);
size_t	d_pattern(t_arg *ar, int fd);
size_t	bs_pattern(t_arg *ar, int fd);
size_t	bu_pattern(t_arg *ar, int fd);
size_t	bc_pattern(t_arg *ar, int fd);
size_t	s_pattern(t_arg *ar, int fd);
size_t	p_pattern(t_arg *ar, int fd);
size_t	u_pattern(t_arg *ar, int fd);
size_t	xx_pattern(t_arg *ar, int fd);
t_arg	*get_init_arg(void);
void	arg_del(t_arg *ar);
#endif
