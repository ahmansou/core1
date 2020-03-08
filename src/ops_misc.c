/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:33:46 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/08 15:37:55 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		_live(t_token **op, char **sp)
{
	int i;

	i = 0;
	if (!sp[0] || !sp[1] ||
		(sp[2] && sp[2][0] != ';' && sp[2][0] != '#') ||
		(sp[1] && sp[1][0] != '%'))
		return (0);
	ft_printf("live %d | ", (*op)->tdir_sz);
	(*op)->is_encode = 0;
	// (*op)->sz = 5;
	(*op)->argc[0] = T_DIR;
	(*op)->argc[1] = 0;
	(*op)->argc[2] = 0;
	(*op)->args[0] = ft_atoi(sp[1] + 1);
	// get_argc_types(op, sp);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("| arg1 : %x | sz : %d", (*op)->args[0], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		_ld(t_token **op, char **sp)
{	
	if (!sp[0] || !sp[1] || !sp[2] ||
		(sp[3] && sp[3][0] != ';' && sp[3][0] != '#') ||
		(sp[1] && sp[1][0] != '%' && sp[1][0] != ':' && !ft_isdigit(sp[1][0])) ||
		(sp[1] && sp[1][0] == '%' && !is_num(sp[1] + 1)) ||
		(sp[2] && sp[2][0] != 'r') ||
		(sp[2] && sp[2][0] == 'r'  && !is_num(sp[2] + 1)))
		return (0);
	ft_printf("ld %d | ", (*op)->tdir_sz);
	(*op)->encode = calc_encode(sp[1], sp[2], NULL);
	if (sp[1][0] == '%')
	{
		if (sp[1][1] == ':')
			(*op)->args[0] = 2748;
		else
			(*op)->args[0] = ft_atoi(sp[1] + 1);
	}
	else
	{
		if (sp[1][0] == ':')
			(*op)->args[0] = 2748;
		else
			(*op)->args[0] = ft_atoi(sp[1]);
	}
	(*op)->argc[0] = (sp[1][0] == '%') ? T_DIR : T_IND;
	(*op)->args[1] = ft_atoi(sp[2] + 1);
	if ((*op)->args[1] > REG_NUMBER || (*op)->args[1] < 0)
		return (0);
	(*op)->sz = (sp[1][0] == '%') ? 7 : 5;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("encode : %x ", (*op)->encode);
	ft_printf("| arg1 : %x | arg2 : %x | sz : %d",
				(*op)->args[0], (*op)->args[1], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		_st(t_token **op, char **sp)
{	
	if (!sp[0] || !sp[1] || !sp[2] ||
		(sp[3] && sp[3][0] != ';' && sp[3][0] != '#') ||
		(sp[1] && sp[1][0] == 'r' && !is_num(sp[1] + 1)) ||
		(sp[2] && sp[2][0] != 'r' && sp[2][0] != '%')
		)
		return (0);
	ft_putendl("st");
	return (1);
}

int		_add(t_token **op, char **sp)
{		
	if (!sp[0] || !sp[1] || !sp[2] || !sp[3] ||
		(sp[4] && sp[4][0] != ';' && sp[4][0] != '#') ||
		((sp[1][0] != 'r') && (sp[1][0] != 'R')) ||
		((sp[2][0] != 'r') && (sp[2][0] != 'R')) ||
		((sp[3][0] != 'r') && (sp[3][0] != 'R')) ||
		(sp[1] && ((sp[1][0] == 'r') || (sp[1][0] == 'R')) && !is_num(sp[1] + 1)) ||
		(sp[2] && ((sp[2][0] == 'r') || (sp[2][0] == 'R')) && !is_num(sp[2] + 1)) ||
		(sp[3] && ((sp[3][0] == 'r') || (sp[3][0] == 'R')) && !is_num(sp[3] + 1)))
		return (0);
	ft_printf("add %d | ", (*op)->tdir_sz);
	(*op)->encode = calc_encode(sp[1], sp[2], sp[3]);
	(*op)->args[0] = ft_atoi(sp[1] + 1);
	(*op)->args[1] = ft_atoi(sp[2] + 1);
	(*op)->args[2] = ft_atoi(sp[3] + 1);
	if ((*op)->args[0] > REG_NUMBER || (*op)->args[0] < 0 ||
		(*op)->args[1] > REG_NUMBER || (*op)->args[1] < 0 ||
		(*op)->args[2] > REG_NUMBER || (*op)->args[2] < 0)
		return (0);
	get_argc_types(op, sp);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	// (*op)->sz = 5;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("encode : %x ", (*op)->encode);
	ft_printf("| arg1 : %x | arg2 : %x | arg3 : %x | sz : %d",
				(*op)->args[0], (*op)->args[1], (*op)->args[2], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		_sub(t_token **op, char **sp)
{
	if (!sp[0] || !sp[1] || !sp[2] || !sp[3] ||
		(sp[4] && sp[4][0] != ';' && sp[4][0] != '#') ||
		((sp[1][0] != 'r') && (sp[1][0] != 'R')) ||
		((sp[2][0] != 'r') && (sp[2][0] != 'R')) ||
		((sp[3][0] != 'r') && (sp[3][0] != 'R')) ||
		(sp[1] && ((sp[1][0] == 'r') || (sp[1][0] == 'R')) && !is_num(sp[1] + 1)) ||
		(sp[2] && ((sp[2][0] == 'r') || (sp[2][0] == 'R')) && !is_num(sp[2] + 1)) ||
		(sp[3] && ((sp[3][0] == 'r') || (sp[3][0] == 'R')) && !is_num(sp[3] + 1)))
		return (0);
	ft_printf("sub %d | ", (*op)->tdir_sz);
	(*op)->encode = calc_encode(sp[1], sp[2], sp[3]);
	(*op)->args[0] = ft_atoi(sp[1] + 1);
	(*op)->args[1] = ft_atoi(sp[2] + 1);
	(*op)->args[2] = ft_atoi(sp[3] + 1);
	if ((*op)->args[0] > REG_NUMBER || (*op)->args[0] < 0 ||
		(*op)->args[1] > REG_NUMBER || (*op)->args[1] < 0 ||
		(*op)->args[2] > REG_NUMBER || (*op)->args[2] < 0)
		return (0);
	get_argc_types(op, sp);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	// (*op)->sz = 5;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("encode : %x ", (*op)->encode);
	ft_printf("| arg1 : %x | arg2 : %x | arg3 : %x | sz : %d",
				(*op)->args[0], (*op)->args[1], (*op)->args[2], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		check_and_err(char **sp)
{
	if (!sp[0] || !sp[1] || !sp[2] || !sp[3] ||
		(sp[4] && sp[4][0] != ';' && sp[4][0] != '#') ||
		(sp[1] && sp[1][0] != 'r' && sp[1][0] != 'R' && sp[1][0] != '%' && !is_num(sp[1])) ||
		(sp[2] && sp[2][0] != 'r' && sp[2][0] != 'R' && sp[2][0] != '%' && !is_num(sp[2])) ||
		(sp[3] && sp[3][0] != 'r' && sp[3][0] != 'R') ||
		(sp[2] && (sp[1][0] == 'r' || sp[1][0] == 'R') && !is_num(sp[1] + 1)) ||
		(sp[2] && (sp[2][0] == 'r' || sp[2][0] == 'R') && !is_num(sp[2] + 1)) ||
		(sp[3] && (sp[3][0] == 'r' || sp[3][0] == 'R') && !is_num(sp[3] + 1)) ||
		(sp[1] && (sp[1][0] == '%' && sp[1][1] != ':') && !is_num(sp[1] + 1)) ||
		(sp[2] && (sp[2][0] == '%' && sp[2][1] != ':') && !is_num(sp[2] + 1))
		)
		return (0);
	return (1);
}

int		_and(t_token **op, char **sp)
{
	if (!check_and_err(sp))
		return (0);
	ft_printf("and %d | ", (*op)->tdir_sz);
	(*op)->encode = calc_encode(sp[1], sp[2], sp[3]);
	get_argc_types(op, sp);
	(*op)->argc[2] = T_REG;
	(*op)->args[0] = (sp[1][0] == 'r' || sp[1][0] == '%') ?
		ft_atoi(sp[1] + 1) : ft_atoi(sp[1]);
	(*op)->args[1] = (sp[2][0] == 'r' || sp[2][0] == '%') ?
		ft_atoi(sp[2] + 1) : ft_atoi(sp[2]);
	(*op)->args[2] = ft_atoi(sp[3] + 1);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("encode : %x ", (*op)->encode);
	ft_printf("| arg1 : %x | arg2 : %x | arg3 : %x | sz : %d",
				(*op)->args[0], (*op)->args[1], (*op)->args[2], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		_or(t_token **op, char **sp)
{
	if (!check_and_err(sp))
		return (0);
	ft_printf("or %d | ", (*op)->tdir_sz);
	(*op)->encode = calc_encode(sp[1], sp[2], sp[3]);
	get_argc_types(op, sp);
	(*op)->argc[2] = T_REG;
	(*op)->args[0] = (sp[1][0] == 'r' || sp[1][0] == '%') ?
		ft_atoi(sp[1] + 1) : ft_atoi(sp[1]);
	(*op)->args[1] = (sp[2][0] == 'r' || sp[2][0] == '%') ?
		ft_atoi(sp[2] + 1) : ft_atoi(sp[2]);
	(*op)->args[2] = ft_atoi(sp[3] + 1);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("encode : %x ", (*op)->encode);
	ft_printf("| arg1 : %x | arg2 : %x | arg3 : %x | sz : %d",
				(*op)->args[0], (*op)->args[1], (*op)->args[2], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		_xor(t_token **op, char **sp)
{
	if (!check_and_err(sp))
		return (0);
	ft_printf("xor %d | ", (*op)->tdir_sz);
	(*op)->encode = calc_encode(sp[1], sp[2], sp[3]);
	get_argc_types(op, sp);
	(*op)->argc[2] = T_REG;
	(*op)->args[0] = (sp[1][0] == 'r' || sp[1][0] == '%') ?
		ft_atoi(sp[1] + 1) : ft_atoi(sp[1]);
	(*op)->args[1] = (sp[2][0] == 'r' || sp[2][0] == '%') ?
		ft_atoi(sp[2] + 1) : ft_atoi(sp[2]);
	(*op)->args[2] = ft_atoi(sp[3] + 1);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("encode : %x ", (*op)->encode);
	ft_printf("| arg1 : %x | arg2 : %x | arg3 : %x | sz : %d",
				(*op)->args[0], (*op)->args[1], (*op)->args[2], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		_zjmp(t_token **op, char **sp)
{
	ft_putendl("zjmp");
	return (1);
}

int		_ldi(t_token **op, char **sp)
{
	ft_putendl("ldi");
	return (1);
}

int		check_sti_err(char **sp)
{
	if (!sp[0] || !sp[1] || !sp[2] || !sp[3] ||
		(sp[4] && sp[4][0] != ';' && sp[4][0] != '#') ||
		(sp[1] && sp[1][0] != 'r' && sp[1][0] != 'R') ||
		(sp[2] && sp[2][0] != 'r' && sp[2][0] != 'R' && sp[2][0] != '%' && !is_num(sp[2])) ||
		(sp[3] && sp[3][0] != 'r' && sp[3][0] != 'R' && sp[2][0] != '%') ||
		(sp[2] && (sp[1][0] == 'r' || sp[1][0] == 'R') && !is_num(sp[1] + 1)) ||
		(sp[2] && (sp[2][0] == 'r' || sp[2][0] == 'R') && !is_num(sp[2] + 1)) ||
		(sp[3] && (sp[3][0] == 'r' || sp[3][0] == 'R') && !is_num(sp[3] + 1)) ||
		(sp[2] && (sp[2][0] == '%' && sp[2][1] != ':') && !is_num(sp[2] + 1)) || 
		(sp[1] && (sp[3][0] == '%' && sp[3][1] != ':') && !is_num(sp[3] + 1))
		)
		return (0);
	return (1);
}

int		_sti(t_token **op, char **sp)
{
	if (!check_sti_err(sp))
		return (0);
	ft_printf("sti %d | ", (*op)->tdir_sz);
	(*op)->encode = calc_encode(sp[1], sp[2], sp[3]);
	(*op)->args[0] = ft_atoi(sp[1] + 1);
	if (sp[2][0] == 'r')
		(*op)->args[0] = ft_atoi(sp[1] + 1);
	else if (sp[2][0] == '%')
	{
		if (sp[2][1] == ':')
			(*op)->args[1] = 2748;
		else
			(*op)->args[1] = ft_atoi(sp[2] + 1);
	}
	else if (is_num(sp[2]))
		(*op)->args[1] = ft_atoi(sp[2]);
	(*op)->args[2] = ft_atoi(sp[3] + 1);
	(*op)->args[2] = ft_atoi(sp[3] + 1);
	(*op)->argc[2] = (sp[3][0] == 'r') ? T_REG : T_DIR;
	get_argc_types(op, sp);
	(*op)->sz = calc_sz((*op)->argc, (*op)->tdir_sz) + 1;
	ft_printf("code : %x ", (*op)->code);
	ft_printf("encode : %x ", (*op)->encode);
	ft_printf("| arg1 : %x | arg2 : %x | arg3 : %x | sz : %d",
				(*op)->args[0], (*op)->args[1], (*op)->args[2], (*op)->sz);
	ft_putendl("\n--------------------");
	return (1);
}

int		_fork(t_token **op, char **sp)
{
	ft_putendl("fork");
	return (1);
}

int		_lld(t_token **op, char **sp)
{
	ft_putendl("lld");
	return (1);
}

int		_lldi(t_token **op, char **sp)
{
	ft_putendl("lldi");
	return (1);
}

int		_lfork(t_token **op, char **sp)
{
	ft_putendl("fork");
	return (1);
}

int		_aff(t_token **op, char **sp)
{
	ft_putendl("aff");
	return (1);
}
