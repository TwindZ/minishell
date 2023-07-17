/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/17 17:39:31 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list_ltkn(t_ltkn *ltkn)
{
	t_ltkn	*temp;

	temp = NULL;
	while (ltkn != NULL)
	{
		temp = ltkn->next;
		ltkn->arg = ft_freeall(ltkn->arg);
		free(ltkn->arg);
		if (ltkn->path)
			free(ltkn->path);
		if(ltkn->infile)
			free(ltkn->infile);
		if(ltkn->outfile)
			free(ltkn->outfile);
		free(ltkn);
		ltkn = temp;
	}
}

void	free_reset(t_data *data)
{
	if (data->ltkn)
		free_list_ltkn(data->ltkn);
	data->ltkn = NULL;
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->read)
		free(data->read);
	data->read = NULL;
}
