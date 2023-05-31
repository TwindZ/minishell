/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:39 by fbouchar          #+#    #+#             */
/*   Updated: 2023/05/31 13:32:25 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_list(t_data *data)
{
	char 	**arg;
	t_ltkn	*temp;

	data->i = 0;
	arg = NULL;
	arg = ft_split(data->line, '\t');
	if (!arg)
		mini_exit(data);
	while (arg[data->i])
	{
		if(!data->ltkn)
			data->ltkn = ft_lstlast_tkn(data->ltkn);
		// ft_printf("%s\n", arg[data->i]);
		else
		{
			temp = data->ltkn;
			temp = ft_lstlast_tkn(data->ltkn);
			temp->next = ft_lstnew_tkn(arg[data->i]);
		}
		data->i++;
	}
}

t_ltkn	*ft_lstnew_tkn(char *content)
{
	t_ltkn	*ltkn;

	ltkn = (t_ltkn *)malloc(sizeof(t_ltkn));
	if (!ltkn)
		return (NULL);
	ltkn->token = content;
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
