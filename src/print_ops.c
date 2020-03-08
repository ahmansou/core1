/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 12:48:30 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/08 15:36:23 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

void	ld_misc(char *s, t_token *token, int fd, int t)
{
	int i;
	int	max;
	char	*a;
	int	maxi;
	
	maxi = (token->argc[t] == T_DIR) ? 8 : 4;
	max = ft_strlen(s);
	i = (max % 2 != 0) ? 1 : 0;
	while (i < maxi - max)
	{
		ft_putchar_fd(00, fd);
		ft_putchar_fd(00, 1);
		i += 2;
	}
	i = 0;
	while (i < ft_strlen(s))
	{
		a = (i == 0 && max % 2 != 0) ? ft_strsub(s, i, 1) : ft_strsub(s, i, 2);
		ft_putchar_fd(ft_atoi_base(a, 16), fd);
		ft_putstr_fd(itoa_base(ft_atoi_base(a, 16), 16), 1);
		ft_strdel(&a);
		i += (i == 0 && max % 2 != 0) ? 1 : 2;
	}
	ft_putchar_fd(' ', 1);
}

void	print_live(t_token *token, int fd, int *sz)
{
	char	*s;
	char	*a;
	int i;
	int	max;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ld_misc(s, token, fd, 0);
	ft_strdel(&s);
}


void	print_ld(t_token *token, int fd, int *sz)
{
	char	*s;
	char	*a;
	int i;
	int	max;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd(' ', 1);
	ft_strdel(&s);
	s = itoa_base(token->encode, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd(' ', 1);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ld_misc(s, token, fd, 0);
	ft_strdel(&s);
	s = itoa_base(token->args[1], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd('\n', 1);
	ft_strdel(&s);
}

void	print_add_sub(t_token *token, int fd, int *sz)
{
	char	*s;
	char	*a;
	int i;
	int	max;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd(' ', 1);
	ft_strdel(&s);
	s = itoa_base(token->encode, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd(' ', 1);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd(' ', 1);
	ft_strdel(&s);
	s = itoa_base(token->args[1], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd(' ', 1);
	ft_strdel(&s);
	s = itoa_base(token->args[2], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_putstr_fd(itoa_base(ft_atoi_base(s, 16), 16), 1);
	ft_putchar_fd('\n', 1);
	ft_strdel(&s);
}


////////////////////////

void	sti_misc(char *s, t_token *token, int fd, int t)
{
	int i;
	int	max;
	char	*a;
	int	maxi;
	
	maxi = 2;
	maxi = (token->argc[t] == T_DIR || token->argc[t] == T_IND) ? 4 : maxi;
	max = ft_strlen(s);
	i = (max % 2 != 0) ? 1 : 0;
		while (i < maxi - max)
		{
			ft_putchar_fd(00, fd);
			i += 2;
		}
	i = 0;
	while (i < ft_strlen(s))
	{
		a = (i == 0 && max % 2 != 0) ? ft_strsub(s, i, 1) : ft_strsub(s, i, 2);
		ft_putchar_fd(ft_atoi_base(a, 16), fd);
		ft_strdel(&a);
		i += (i == 0 && max % 2 != 0) ? 1 : 2;
	}
}

void	print_sti(t_token *token, int fd, int *sz)
{
	char	*s;
	char	*a;
	int i;
	int	max;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->encode, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[1], 16);
	sti_misc(s, token, fd, 1);
	ft_strdel(&s);
	s = itoa_base(token->args[2], 16);
	sti_misc(s, token, fd, 2);
	ft_strdel(&s);
}

void	print_and_xor(t_token *token, int fd, int *sz)
{
	char	*s;
	char	*a;
	int i;
	int	max;

	s = itoa_base(token->code, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->encode, 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[0], 16);
	ft_putchar_fd(ft_atoi_base(s, 16), fd);
	ft_strdel(&s);
	s = itoa_base(token->args[1], 16);
	sti_misc(s, token, fd, 1);
	ft_strdel(&s);
	s = itoa_base(token->args[2], 16);
	sti_misc(s, token, fd, 2);
	ft_strdel(&s);
}
