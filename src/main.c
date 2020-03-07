/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:03:32 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/07 17:09:56 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static void	init_env(t_ass_env *ass)
{
	ass->champ.prog_name = NULL;
	ass->champ.prog_cmnt = NULL;
	ass->tokens = NULL;
	ass->op = NULL;
	ass->sz = 0;
}

char		*renamefn(char *s)
{
	int i;
	char	*fn;

	i = 0;
	if (!(fn = ft_strnew(ft_strlen(s) + 2)))
		return (NULL);
	fn = ft_strncpy(fn, s, ft_strlen(s) - 2);
	while (s[i] && s[i] != '.')
	{
		fn[i] = s[i];
		i++;
	}
	fn[i++] = '.';
	fn[i++] = 'c';
	fn[i++] = 'o';
	fn[i] = 'r';
	return (fn);
}

void	find_prevs(t_token **token)
{
	t_token *ttoken;
	t_token *current;

	ttoken = *token;
	current = NULL;
	while (ttoken)
	{
		ttoken->prev = current;
		current = ttoken;
		ttoken = ttoken->next;
	}
}

int			main(int ac, char **av)
{
	t_ass_env	ass;
	int i;
	
	init_env(&ass);
	if (ac > 1 && !assembler(av[1], &ass))
	{
		ft_printf("oh no");
		return (0);
	}
	// ft_printf("name : |%s|\n", ass.champ.prog_name);
	// ft_printf("desc : |%s|\n", ass.champ.prog_cmnt);

	t_token *ttoken;
	ttoken = ass.tokens;
	ass.sz = 0;
	ft_printf("\n%d", ass.sz);
	i = 0;
	ft_putendl("");
	find_prevs(&(ass.tokens));
	while (ttoken)
	{
		ft_printf("%d\t %d %s ", i, ttoken->type, ttoken->name);
		if (ttoken->type == 4)
			ft_printf("%#0x", ttoken->code);
		if (ttoken->prev)
			ft_printf("\t++ prev %s ", ttoken->prev->name);
		ft_putendl("");
		ttoken = ttoken->next;
		i++;
	}
	print_content(ass.tokens, av[1], &ass.sz);
	return (0);
}
