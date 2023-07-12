/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_ltkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:39 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/12 13:53:36 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_arg(char **arg, int i)
{
	int	j;

	j = 0;
	while ((ft_strncmp(arg[i], "|\0", 2)) && arg[i++])
		j++;
	return (j);
}

t_ltkn	*new_node(t_data *data, char **arg, t_ltkn *temp)
{
	int	nbarg;

	nbarg = 0;
	nbarg = ft_count_arg(arg, data->i);
	if (!data->ltkn)
	{
		temp = ft_lstnew_tkn(arg[data->i], nbarg, data->j);
		data->ltkn = temp;
	}
	else
	{
		temp->next = ft_lstnew_tkn(arg[data->i], nbarg, data->j);
		temp = temp->next;
	}
	check_path(data, arg, temp);
	data->j++;
	return (temp);
}

void	set_redirect(t_data *data, char **arg, t_ltkn *temp)
{
	if (temp && data->j > 0)
	{
		temp->in_mod = data->temp_in_mod;
		temp->out_mod = data->temp_out_mod;
		temp->infile = data->temp_infile;
		temp->outfile = data->temp_outfile;
	}
	if (temp && strncmp(arg[data->i], "|\0", 2) == 0)
	{
		data->temp_in_mod = 0;
		data->temp_out_mod = 0;
		data->temp_infile = NULL;
		data->temp_outfile = NULL;
		freenull(arg[data->i]);
	}
}

// TODO if (!arg)
void	make_list_ltkn(t_data *data)
{
	char	**arg;
	t_ltkn	*temp;

	temp = NULL;
	data->i = 0;
	data->j = 0;
	arg = NULL;
	arg = ft_split(data->line, '\t');
	while (arg[data->i])
	{
		if (data->j == 0 && is_meta(data, arg) == 0
			&& ft_strncmp(arg[data->i], "|\0", 2))
			temp = new_node(data, arg, temp);
		else
			build_cmd_param(data, arg, temp);
		if (arg[data->i] == NULL || data->temp_in_mod == -1 || data->syntax == -1)
			break ;
		if (temp)
			set_redirect(data, arg, temp);
		data->i++;
	}
	free(arg);
	arg = NULL;
}

t_ltkn	*ft_lstnew_tkn(char *content, int nbarg, int index)
{
	t_ltkn	*ltkn;

	ltkn = ft_calloc(1, sizeof(t_ltkn));
	if (!ltkn)
		return (NULL);
	ltkn->arg = ft_calloc(nbarg + 1, sizeof(char *));
	if (!ltkn)
		return (NULL);
	ltkn->arg[index] = content;
	ltkn->next = NULL;
	return (ltkn);
}
