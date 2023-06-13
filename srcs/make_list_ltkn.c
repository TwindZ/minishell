/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_ltkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:39 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/13 07:08:21 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_meta(char *arg)
{
	if(ft_strncmp(arg, ">", 1) 
		|| ft_strncmp(arg, ">>", 2) 
		|| ft_strncmp(arg, "<", 1) 
		|| ft_strncmp(arg, "<<", 2))
		return(1);
	return(0);
	// peut etre return multiple
}

void build_cmd_param()
{
	
}

int ft_count_arg(char **arg, int i)
{
	int j;
	
	j = 0;
	while((ft_strncmp(arg[i], "|", 1)) && arg[i++])
		j++;
	return (j);
	ft_printf("%d\n", j);
}

void	make_list_ltkn(t_data *data)
{
	char 	**arg;
	t_ltkn	*temp;
	int nbarg;
	int arg_index;
	
	nbarg = 0;
	temp = NULL;
	data->i = 0;
	arg = NULL;
	arg = ft_split(data->line, '\t');
	// if (!arg)
	while (arg[data->i])
	{
		if(data->i == 0 || strncmp(arg[data->i - 1], "|", 1) == 0)
		{
			if(!data->ltkn)
			{	
				nbarg = ft_count_arg(arg, data->i);
				ft_printf("nbarg : %d\n", nbarg);
				data->ltkn = ft_lstnew_tkn(arg[data->i], nbarg, 0);
			}			
			else
			{
			ft_printf(" arg : %s\n", arg[data->i]);
				nbarg = ft_count_arg(arg, data->i);
				temp = data->ltkn;
				temp = ft_lstlast_tkn(data->ltkn);
				temp->next = ft_lstnew_tkn(arg[data->i], nbarg, 0);
			}
		}
		if(is_meta(arg[data->i]))
		{
			// do something to resolve io
		}	
		else
		{
			// do somthing to add next argv
		}
		data->i++;
	}
}


t_ltkn	*ft_lstnew_tkn(char *content, int nbarg, int index)
{
	t_ltkn	*ltkn;

	ltkn = ft_calloc(1, sizeof(t_ltkn));
	ltkn->arg = ft_calloc(nbarg + 1, sizeof(char *));
	if (!ltkn)
		return (NULL);
	ltkn->arg[index] = content;
	ltkn->next = NULL;
	return (ltkn);
}

t_ltkn	*ft_lstlast_tkn(t_ltkn *ltkn)
{
	if (ltkn)
	{
		while (ltkn->next)
			ltkn = ltkn->next;
	}
	return (ltkn);
}

void	print_list(t_data *data)
{
	t_ltkn	*temp;

	temp = data->ltkn;
	while (temp != NULL)
	{
		ft_printf("%s\n", temp->arg[0]);
		temp = temp->next;
	}	
}

void	free_ltkn(t_ltkn *ltkn)
{
	t_ltkn	*temp;

	while (ltkn)
	{
		temp = ltkn->next;
		free(ltkn);
		ltkn = temp;
	}
	ltkn = NULL;
}
