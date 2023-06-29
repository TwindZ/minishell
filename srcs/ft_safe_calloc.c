/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_calloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:57:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/06/29 12:59:55 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*The ft_calloc() function shall allocate unused space for an array of
<count> elements each of whose size in bytes is <size>.  The space
shall be initialized to all bits 0.*/
void	*ft_safe_calloc(size_t count, size_t size, t_data *data)
{
	void	*a;

	a = (malloc(count * size));
	if (!a)
	{
		free_list_ltkn(data->ltkn);
		free (data->read);
		free (data->line);
		ft_freeall(data->envp);
		free (data);
		ft_putstr_fd("Memory Fatal ERROR!!!!", STDERR_FILENO);
		exit(1);
	}
	ft_bzero(a, count * size);
	return (a);
}
