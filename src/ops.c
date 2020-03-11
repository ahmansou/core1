/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:51:00 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/11 20:15:19 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static int	return_err(char ***split, int ret)
{
	free2d(split);
	return (ret);
}

void		init_labels(t_token **token)
{
	(*token)->labels[0] = NULL;
	(*token)->labels[1] = NULL;
	(*token)->labels[2] = NULL;
}

t_token		*new_op_token(char **split, t_ass_env *ass)
{
	const t_op	*ops;
	t_token		*new;
	int			i;
	t_op_types	o_tps;
	
	o_tps = get_o_types();
	ops = get_op_tab();
	i = -1;
	if (!split || !(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	while (++i < 16)
	{
		if (!split[0])
			return (NULL);
		if (!ft_strcmp(split[0], ops[i].name))
		{
			new->type = 4;
			new->name = strdup(split[0]);
			new->code = ops[i].code;
			new->tdir_sz = ops[i].tdir_sz;
			// ft_printf("%s\n", new->name);
			init_labels(&new);
			if (new->code >= 1 && new->code <= 16)
				if (!o_tps.t[new->code - 1](&new, split))
					return (NULL);
			return (new);
		}
	}
	free2d(&split);
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
