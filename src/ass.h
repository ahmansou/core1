/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ass.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:03:28 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/08 11:44:11 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASS_H
# define ASS_H

# define BUFF_SIZE 1
# define FD_LIMIT 4864

# include "../libft/libft.h"
# include "../ft_printf/src/ft_printf.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef	struct		s_lines
{
	char			*line;
	struct s_lines	*next;
}					t_lines;

typedef struct		s_op
{	
	char			*name;
	char			binary;
	char			arg[3];
	int				code;
	int				cycle;
	char			*desc;
	char			carry;
	char			octcode;
	int				tdir_sz;
}					t_op;

typedef struct 		s_token
{
	int				type;
	char			*name;
	int				args[3];
	char			argc[3];
	int				code;
	int				tdir_sz;
	int				is_encode;
	int				encode;
	int				sz;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct		s_ch
{
	char			*prog_name;
	char			*prog_cmnt;
}					t_ch;

typedef struct		s_ass_env
{
	struct s_op		*op;
	t_lines			*lines;
	t_token			*tokens;
	int				sz;
	int				exec_code_sz;
	struct s_ch		champ;
}					t_ass_env;

typedef struct		s_op_types
{
	int 			opss[16];
	int				(*t[16])(t_token **op, char **sp);
}					t_op_types;

t_op_types			get_o_types(void);
int					_live(t_token **op, char **sp);
int					_ld(t_token **op, char **sp);
int					_st(t_token **op, char **sp);
int					_add(t_token **op, char **sp);
int					_sub(t_token **op, char **sp);
int					_and(t_token **op, char **sp);
int					_or(t_token **op, char **sp);
int					_xor(t_token **op, char **sp);
int					_zjmp(t_token **op, char **sp);
int					_ldi(t_token **op, char **sp);
int					_sti(t_token **op, char **sp);
int					_fork(t_token **op, char **sp);
int					_lld(t_token **op, char **sp);
int					_lldi(t_token **op, char **sp);
int					_lfork(t_token **op, char **sp);
int					_aff(t_token **op, char **sp);

int					assembler(char *fn, t_ass_env *ass);
int 				get_lines(char *filename, t_ass_env *env);
char				**ft_split_whitespaces(char *str);
int					skip_ws(char *line);
int					is_label(char *s);
int					get_champ_name(char *line, t_ass_env *ass);
int					get_champ_cmnt(char *line, t_ass_env *ass);
int					is_label_char(char c);
int					get_label(char *line, t_ass_env *ass, int l);
int					add_token(t_ass_env *ass, t_token *new);
t_token				*new_token(char *line, int type);
int					is_op(char *line);
const t_op			*get_op_tab(void);
int					get_op(char *line, t_ass_env *ass);
void				free2d(char ***s);
int					ft_atoi_base(char *nb, int base);

void				print_magic_header(int fd, int *sz);
void				print_name_comnt(int fd, char *name, int max, int *sz);
void				print_null(int fd, int *sz);
void				print_exec_code_size(int fd, int *sz);
void				print_content(t_token *ttoken, char *fn, int *sz);
void				print_exec_code(int fd, t_token *tk, int *sz);

int					count_int(int n);
char		*renamefn(char *s);

void	print_live(t_token *token, int fd, int *sz);
void	print_ld(t_token *token, int fd, int *sz);
void	print_add_sub(t_token *token, int fd, int *sz);
void	print_sti(t_token *token, int fd, int *sz);
void	print_and_xor(t_token *token, int fd, int *sz);

int				is_num(char *s);

int		calc_encode(char *arg1, char *arg2, char *arg3);
int		calc_sz(char *argc, int dirsz);
void	get_argc_types(t_token **op, char **sp);

#endif
