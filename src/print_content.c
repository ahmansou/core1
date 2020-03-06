/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:36:22 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/06 11:36:47 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

void		print_magic_header(int fd, int *sz)
{
	char *s;
	int i;

	s = itoa_base(COREWAR_EXEC_MAGIC, 16);
	ft_putchar_fd(00, fd);
	(*sz)++;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(ft_atoi_base(ft_strsub(&s[i], 0, 2), 16), fd);
		(*sz)++;
		i += 2;
	}
	ft_strdel(&s);
}

void		print_name_comnt(int fd, char *name, int max, int *sz)
{
	int i;
	int k;
	
	i = -1;
	while (name[++i])
	{
		ft_putchar_fd(ft_atoi_base(itoa_base(name[i], 16), 16), fd);
		(*sz)++;
	}
	i--;
	while (++i < max)
	{
		ft_putchar_fd(00, fd);
		(*sz)++;
	}
}

void		print_null(int fd, int *sz)
{
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		(*sz) += 4;
}

void		print_exec_code_size(int fd, int *sz)
{
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		ft_putchar_fd(0x4d, fd);
		(*sz) += 4;
}
