/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_pattern.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:28:58 by amyroshn          #+#    #+#             */
/*   Updated: 2021/12/06 15:29:05 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

size_t	d_pattern(t_arg *ar, int fd)
{
	size_t	len;

	ft_putnbr_fd(*(long *)ar->content, fd);
	len = ft_numblen(*(long *)ar->content);
	arg_del(ar);
	return (len);
}

size_t	p_pattern(t_arg *ar, int fd)
{
	unsigned long	cont;
	size_t			len;
	char			*res;

	cont = (*(unsigned long *) ar->content);
	if (cont == 0)
	{
		ft_putstr_fd("0x0", fd);
		len = 3;
	}
	else
	{
		ft_putstr_fd("0x", fd);
		res = ft_convert_base(cont, BASE_HEX_LOWER);
		if (!res)
			return (0);
		ft_putstr_fd(res, fd);
		len = ft_strlen(res) + 2;
		free(res);
	}
	arg_del(ar);
	return (len);
}

size_t	s_pattern(t_arg *ar, int fd)
{
	size_t	len;

	if (ar->type == 'c')
	{
		ft_putchar_fd((char) *(int *)ar->content, fd);
		arg_del(ar);
		return (1);
	}
	if ((char *)ar->content == NULL)
	{
		ft_putstr_fd("(null)", fd);
		len = 6;
	}
	else
	{
		ft_putstr_fd((char *)ar->content, fd);
		len = ft_strlen((char *)ar->content);
	}
	arg_del(ar);
	return (len);
}

size_t	u_pattern(t_arg *ar, int fd)
{
	unsigned int	n;
	size_t			len;

	n = *(unsigned int *) ar->content;
	ft_putnbr_fd(n, fd);
	len = ft_numblen(n);
	arg_del(ar);
	return (len);
}

size_t	xx_pattern(t_arg *ar, int fd)
{
	unsigned int	cont;
	size_t			len;
	char			*res;

	cont = (*(unsigned int *) ar->content);
	res = ft_convert_base(cont, ar->type == 'x' ? BASE_HEX_LOWER : BASE_HEX_UPPER);
	ft_putstr_fd(res, fd);
	len = ft_strlen(res);
	free(res);
	arg_del(ar);
	return (len);
}

size_t	bu_pattern(t_arg *ar, int fd)
{
	uint32_t 		cont;
	char			res[33];

	cont = (*(uint32_t *) ar->content);
	for (int i = 0; i < 32; ++i) {
		res[i] = (cont & (1 << (31 - i))) ? '1' : '0';
	}
	res[32] = '\0';
	ft_putstr_fd(res, fd);
	arg_del(ar);
	return (32);
}

size_t	bs_pattern(t_arg *ar, int fd)
{
	size_t	len;
	char	*s;
	char 	*bin_str;

	s = (char *) ar->content;
	if (s == NULL)
	{
		ft_putstr_fd("(null)", fd);
		arg_del(ar);
		return (6);
	}
	bin_str = ft_strtobinstr(s);
	if (!bin_str) {
		len = 0;
	} else {
		ft_putstr_fd(bin_str, fd);
		len = ft_strlen(bin_str);
		free(bin_str);
	}
	arg_del(ar);
	return (len);
}

size_t	bc_pattern(t_arg *ar, int fd)
{
	uint32_t 		cont;
	char			res[9];

	cont = (*(unsigned char *) ar->content);
	for (int i = 0; i < 8; ++i) {
		res[i] = (cont & (1 << (7 - i))) ? '1' : '0';
	}
	res[8] = '\0';
	ft_putstr_fd(res, fd);
	arg_del(ar);
	return (32);
}
