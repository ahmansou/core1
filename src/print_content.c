/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:36:22 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/07 19:03:21 by ahmansou         ###   ########.fr       */
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

void		print_exec_code(int fd, t_token *tk, int *sz)
{
	t_token	*ttoken;
	char	*s;
	char	*a;
	int i;

	ttoken = tk;
	// ft_printf("%s", tk->name);
	if (!ttoken)
		ft_printf("nah");
	while (ttoken)
	{
		if (ttoken->type == 4)
			if (ttoken->code == 1)
				print_live(ttoken, fd, sz);
			if (ttoken->code == 2)
				print_ld(ttoken, fd, sz);
			if (ttoken->code == 4 || ttoken->code == 5)
				print_add_sub(ttoken, fd, sz);
			if (ttoken->code == 11)
				print_sti(ttoken, fd, sz);
		ttoken = ttoken->next;
	}
}

void		print_content(t_token *ttoken, char *fn, int *sz)
{
	int fd;
	char	*nfn;
	// char	*hex;
	t_token	*tk;
	
	tk = ttoken;
	nfn = renamefn(fn);
	if ((fd = open(nfn, O_RDWR | O_CREAT, 0644)) < 0)
	{
		ft_printf("no can do");
		return ;
	}
	ft_printf("Creating the file %s\n", nfn);
	print_magic_header(fd,sz);
	while (tk)
	{
		if (tk->type == 1)
			print_name_comnt(fd, tk->name, PROG_NAME_LENGTH, sz);
		else if (tk->type == 2)
		{
			print_null(fd, sz);
			print_exec_code_size(fd, sz);
			print_name_comnt(fd, tk->name, COMMENT_LENGTH, sz);
			print_null(fd, sz);
		}
		tk = tk->next;
	}
	print_exec_code(fd, ttoken, sz);
}
