/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/14 16:23:19 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list_ltkn(t_ltkn *ltkn)
{
	t_ltkn	*temp;
	
	temp = NULL;
	while (ltkn)
	{
		temp = ltkn->next;
		ltkn->arg = ft_freeall(ltkn->arg);
		free(ltkn->path);
		ltkn = temp;
	}
	ltkn = NULL;
}

void	mini_free(t_data *data)
{
	if (data->rdflag == 1)
	{
		// free(data->read);
		// free (data->line);
	}
	// data->rdflag = 0;
	// free_ltkn(data->ltkn);
	// data->ltkn = NULL;
	// free(data);
}
