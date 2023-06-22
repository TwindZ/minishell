/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/22 12:14:05 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_echo(int fd, t_data *data, t_ltkn *temp)
{
	int i;
	(void) data;

	i = 1;
	if (temp->arg[1] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return;
	}
	while (temp->arg[i])
	{
		if (ft_strncmp(temp->arg[i], "-n\0", 3) == 0)
			i++;
		ft_putstr_fd(temp->arg[i], fd);
		i++;
		if (temp->arg[i] != NULL)
			ft_putstr_fd(" ", fd);
	}
	if (ft_strncmp(temp->arg[1], "-n\0", 3))
		ft_putstr_fd("\n", fd);
}

void	mini_pwd(int fd)
{
	char	buffer[PATH_MAX];
	
	ft_putstr_fd(getcwd(buffer, sizeof(buffer)), fd);
	ft_putstr_fd("\n", fd);
}

//mini exit rendu dans main.c

void	mini_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		// ft_printf("%p\n", data->envp[i]);
		ft_putstr_fd(data->envp[i], data->fd.cmd_out);
		ft_putstr_fd("\n", data->fd.cmd_out);
		i++;
	}
}

void	mini_cd(t_data *data, t_ltkn *temp)
{
	int 	i;
	int		result;
	char	*home;
	(void) data;

	i = 0;
	result = 0;
	home = NULL;
	home = getenvp(data, "HOME", 1);
	if (!home)
		ft_printf("HOME not found");
	while (temp->arg[i])
		i++;
	if (i == 2)
	{
		i = 1;
		result = chdir(temp->arg[i]);
		if (result != 0)
			ft_printf("Minishell: cd: %s: No such file or directory\n", temp->arg[i]);
		// TODO changer les messages d'erreurs avec stderr ou perror
		return ;
	}
	else if (i == 1)
	{
		result = chdir(home);
		if (result != 0)
			ft_printf("Minishell: cd: Cant't find HOME directory\n");
		return ;
	}
}

void	mini_unset(t_data *data, t_ltkn *temp)
{
	int	i;
	char	*to_find;

	i = 0;
	to_find = NULL;
	to_find = ft_strjoin(temp->arg[1], "=", 0);
	while (ft_strncmp(to_find, data->envp[i], ft_strlen(to_find)))
		i++;
	while (data->envp[i + 1] != NULL)
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
	i++;
	data->envp = env_cpy(data->envp, -1);
	// TODO changer les messages d'erreurs avec stderr ou perror
}
