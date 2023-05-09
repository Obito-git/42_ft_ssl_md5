/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:32:05 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 12:53:23 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
static char getType(char *s) {
	if (ft_strncmp(s, "c", 1) == 0)
		return 'c';
	if (ft_strncmp(s, "s", 1) == 0)
		return 's';
	if (ft_strncmp(s, "p", 1) == 0)
		return 'p';
	if (ft_strncmp(s, "d", 1) == 0)
		return 'd';
	if (ft_strncmp(s, "i", 1) == 0)
		return 'i';
	if (ft_strncmp(s, "x", 1) == 0)
		return 'x';
	if (ft_strncmp(s, "X", 1) == 0)
		return 'X';
	if (ft_strncmp(s, "u", 1) == 0)
		return 'u';
	if (ft_strncmp(s, "bs", 2) == 0)
		return 'v';
	if (ft_strncmp(s, "bu", 2) == 0)
		return 'b';
	if (ft_strncmp(s, "bc", 2) == 0)
		return 'n';
	return (0);
}

static size_t	find_pattern(t_arg	*ar, int fd)
{
	if (ar->type == 'd' || ar->type == 'i')
		return (d_pattern(ar, fd));
	if (ar->type == 's' || ar->type == 'c')
		return (s_pattern(ar, fd));
	if (ar->type == 'p')
		return (p_pattern(ar, fd));
	if (ar->type == 'u')
		return (u_pattern(ar, fd));
	if (ar->type == 'x' || ar->type == 'X')
		return (xx_pattern(ar, fd));
	if (ar->type == 'b')
		return (bu_pattern(ar, fd));
	if (ar->type == 'v')
		return (bs_pattern(ar, fd));
	if (ar->type == 'n')
		return (bc_pattern(ar, fd));
	return (0);
}

size_t	print_pattern(char type, void *var_content, int fd)
{
	t_arg	*ar;

	ar = get_init_arg();
	if (ar == NULL)
		return (0);
	ar->type = type;
	ar->content = var_content;
	return (find_pattern(ar, fd));
}

void	*parse_content(va_list *ar, char type)
{
	void			*mem;
	long			*l;
	unsigned long	*ul;
	uint32_t		*uint32;
	
	if (ar == NULL)
		return (NULL);
	mem = malloc(100);
	if (mem && (type == 'd' || type == 'c' || type == 'i' || type == 'n'))
	{
		l = mem;
		*l = va_arg(*ar, int);
	} 
	if (mem && (type == 's' || type == 'v')) {
		free(mem);
		return ((void *) ft_strdup(va_arg(*ar, char *)));
	}
	if (mem && (type == 'p' || type == 'u' || type == 'x' || type == 'X'))
	{
		ul = mem;
		*ul = (type == 'p' ? va_arg(*ar, unsigned long) : va_arg(*ar, unsigned int));
	}
	if (mem && type == 'b')
	{
		uint32 = mem;
		*uint32 = va_arg(*ar, uint32_t);
	}
	return (mem);
}

size_t	parse(int fd, va_list *ar, char *str)
{
	size_t	i;
	size_t	printed_chars;
	char	type;

	i = 0;
	printed_chars = 0;
	while (str[i])
	{
		if (str[i] == '%' && (type = getType(&str[i + 1])))
		{
			printed_chars += print_pattern(type,
					parse_content(ar, type), fd);
			i += ((type == 'v' || type == 'b' || type == 'n') ? 3 : 2);
			continue ;
		}
		if (str[i] == '%' && str[i + 1] == '%')
			i++;
		ft_putchar_fd(str[i], fd);
		printed_chars++;
		i++;
	}
	return (printed_chars);
}
