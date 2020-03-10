/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:35:47 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/10 14:50:41 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		_st(t_token **op, char **sp)
{	
	// ft_printf("%s %x ok\n", (*op)->name, (*op)->code);
	if (
		!sp[0] || !sp[1] || !sp[2] ||
		(sp[3] && sp[3][0] != ';' && sp[3][0] != '#') ||
		(sp[1] && (sp[1][0] == 'r' || sp[1][0] == 'R') && !is_num(sp[1] + 1)) ||
		(sp[2] && sp[2][0] != 'r' && sp[2][0] != 'R' && sp[2][0] != ':' &&
		!is_num_neg(sp[2]))
		)
		return (0);
	(*op)->args[0] = ft_atoi(sp[1] + 1);
	if ((*op)->args[0] > REG_NUMBER || (*op)->args[0] < 0)
		return (0);
	if (sp[2][1] == ':' && ((*op)->args[1] = 2748))
		(*op)->labels[1] = ft_strdup(sp[2] + 2);
	else if (is_num_neg(sp[2]))
		(*op)->args[1] = ft_atoi(sp[2]);
	else if (sp[2][1] == 'r')
		(*op)->args[1] = ft_atoi(sp[2] + 1);
	get_argc_types(op, sp);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
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
	max = ft_strlen(s);
	i = (max % 2 != 0) ? 1 : 0;
	while (i < maxi - max)
	{
		ft_putchar_fd(00, fd);
		i += 2;
	}
	maxi = (max > maxi) ? max - maxi : 0;
	i = maxi;
	while (i < ft_strlen(s))
	{
		a = (i == maxi && max % 2 != 0) ? ft_strsub(s, i, 1) : ft_strsub(s, i, 2);
		ft_putchar_fd(ft_atoi_base(a, 16), fd);
		ft_strdel(&a);
		i += (i == maxi && max % 2 != 0) ? 1 : 2;
	}
}

void	print_st(t_token *token, int fd)
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
