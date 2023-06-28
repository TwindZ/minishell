/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/28 14:26:27 by emlamoth         ###   ########.fr       */
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
		if (ltkn->infile)
			free(ltkn->infile);
		if (ltkn->outfile)
			free (ltkn->outfile);
		free (ltkn->arg);
		if (ltkn->path)
			free (ltkn->path);
		free (ltkn);
		ltkn = NULL;
		ltkn = temp;
	}
}

void	mini_free(t_data *data)
{
	(void) data;
	// if (data->rdflag == 1)
	// {
		// free(data->read);
		// free (data->line);
	// }
	// data->rdflag = 0;
	// data->ltkn = NULL;
	// free_list_ltkn(data->ltkn);
	// free(data);
	//------------------------------------
	// if(data->envp)
	// 	free(data->envp);
	// if(data->envp)
	// 	free(data->envp);
}
// TODO ça prend un focntion de sortie universelle