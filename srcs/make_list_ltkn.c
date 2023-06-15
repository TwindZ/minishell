/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_ltkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:39 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/15 16:40:11 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_meta(char **arg, t_data *data)
{
	t_ltkn *temp;

	temp = data->ltkn;
	temp = ft_lstlast_tkn(temp);
	if(!ft_strncmp(arg[data->i], ">\0", 2))
	{
		free(arg[data->i]);
		temp->out_mod = 1;
		temp->outfile = arg[++data->i];
		return(1);
	}
	else if (!ft_strncmp(arg[data->i], ">>", 2))
	{
		free(arg[data->i]);
		temp->out_mod = 2;
		temp->outfile = arg[++data->i];
		return(1);
	}
	else if (!ft_strncmp(arg[data->i], "<\0", 2))
	{
		free(arg[data->i]);
		temp->in_mod = 1;
		temp->infile = arg[++data->i];
		return(1);
	}
	else if (!ft_strncmp(arg[data->i], "<<", 2))
	{
		free(arg[data->i]);
		temp->in_mod = 2;
		data->hd.end = arg[++data->i];
		data->exe_flag.heredoc_in = 1;
		return(1);
	}
	else
		return(0);
}

// void	set_meta(t_data *data)
// {
// 	if(data->exe_flag.file_in)
// 		open_infile(data);
// 	else if(data->exe_flag.file_out_a || data->exe_flag.file_out_w)
// 		open_outfile(data);
// 	else if(data->exe_flag.heredoc_in)
// 		heredoc(data);
// }

void build_cmd_param(t_data *data, char **arg)
{
	t_ltkn *temp;

	temp = data->ltkn;
	temp = ft_lstlast_tkn(temp);
	if(strncmp(arg[data->i], "|\0", 1) == 0)
	{
		temp->front_pipe = 1;
		return ;// ft_pipe(data);
	}	
	else if(is_meta(arg, data))
		return ;	
	else
	{
		temp->arg[data->j++] = arg[data->i];
	}
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
	char	**arg;
	t_ltkn	*temp;
	t_ltkn	*new;
	int nbarg;
	nbarg = 0;
	temp = NULL;
	new = NULL;
	data->ltkn = new;
	data->i = 0;
	arg = NULL;
	arg = ft_split(data->line, '\t');
	//TODO if (!arg)
	while (arg[data->i])
	{
		if(data->i == 0 || (data->i > 0 && strncmp(arg[data->i - 1], "|", 1) == 0))
		{
			if(!data->ltkn)
			{	
				data->j = 0;
				nbarg = ft_count_arg(arg, data->i);
				data->ltkn = ft_lstnew_tkn(arg[data->i], nbarg, data->j);
				data->j++;
				check_path(data, arg, data->ltkn);
			}			
			else
			{
				free(arg[data->i - 1]);
				data->j = 0;
				nbarg = ft_count_arg(arg, data->i);
				temp = data->ltkn;
				temp = ft_lstlast_tkn(temp);
				temp->next = ft_lstnew_tkn(arg[data->i], nbarg, data->j);
				data->j++;
				check_path(data, arg, temp->next);
			}
		}
		else
			build_cmd_param(data, arg);
		data->i++;
	}
	free(arg);
	//TODO a optimiser if/else + cur_ltkn;
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
	int i;

	temp = data->ltkn;
	while (temp != NULL)
	{
		i = 0;
		ft_printf("\npath : %s\n", temp->path);
		ft_printf("argv : ");
		while(temp->arg[i])
			ft_printf("%s, ", temp->arg[i++]);
		ft_printf("\n");
		ft_printf("infile : %s\n", temp->infile);
		ft_printf("outfile : %s\n", temp->outfile);
		ft_printf("frontpipe : %i\n\n", temp->front_pipe);
		
		
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
