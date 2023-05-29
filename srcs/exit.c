/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/05/29 13:01:23 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_data *data)
{
	if (data->rdflag == 1)
		free(data->read);
	free(data);
	exit(EXIT_FAILURE);
}