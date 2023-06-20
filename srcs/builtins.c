/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/20 08:58:35 by fbouchar         ###   ########.fr       */
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

void	mini_exit(void)
{
	ft_printf("exit\n");
	exit(0);
}

void	mini_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_printf("%s\n", data->envp[i]);
		i++;
	}
}

void	mini_cd(t_data *data)
{
	int 	i;
	int		result;
	char	*home;

	i = 0;
	result = 0;
	home = NULL;
	home = getenv("HOME");
	if (!home)
		ft_printf("HOME not found");
	while (data->ltkn->arg[i])
		i++;
	if (i == 2)
	{
		i = 1;
		result = chdir(data->ltkn->arg[i]);
		if (result != 0)
			ft_printf("Minishell: cd: %s: No such file or directory", data->ltkn->arg[i]);
		// TODO changer les messages d'erreurs avec stderr ou perror
		return ;
	}
	else if (i == 1)
	{
		result = chdir(home);
		if (result != 0)
			ft_printf("Minishell: cd: Cant't find HOME directory");
		return ;
	}
}