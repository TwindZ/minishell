/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:23:39 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/29 15:06:21 by fbouchar         ###   ########.fr       */
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
# include <stdio.h>
# include <signal.h>

typedef struct s_ltkn
{
	
	char			*path;
	char			**arg;
	char			*infile;
	int				in_mod;
	char			*outfile;
	int				out_mod;
	int 			front_pipe;
	struct s_ltkn	*next;
}				t_ltkn;

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

typedef struct s_env
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*result;
}				t_env;

typedef struct s_exp
{
	int		i;
	int		j;
	int		k;
	char	**new_env;
	char	**temp_env;
	char	*swap;
}				t_exp;

typedef struct s_heredoc
{
	char	*end;
	char	*data;
	int		i;
}				t_heredoc;

typedef struct s_fd
{
	int		cmd_in;
	int		cmd_out;
	int		cmd_next_in;
}				t_fd;

typedef struct s_exe_flag
{
	int		file_in;
	int		file_out;
	int		back_pipe;
	int		front_pipe;
	int		heredoc_in;
}				t_exe_flag;

typedef struct s_data
{
	t_fd		fd;
	t_exe_flag	exe_flag;
	t_heredoc	hd;
	t_ltkn 		*ltkn;
	char		*temp_infile;
	int			temp_in_mod;
	char		*temp_outfile;
	int			temp_out_mod;
	char		*file;
	char		**envp;
	char		*read;
	char		*readhd;
	char		*line;
	char		*linetemp;
	int			rdflag;
	int			flag;
	int			i;
	int			j;
	t_quotes	quotes;
	t_dolsign	dolsign;
	t_dshd		dshd;
	t_meta		meta;
	t_env		env;
	t_exp		exp;
	int			child;
}				t_data;

void	mini_execute(t_data *data);
void	arg_list(t_data *data);
void 	open_infile(t_data *data, char *file);
void 	open_outfile(t_data *data, char *file, int mod);
void	heredoc(t_data *data, char *delimiter);
void	free_list_ltkn(t_ltkn *ltkn);
void 	ft_pipe(t_data *data);
void	set_meta(t_data *data, char **arg);
int		is_meta(t_data *data, char **arg);
void	build_cmd_param(t_data *data, char **arg, t_ltkn *temp);

void	sig_handler(int sig, siginfo_t *info, void *ucontext);

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

t_ltkn	*ft_lstnew_tkn(char *content, int nbarg, int index);
void	make_list_ltkn(t_data *data);
void	print_list(t_data *data);
void	free_ltkn(t_ltkn *ltkn);

void	check_path(t_data *data, char **arg, t_ltkn *temp);

void	mini_echo(int fd, t_ltkn *temp, t_data *data);
void	echo_print(int fd, t_ltkn *temp, t_data *data);
void	mini_pwd(int fd);
void	mini_exit(t_data *data, t_ltkn *temp);
void	mini_cd(t_data *data, t_ltkn *temp);
void	change_dir(t_data *data, t_ltkn *temp, char *home);
void	mini_unset(t_data *data, t_ltkn *temp);
char	**env_cpy(char **envp, int exp, t_data *data);

void	mini_env(t_data *data);
char	*getenvp(t_data *data, char *var, int extract);
void	init_env(t_data *data);
void	find_var(t_data *data);

void	mini_export(int fd, t_data *data, t_ltkn *temp);
void	init_export(t_data *data);
void	add_to_env(t_data *data, t_ltkn *temp);
void	print_env(int fd, t_data *data);
void	build_env(t_data *data, char **envp);
void 	add_var(t_data *data, char **envp, t_ltkn *temp);

void	mini_reset(t_data *data);
t_data	*ft_init_data(char **envp);
void	main_core(char **envp);
void	*ft_safe_calloc(size_t count, size_t size, t_data *data);
void	freenull(void *ptr);
#endif