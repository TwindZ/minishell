/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:39:08 by emlamoth          #+#    #+#             */
/*   Updated: 2023/07/12 09:42:24 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	path_error(t_data *data, t_ltkn *temp, int err)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(temp->arg[0], 2);
	if (err)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
	data->prevout = 127;
}

int	is_builtin(char *arg)
{
	if (!strncmp(arg, "echo\0", 5)
		|| !strncmp(arg, "cd\0", 3)
		|| !strncmp(arg, "pwd\0", 4)
		|| !strncmp(arg, "export\0", 7)
		|| !strncmp(arg, "unset\0", 6)
		|| !strncmp(arg, "env\0", 4)
		|| !strncmp(arg, "exit\0", 5))
		return (1);
	return (0);
}
