/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:03:32 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/06 14:03:40 by ahmansou         ###   ########.fr       */
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

void		print_content(t_token *ttoken, char *fn, int *sz)
{
	int fd;
	char	*nfn;
	t_token	*tk;
	
	tk = ttoken;
	nfn = renamefn(fn);
	if ((fd = open(nfn, O_RDWR | O_CREAT, 0644)) < 0)
	{
		ft_printf("no can do");
		return ;
	}
	ft_printf("Creating the file %s\n", nfn);
	print_magic_header(fd,sz);
	while (tk)
	{
		if (tk->type == 1)
			print_name_comnt(fd, tk->name, PROG_NAME_LENGTH, sz);
		if (tk->type == 2)
		{
			print_null(fd, sz);
			print_exec_code_size(fd, sz);
			print_name_comnt(fd, tk->name, COMMENT_LENGTH, sz);
			print_null(fd, sz);
		}
		tk = tk->next;
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
	print_content(ttoken, av[1], &ass.sz);
	ft_printf("\n%d", ass.sz);
	i = 0;
	ft_putendl("");
	while (ttoken)
	{
		ft_printf("%d\t%s %d ", i, ttoken->name, ttoken->type);
		ft_putendl("");
		ttoken = ttoken->next;
		i++;
	}
	return (0);
}
