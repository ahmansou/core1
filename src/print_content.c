/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:36:22 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/10 13:27:38 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

void		print_magic_header(int fd)
{
	char *s;
	int i;

	s = itoa_base(COREWAR_EXEC_MAGIC, 16);
	ft_putchar_fd(00, fd);
	// sz++;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(ft_atoi_base(ft_strsub(&s[i], 0, 2), 16), fd);
		// (*sz)++;
		i += 2;
	}
	ft_strdel(&s);
}

void		print_name_comnt(int fd, char *name, int max)
{
	int i;
	int k;
	
	i = -1;
	while (name[++i])
	{
		ft_putchar_fd(ft_atoi_base(itoa_base(name[i], 16), 16), fd);
		// (*sz)++;
	}
	i--;
	while (++i < max)
	{
		ft_putchar_fd(00, fd);
		// (*sz)++;
	}
}

void		print_null(int fd)
{
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, fd);
		// (*sz) += 4;
}

void		print_exec_code(int fd, t_token *tk)
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
		{
			if (ttoken->code == 1 || ttoken->code == 9 ||
				ttoken->code == 12 || ttoken->code == 15)
				print_live(ttoken, fd);
			if (ttoken->code == 2 || ttoken->code == 13)
				print_ld(ttoken, fd);
			if (ttoken->code == 3)
				print_st(ttoken, fd);
			if (ttoken->code == 4 || ttoken->code == 5)
				print_add_sub(ttoken, fd);
			if (ttoken->code == 6 || ttoken->code == 7 || ttoken->code == 8)
				print_and_xor(ttoken, fd);
			if (ttoken->code == 10 || ttoken->code == 14)
				print_ldi(ttoken, fd);
			if (ttoken->code == 11)
				print_sti(ttoken, fd);
		}
		ttoken = ttoken->next;
	}
}

void		print_content(t_token *ttoken, char *fn, int sz)
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
	sz = calc_exec_code_sz(ttoken);
	print_magic_header(fd);
	while (tk)
	{
		if (tk->type == 1)
			print_name_comnt(fd, tk->name, PROG_NAME_LENGTH);
		else if (tk->type == 2)
		{
			print_null(fd);
			print_exec_code_size(fd, sz);
			print_name_comnt(fd, tk->name, COMMENT_LENGTH);
			print_null(fd);
		}
		tk = tk->next;
	}
	print_exec_code(fd, ttoken);
}
