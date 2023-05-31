/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:23:39 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/31 13:31:03 by emlamoth         ###   ########.fr       */
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

typedef struct s_ltkn
{
	char			*token;
	struct s_ltkn	*next;
}				t_ltkn;

typedef struct s_lcmd
{
	char			*cmdpath;
	char			**argv;
	int				builtin;
	struct s_lcmd	*next;
}				t_lcmd;

typedef struct s_data
{
	//---emman-----
	int		oldfdr;
	int		back_pipe;
	int		front_pipe;
	//---frank-----
	char 	*read;
	char 	*line;
	int		rdflag;
	int		i;
	int		j;
	int		dquote;
	int		squote;
	//---common-----
	char	**path;
	char	**envp;
	t_lcmd	*lcmd;
	t_ltkn 	*ltkn;

	
}				t_data;

void	mini_execute(t_data *data);
void	mini_start(t_data *data);
void	mini_exit(t_data *data);
void	dquotes(t_data *data);
void	squotes(t_data *data);
void	prep_line(t_data *data);
void	in_quotes(t_data *data);

t_ltkn	*ft_lstlast_tkn(t_ltkn *ltkn);
t_ltkn	*ft_lstnew_tkn(char *content);
void	make_list(t_data *data);

#endif