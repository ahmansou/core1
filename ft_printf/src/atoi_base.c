/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 11:57:27 by jbouazao          #+#    #+#             */
/*   Updated: 2020/10/17 15:19:00 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_base(unsigned long long nbr, int base)
{
	char				*str;
	unsigned long long	temp;
	int					count;
	char				*res;

	temp = nbr;
	str = "0123456789abcdef";
	if (!(count = 0) && nbr == 0)
	{
		res = ft_strnew(1);
		res[0] = '0';
		return (res);
	}
	while (temp != 0 && count++ > -1)
		temp /= base;
	res = ft_strnew(count);
	while (nbr != 0)
	{
		res[--count] = str[nbr % base];
		nbr /= base;
	}
	return (res);
}

char	*itoa_basecap(unsigned long long nbr, int base)
{
	char				*str;
	unsigned long long	temp;
	int					count;
	char				*res;

	temp = nbr;
	str = "0123456789ABCDEF";
	if (!(count = 0) && nbr == 0)
	{
		res = ft_strnew(1);
		res[0] = '0';
		return (res);
	}
	while (temp != 0 && count++ > -1)
		temp /= base;
	res = ft_strnew(count);
	while (nbr != 0)
	{
		res[--count] = str[nbr % base];
		nbr /= base;
	}
	return (res);
}
