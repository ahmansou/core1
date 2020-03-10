/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:14:05 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/10 16:31:18 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 2},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 2},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
};

const t_op	*get_op_tab(void)
{
	return (op_tab);
}

const t_op_types op_type = 
{
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
	// {0, 1, 2, 3, 4},
	{&_live, &_ld, &_st, &_add, &_add, &_and, &_and,
		&_and, &_live, &_ldi, &_sti, &_live, &_ld, &_ldi, &_live, &_aff}
};

t_op_types get_o_types(void)
{
	return (op_type);
}

int	skip_ws(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' '
			|| line[i] == '\t'
			|| line[i] == '\v'
			// || line[i] == '\n'
			)
			i++;
	return (i);
}

int		is_label(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != LABEL_CHAR)
	{
		if (!is_label_char(s[i]))
			return (0);
		i++;
	}
	if (s[i] == LABEL_CHAR)
		return (i);
	return (0);
}

void	free2d(char ***s)
{
	int i;

	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		i++;
	}
	free(*s);
}

int		count_int(int n)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int				is_num(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

int				is_num_neg(char *s)
{
	int i;

	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}


int	calc_sz(char *argc, int dirsz)
{
	int sz;

	sz = 1;
	if (argc[0] == T_REG)
		sz += 1;
	else if (argc[0] == T_DIR)
		sz += dirsz;
	else if (argc[0] == T_IND)
		sz += 2;
	
	if (argc[1] == T_REG)
		sz += 1;
	else if (argc[1] == T_DIR)
		sz += dirsz;
	else if (argc[1] == T_IND)
		sz += 2;
	
	if (argc[2] == T_REG)
		sz += 1;
	else if (argc[2] == T_DIR)
		sz += dirsz;
	else if (argc[2] == T_IND)
		sz += 2;
	return (sz);
}


void	get_argc_types(t_token **op, char **sp)
{
	if (sp[1] && sp[1][0] == 'r')
		(*op)->argc[0] = T_REG;
	else if (sp[1] && sp[1][0] == '%')
		(*op)->argc[0] = T_DIR;
	else if (sp[1] && (is_num_neg(sp[1]) || sp[1][0] == ':'))
		(*op)->argc[0] = T_IND;
	else
		(*op)->argc[0] = 0;

	if (sp[2] && sp[2][0] == 'r')
		(*op)->argc[1] = T_REG;
	else if (sp[2] && sp[2][0] == '%')
		(*op)->argc[1] = T_DIR;
	else if (sp[2] && (is_num_neg(sp[2]) || sp[2][0] == ':'))
		(*op)->argc[1] = T_IND;
	else
		(*op)->argc[1] = 0;
		
	if (sp[3] && sp[3][0] == 'r')
		(*op)->argc[2] = T_REG;
	else if (sp[3] && sp[3][0] == '%')
		(*op)->argc[2] = T_DIR;
	else if (sp[3] && (is_num_neg(sp[3]) || sp[3][0] == ':'))
		(*op)->argc[2] = T_IND;
	else
		(*op)->argc[2] = 0;
}
