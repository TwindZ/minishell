/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:23:39 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/15 14:19:47 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libc.h>
# include "../srcs/libft/libft.h"
# include <stdarg.h>

typedef struct s_ltkn
{
	char			**arg;
	int				in;
	int				out;
	struct s_ltkn	*next;
}				t_ltkn;

typedef struct s_lcmd
{
	char			*cmdpath;
	char			**argv;
	int				builtin;
	struct s_lcmd	*next;
}				t_lcmd;

typedef struct s_quotes
{
	int	idx;
	int	spotdbl;
	int	spotsgl;
	int	dbl;
	int	sgl;
	int	dblflag;
	int	sglflag;
}				t_quotes;

typedef struct s_dolsign
{
	int		start;
	int		end;
	int		len;
	int		idx;
	int		towritelen;
	int		linelen;
	int		i;
	char	*tocheck;
	char	*towrite;
}				t_dolsign;

typedef struct s_dshd
{
	int		start;
	int		start2;
	int		end;
	int		len;
	int		idx;
	int		towritelen;
	int		linelen;
	int		i;
	int		j;
	char	*tocheck;
	char	*towrite;
}				t_dshd;

typedef struct s_meta
{
	int		spaces;
	int		len;
	int		i;
	char	*temp;
}				t_meta;

typedef struct s_heredoc
{
	char	*end;
	char	*data;
	int		i;
}				t_heredoc;

typedef struct s_exe_cmd
{
	char			**meta;
	char			**cmdpath;
	char			***argv;
}				t_exe_cmd;

typedef struct s_fd
{
	int		cmd_in;
	int		cmd_out;
	int		cmd_next_in;
}				t_fd;

typedef struct s_exe_flag
{
	int		file_in;
	int		file_out_w;
	int		file_out_a;
	int		back_pipe;
	int		front_pipe;
}				t_exe_flag;

typedef struct s_data
{
	//---emman-----
	t_fd		fd;
	t_exe_flag	exe_flag;
	t_exe_cmd	exe_cmd;
	t_heredoc	hd;
	t_ltkn 		*ltkn;
	char		*file;
	//---frank-----
	char		*read;
	char		*readhd;
	char		*line;
	char		*linetemp;
	int			rdflag;
	int			i;
	int			j;
	t_quotes	quotes;
	t_dolsign	dolsign;
	t_dshd		dshd;
	t_meta		meta;
	//---common----- 
	//TODO enlever les commentaires
	char		**path;
	// char	*cmdpath;
	char		**envp;
	t_lcmd		*lcmd;
}				t_data;

void	mini_execute(t_data *data);
void	arg_list(t_data *data);

void	mini_start(t_data *data);
void	mini_free(t_data *data);
int		whitespace(t_data *data);
void	prep_line(t_data *data);
void	in_quotes(t_data *data);
void	transform_spaces(t_data *data);
void	write_chars(t_data *data);
void	replace_meta(t_data *data);
void	meta_replace(t_data *data);

int		fuckin_quotes(t_data *data);
void	init_quotes(t_data *data);
void	double_quotes(t_data *data);
void	single_quotes(t_data *data);
void	quotes_priority(t_data *data);

void	dollar_sign(t_data *data);
void	init_dollar(t_data *data);
void	make_tocheck(t_data *data);
void	adjust_line(t_data *data);
void	init_adjust(t_data *data);

void	dollar_sign_hd(t_data *data);
void	init_dollar_hd(t_data *data);
void	make_tocheck_hd(t_data *data);
void	adjust_line_hd(t_data *data);
void	init_adjust_hd(t_data *data);

void	meta_chars(t_data *data, char meta);
void	init_meta(t_data *data);
void	make_temp(t_data *data);
void	remake_line(t_data *data, char meta);
void	place_tab(t_data *data, char meta);

t_ltkn	*ft_lstlast_tkn(t_ltkn *ltkn);
t_ltkn	*ft_lstnew_tkn(char *content, int nbarg, int index);
void	make_list_ltkn(t_data *data);
void	print_list(t_data *data);
void	free_ltkn(t_ltkn *ltkn);

void	make_list_lcmd(t_data *data, char *path);
t_lcmd	*ft_lstnew_lcmd(char *content);
t_lcmd	*ft_lstlast_lcmd(t_lcmd *lcmd);
void	print_list_lcmd(t_data *data);
void	free_lcmd(t_lcmd *lcmd);

void	check_path(t_data *data);

void	mini_echo(int fd, t_data *data);
void	mini_pwd(int fd);
#endif