/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:58:18 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/29 14:20:21 by emlamoth         ###   ########.fr       */
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

void	freenull(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	mini_free(t_data *data)
{
	if(data->temp_infile)
		freenull(data->temp_infile);
	if(data->temp_outfile)
		freenull(data->temp_outfile);
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
	if(data->ltkn->path)
		freenull(data->ltkn->path);
	if(data->ltkn->infile)
		freenull(data->ltkn->infile);
	if(data->ltkn->outfile)
		freenull(data->ltkn->outfile);
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
	if(data->env.result)
		freenull(data->env.result);
	if(data->exp.swap)
		freenull(data->exp.swap);
	if(data->hd.data)
		freenull(data->hd.data);
	if(data->hd.end)
		freenull(data->hd.end);
}
