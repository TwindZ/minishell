/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/29 15:12:51 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	freenull(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_list_ltkn(t_ltkn *ltkn)
{
	t_ltkn	*temp;

	temp = NULL;
	while (ltkn)
	{
		temp = ltkn->next;
		ltkn->arg = ft_freeall(ltkn->arg);
		if (ltkn->infile)
			freenull(ltkn->infile);
		if (ltkn->outfile)
			freenull(ltkn->outfile);
		freenull(ltkn->arg);
		if (ltkn->path)
			freenull(ltkn->path);
		freenull (ltkn);
		ltkn = temp;
	}
}


void	mini_free(t_data *data)
{
	if(data->temp_infile)
		freenull(data->temp_infile);
	if(data->temp_outfile != NULL)
	{
		ft_printf("\nBATARD !!\n");
		freenull(data->temp_outfile);
	}
	if(data->file)
		freenull(data->file);
	if(data->read)
		freenull(data->read);
	if(data->readhd)
		freenull(data->readhd);
	if(data->line)
		freenull(data->line);
	if(data->linetemp)
		freenull(data->linetemp);
	if(data->dolsign.tocheck)
		freenull(data->dolsign.tocheck);
	if(data->dolsign.towrite)
		freenull(data->dolsign.towrite);
	if(data->dshd.tocheck)
		freenull(data->dshd.tocheck);
	if(data->dshd.towrite)
		freenull(data->dshd.towrite);
	if(data->meta.temp)
		freenull(data->meta.temp);
	if(data->exp.swap)
		freenull(data->exp.swap);
	if(data->hd.data)
		freenull(data->hd.data);
	if(data->hd.end)
		freenull(data->hd.end);
}
