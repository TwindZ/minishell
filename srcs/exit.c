/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/29 13:42:50 by fbouchar         ###   ########.fr       */
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

// TODO ça prend un focntion de sortie universelle