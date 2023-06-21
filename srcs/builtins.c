/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/20 21:29:33 by emman            ###   ########.fr       */
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
	home = getenv("HOME");
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

void	mini_export(t_data *data, t_ltkn *temp)
{
	int		i;
	int		j;
	char 	**new_env;

	i = 0;
	j = 0;
	new_env = NULL;
	while (data->envp[j])
		j++;
	while (ft_strncmp(temp->arg[1], data->envp[i], ft_strlen(temp->arg[1])))
		i++;
	if (temp->arg[1] == NULL)
	{
		while (data->envp[i])
			ft_printf("declare -x %s\n", data->envp[i]);
	}
	if (i == j)
	{
		new_env = env_cpy(data->envp, 1);
		j++;
		new_env[j] = ft_calloc(ft_strlen(temp->arg[1]), sizeof(char));
		new_env[j] = temp->arg[1];
		free (data->envp);
		data->envp = new_env;
	}
	else
	{
		
	}

	// TODO changer les messages d'erreurs avec stderr ou perror
}

void	mini_unset(t_data *data)
{
	int	result;
	int	i;

	i = 0;
	result = unsetenv(data->ltkn->arg[1]);
	if (result != 0)
		ft_printf("Error");
	// TODO changer les messages d'erreurs avec stderr ou perror
	while (data->envp[i])
	{
		if (ft_strncmp(data->ltkn->arg[1], data->envp[i], ft_strlen(data->ltkn->arg[1])) == 0)
		{
			// enlève la ligne data->ltkn->arg[1] dans data->enp[i] avec le malloc pis toute.
		}
	}
}
