/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:51:00 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/05 13:53:23 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static int	return_err(char ***split, int ret)
{
	free2d(split);
	return (ret);
}

t_token		*new_op_token(char **split, t_ass_env *ass)
{
	const t_op	*ops;
	t_token		*new;
	int			i;
	
	ops = get_op_tab();
	i = -1;
	if (!split || !(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	while (++i < 16)
		if (!ft_strcmp(split[0], ops[i].name))
		{
			// ft_printf("+%s\n", split[0]);
			new->type = 4;
			new->name = strdup(split[0]);
			return (new);
		}
	return (NULL);
}

int		get_op(char *line, t_ass_env *ass)
{
	char		**split;
	int			j;
	
	split = ft_split_whitespaces(line);
	j = 0;
	if (!split[0])
		return (return_err(&split, 0));
	if (is_label(split[0]) > 0)
	{
		j = 1;
		if (!split[j])
			return (return_err(&split, 0));
	}
	split = ft_split_whitespaces(line);
	if (!add_token(ass, new_op_token(split + j, ass)))
		return (0);
	return (1);
}

int		is_op(char *line)
{
	char		**split;
	const t_op	*ops;
	int			i;
	int			j;
	
	ops = get_op_tab();
	j = 0;
	split = ft_split_whitespaces(line);
	if (!split[0])
		return (return_err(&split, 0));
	if (is_label(split[0]) > 0)
	{
		j = 1;
		if (!split[j])
			return (return_err(&split, 0));
	}
	i = -1;
	while (++i < 16)
		if (!ft_strcmp(split[j], ops[i].name))
			return (return_err(&split, 1));
	return (return_err(&split, 0));
}
