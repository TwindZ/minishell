/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:23:39 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/17 18:29:15 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

typedef struct s_lst
{
	char			*cmd;
	struct s_cmd	*next;
}				t_lst;

typedef struct s_data
{
	t_lst	cmd;
}				t_data;

#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libc.h>
#include "libft/libft.h"

#endif