/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 11:39:36 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/12 12:28:06 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

void	free_lines(t_lines **lines)
{
	t_lines *tmp;
	t_lines *tline;

	tmp = *lines;
	while (tmp)
	{
		tline = tmp->next;
		ft_strdel(&tmp->line);
		free(tmp);
		tmp = tline;
	}
}

void	free_token(t_token **token)
{
	t_token *tmp;
	t_token *ttoken;
	int		i;

	ttoken = *token;
	while (ttoken)
	{
		tmp = ttoken->next;
		i = 0;
		while (i < 3)
			ft_strdel(&ttoken->labels[i++]);
		ft_strdel(&ttoken->name);
		free(ttoken);
		ttoken = tmp;
	}
}

void	free_name_cmnt(t_ch *ch)
{
	ft_strdel(&(ch->prog_name));
	ft_strdel(&(ch->prog_cmnt));
}
