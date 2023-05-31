/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_lcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:50:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/05/31 15:45:31 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	make_list_lcmd(t_data *data, char *path)
{
		t_lcmd	*temp;
		
		temp = NULL;
		if(!data->lcmd)
			data->lcmd = ft_lstnew_lcmd(path);
		else
		{
			temp = data->lcmd;
			temp = ft_lstlast_lcmd(data->lcmd);
			temp->next = ft_lstnew_lcmd(path);
		}
}

t_lcmd	*ft_lstnew_lcmd(char *content)
{
	t_lcmd	*lcmd;

	lcmd = (t_lcmd *)malloc(sizeof(t_lcmd));
	if (!lcmd)
		return (NULL);
	lcmd->cmdpath = content;
	lcmd->next = NULL;
	return (lcmd);
}

t_lcmd	*ft_lstlast_lcmd(t_lcmd *lcmd)
{
	if (lcmd)
	{
		while (lcmd->next)
			lcmd = lcmd->next;
	}
	return (lcmd);
}

void	print_list_lcmd(t_data *data)
{
	t_lcmd	*temp;

	temp = NULL;
	temp = data->lcmd;
	while (temp != NULL)
	{
		ft_printf("%s\n", temp->cmdpath);
		temp = temp->next;
	}	
}

void	free_lcmd(t_lcmd *lcmd)
{
	t_lcmd	*temp;

	while (lcmd)
	{
		temp = lcmd->next;
		free(lcmd);
		lcmd = temp;
	}
	lcmd = NULL;
}