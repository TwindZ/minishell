/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/28 13:14:35 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_echo(int fd, t_ltkn *temp)
{
	int	i;

	i = 1;
	if (temp->arg[1] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	while (temp->arg[i])
	{
		if (i < 2 && ft_strncmp(temp->arg[1], "-n\0", 3) == 0)
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
	int		i;
	int		result;
	char	*home;

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
			ft_printf("Minishell: cd: %s: No such file or directory\n",
				temp->arg[i]);
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
// TODO changer les messages d'erreurs avec stderr ou perror

void	mini_unset(t_data *data, t_ltkn *temp)
{
	int		i;
	int 	j;
	char	*to_find;
	char	**new_env;
	
	i = 0;
	j = 0;
	while (data->envp[i])
		i++;
	new_env = ft_calloc(i, sizeof(char *));
	if(!new_env)
		exit (1);
	i = 0;
	to_find = NULL;
	to_find = ft_strjoin(temp->arg[1], "=", 0);
	while (data->envp[i])
	{
		if (ft_isalpha(temp->arg[1][0]) == 0 && temp->arg[1][0] != 95)
		{
			ft_putstr_fd("Minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(temp->arg[1], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return ;
		}
		if (ft_strncmp(to_find, data->envp[i], ft_strlen(to_find)) == 0)
			;
		else
		{		
			new_env[j] = ft_calloc(ft_strlen(data->envp[i]) + 1, sizeof(char));
			ft_strlcpy(new_env[j], data->envp[i], ft_strlen(data->envp[i]) + 1);
			j++; 
		}
		i++;
	}
	ft_freeall(data->envp);
	data->envp = NULL;
	data->envp = new_env;
	free (to_find);
}
// TODO changer les messages d'erreurs avec stderr ou perror
