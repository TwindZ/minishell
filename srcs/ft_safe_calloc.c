/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_calloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:57:04 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/13 10:31:35 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_safe_calloc(size_t count, size_t size, t_data *data)
{
	void	*a;

	a = (malloc(count * size));
	if (!a)
	{
		free_list_ltkn(data->ltkn);
		freenull(data->read);
		freenull(data->line);
		ft_freeall(data->envp);
		freenull(data);
		ft_putstr_fd("Memory Fatal ERROR!!!!", STDERR_FILENO);
		exit(1);
	}
	ft_bzero(a, count * size);
	return (a);
}
