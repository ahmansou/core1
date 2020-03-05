/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:03:32 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/05 16:23:48 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ass.h"

static void	init_env(t_ass_env *ass)
{
	ass->champ.prog_name = NULL;
	ass->champ.prog_cmnt = NULL;
	ass->tokens = NULL;
	ass->op = NULL;
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

void		print_magic_header(int fd, int *j)
{
	int added;
	char *s;
	int i;

	s = itoa_base(COREWAR_EXEC_MAGIC, 16);
	added = 8 - ft_strlen(s);
	i = -1;
	while (++i < added)
	{
		ft_putstr_fd("0", fd);
		if (((*j) + 1) % 4 == 0)
			ft_putchar_fd(' ', fd);
		(*j)++;
	}
	i = -1;
	while (s[++i])
	{
		ft_putchar_fd(s[i], fd);
		if (((*j) + 1) % 4 == 0)
			ft_putchar_fd(' ', fd);
		(*j)++;
	}
	(*j) /= 2;
	ft_strdel(&s);
}

void		print_name_comnt(int fd, char *name, int *j, int max)
{
	int i;
	int k;
	
	i = -1;
	while (name[++i])
	{
		ft_putstr_fd(itoa_base(name[i], 16), fd);
		if (((*j) + 1) % 2 == 0)
			ft_putchar_fd(' ', fd);
		if (((*j) + 1) % 16 == 0)
			ft_putchar_fd('\n', fd);
		(*j)++;
	}
	i--;
	while (++i < max)
	{
		ft_putstr_fd("00", fd);
		if (((*j) + 1) % 2 == 0)
			ft_putchar_fd(' ', fd);
		if (((*j) + 1) % 16 == 0)
			ft_putchar_fd('\n', fd);
		(*j) ++;
	}
}

void		print_hex(t_token *ttoken, char *fn)
{
	int j;
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
	j = 0;
	print_magic_header(fd, &j);
	while (tk)
	{
		if (tk->type == 1)
			print_name_comnt(fd, tk->name, &j, PROG_NAME_LENGTH);
		if (tk->type == 2)
		{
			// ft_putstr_fd("0000 0000 ", fd);
			ft_putstr_fd("nnnn nnnn ", fd);
			ft_putstr_fd("xxxx xxxx ", fd); //print exec code size
			j += 4;
			j += 4;
			print_name_comnt(fd, tk->name, &j, COMMENT_LENGTH);
			ft_putstr_fd("nnnn nnnn ", fd);
			j += 4;
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
	print_hex(ttoken, av[1]);
	i = 0;
	while (ttoken)
	{
		ft_printf("%d\t%s %d ", i, ttoken->name, ttoken->type);
		ft_putendl("");
		ttoken = ttoken->next;
		i++;
	}
	return (0);
}
