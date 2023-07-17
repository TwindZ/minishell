/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/17 09:33:29 by emlamoth         ###   ########.fr       */
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
		free(ltkn);
		ltkn = temp;
	}
}
