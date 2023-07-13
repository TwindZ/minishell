/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/13 14:59:43 by emlamoth         ###   ########.fr       */
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
//TODO voir si c'est ok avec le free
// void	mini_free(t_data *data)
// {
// 	if(data->temp_infile)
// 		freenull(data->temp_infile);
// 	if(data->temp_outfile != NULL)
// 	{
// 		freenull(data->temp_outfile);
// 	}
// 	if(data->file)
// 		freenull(data->file);
// 	if(data->read)
// 		freenull(data->read);
// 	if(data->readhd)
// 		freenull(data->readhd);
// 	if(data->line)
// 		freenull(data->line);
// 	if(data->meta.temp)
// 		freenull(data->meta.temp);
// 	if(data->hd.data)
// 		freenull(data->hd.data);
// 	if(data->hd.end)
// 		freenull(data->hd.end);
// 	ft_printf("\nBATARD !!\n");
// }
