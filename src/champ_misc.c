/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:51:41 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/05 12:28:41 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

int		get_champ_name(char *line, t_ass_env *ass)
{
	line = ft_strtrim(line);
	if (!line || line[0] != '"' || line[ft_strlen(line) - 1] != '"')
		return (0);
	line++;
	if (ft_strlen(line) - 1 > PROG_NAME_LENGTH)
		return (0);
	ass->champ.prog_name = ft_strsub(line, 0, ft_strlen(line) - 1);
	if (!add_token(ass, new_token(ass->champ.prog_name, 1)))
		return (0);
	return (1);
}

int		get_champ_cmnt(char *line, t_ass_env *ass)
{
	line = ft_strtrim(line);
	if (!line || line[0] != '"' || line[ft_strlen(line) - 1] != '"')
		return (0);
	line++;
	if (ft_strlen(line) - 1 > PROG_NAME_LENGTH)
		return (0);
	ass->champ.prog_cmnt = ft_strsub(line, 0, ft_strlen(line) - 1);
	if (!add_token(ass, new_token(ass->champ.prog_cmnt, 2)))
		return (0);
	return (1);
}

int		is_label_char(char c)
{
	int i;

	i = -1;
	while (LABEL_CHARS[++i])
		if (LABEL_CHARS[i] == c)
			return (1);
	return (0);
}

int		get_label(char *line, t_ass_env *ass, int l)
{
	// ft_printf("%s:\n", ft_strsub(line, 0, l));
	if (!add_token(ass, new_token(ft_strsub(line, 0, l), 3)))
		return (0);
	return (1);
}

