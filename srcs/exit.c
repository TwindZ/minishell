/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/01 11:15:26 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_free(t_data *data)
{
	// if (data->rdflag == 1)
	// free(data->read);
	data->rdflag = 0;
	free_ltkn(data->ltkn);
	data->ltkn = NULL;
	// free(data);
}
