/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:23:39 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/29 15:39:03 by fbouchar         ###   ########.fr       */
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
#include "libft/libft.h"

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
	t_ltkn 	*ltkn;
	t_lcmd	*lcmd;
	char	**path;
	char	**envp;
	int		oldfdw;
	int		oldfdr;
	int		newfdw;
	int		newfdr;
	char 	*read;
	char 	*line;
	int		rdflag;
	int		dquote;
	int		squote;
	int		pfdw;
	int		pfdr;
	
}				t_data;

void	mini_execute(t_data *data);
void	mini_start(t_data *data);
void	mini_exit(t_data *data);
void	dquotes(t_data *data);
void	squotes(t_data *data);
void	prep_line(t_data *data);

#endif