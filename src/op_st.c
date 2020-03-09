/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:35:47 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/09 16:02:13 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		_st(t_token **op, char **sp)
{	
	ft_printf("%s %x ok\n", (*op)->name, (*op)->code);
	if (
		!sp[0] || !sp[1] || !sp[2] ||
		(sp[3] && sp[3][0] != ';' && sp[3][0] != '#') ||
		(sp[1] && (sp[1][0] == 'r' || sp[1][0] == 'R') && !is_num(sp[1] + 1)) ||
		(sp[2] && sp[2][0] != 'r' && sp[2][0] != 'R' && sp[2][0] != '%')
		)
		return (0);
	(*op)->args[0] = ft_atoi(sp[1] + 1);
	if ((*op)->args[0] > REG_NUMBER || (*op)->args[0] < 0)
		return (0);
	if (sp[2][0] == '%')
	{
		if (sp[2][1] == ':' && ((*op)->args[1] = 2748))
			(*op)->labels[1] = ft_strdup(sp[2] + 2);
		else
			(*op)->args[1] = ft_atoi(sp[2] + 1);
	}
	else
		(*op)->args[1] = ft_atoi(sp[2] + 1);
	(*op)->argc[0] = T_REG;
	(*op)->argc[1] = (sp[2][0] == '%') ? T_DIR : T_REG;
	(*op)->sz = (sp[2][0] == '%') ? 7 : 4;
	(*op)->encode = calc_encode(sp[1], sp[2], NULL);
	return (1);
}

void	st_misc(char *s, t_token *token, int fd, int t)
{
	int i;
	int	max;
	char	*a;
	int	maxi;
	
	maxi = 2;
	maxi = (token->argc[t] == T_IND) ? 4 : maxi;
	maxi = (token->argc[t] == T_DIR) ? 8 : maxi;
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

void	print_st(t_token *token, int fd, int *sz)
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
	st_misc(s, token, fd, 1);
	ft_strdel(&s);
}
