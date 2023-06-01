/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:23:39 by emlamoth          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/01 14:04:52 by fbouchar         ###   ########.fr       */
=======
/*   Updated: 2023/06/01 12:52:56 by emlamoth         ###   ########.fr       */
>>>>>>> emman
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libc.h>
#include "../srcs/libft/libft.h"

typedef struct	s_ltkn
{
	char			*token;
	struct s_ltkn	*next;
}				t_ltkn;

typedef struct	s_lcmd
{
	char			*cmdpath;
	char			**argv;
	int				builtin;
	struct s_lcmd	*next;
}				t_lcmd;

typedef struct	s_quotes
{
	int	idx;
	int	spotdbl;
	int	spotsgl;
	int	dbl;
	int	sgl;
	int	dblflag;
	int	sglflag;
}				t_quotes;

typedef struct	s_dolsign
{
	int		start;
	int		end;
	int		len;
	int		idx;
	char	*tocheck;
	char	*towrite;
}				t_dolsign;

typedef struct	s_data
{
	//---emman-----
	int			oldfdr;
	int			back_pipe;
	int			front_pipe;
}				t_data;

typedef struct s_fd
{
	int	cmd_in;
	int cmd_out;
	int cmd_next_in;
}				t_fd;

typedef struct s_exe_flag
{

	int 	file_in;
	int		file_out_w;
	int		file_out_a;
	int		back_pipe;
	int		front_pipe;
}				t_exe_flag;

typedef struct	s_data
{
	//---emman-----
	t_fd		fd;
	t_exe_flag	exe_flag;

	//---frank-----
	char 		*read;
	char 		*line;
	int			rdflag;
	int			i;
	int			j;
	t_quotes	quotes;
	t_dolsign	dolsign;
	//---common-----
	char		**path;
	// char	*cmdpath;
	char		**envp;
	t_lcmd		*lcmd;
	t_ltkn 		*ltkn;

	
}				t_data;

void	mini_execute(t_data *data);
void	mini_start(t_data *data);
void	mini_free(t_data *data);
int		whitespace(t_data *data);
int		fuckin_quotes(t_data *data);
void	init_quotes(t_data *data);
void	double_quotes(t_data *data);
void	single_quotes(t_data *data);
void	quotes_priority(t_data *data);
void	prep_line(t_data *data);
void	in_quotes(t_data *data);
void	dollar_sign(t_data *data);
void	init_dollar(t_data *data);
void	make_tocheck(t_data *data);

t_ltkn	*ft_lstlast_tkn(t_ltkn *ltkn);
t_ltkn	*ft_lstnew_tkn(char *content);
void	make_list(t_data *data);
void	print_list(t_data *data);
void	free_ltkn(t_ltkn *ltkn);

void	make_list_lcmd(t_data *data, char *path);
t_lcmd	*ft_lstnew_lcmd(char *content);
t_lcmd	*ft_lstlast_lcmd(t_lcmd *lcmd);
void	print_list_lcmd(t_data *data);
void	free_lcmd(t_lcmd *lcmd);

void	check_path(t_data *data);
#endif