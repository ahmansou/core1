/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ass.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 09:03:28 by ahmansou          #+#    #+#             */
/*   Updated: 2020/03/05 12:04:38 by ahmansou         ###   ########.fr       */
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
}					t_op;

typedef struct 		s_token
{
	int				type;
	char			*name;
	char			**args;
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
	struct s_ch		champ;
}					t_ass_env;

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

#endif
