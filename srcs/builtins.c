/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/15 14:20:19 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_echo(int fd, t_data *data)
{
	int i;

	i = 0;
	if (ft_strncmp(data->ltkn->arg[i], "-n", 2))
		i = 2;
	else
		i = 1;
	if (data->ltkn->arg[1] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return;
	}
	while (data->ltkn->arg[i])
	{
		ft_putstr_fd(data->ltkn->arg[i], fd);
		if (data->ltkn->arg[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
	}
	if (ft_strncmp(data->ltkn->arg[1], "-n", 2))
		ft_putstr_fd("\n", fd);
}

void	mini_pwd(int fd)
{
	char	buffer[PATH_MAX];
	
	ft_putstr_fd(getcwd(buffer, sizeof(buffer)), fd);
	ft_putstr_fd("\n", fd);
}

void	mini_cd(int fd)
{
	(void)fd;
}