/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:35:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/29 13:29:05 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	mini_unset(t_data *data, t_ltkn *temp)
{
	char	*to_find;
	char	**new_env;

	data->i = 0;
	data->j = 0;
	while (data->envp[data->i])
		data->i++;
	new_env = ft_safe_calloc(data->i, sizeof(char *), data);
	data->i = 0;
	to_find = NULL;
	to_find = ft_strjoin(temp->arg[1], "=", 0);
	while (data->envp[data->i])
	{
		if (ft_isalpha(temp->arg[1][0]) == 0 && temp->arg[1][0] != 95)
		{
			ft_putstr_fd("Minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(temp->arg[1], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return ;
		}
		if (ft_strncmp(to_find, data->envp[data->i], ft_strlen(to_find)) == 0)
			;
		else
		{
			new_env[data->j] = ft_safe_calloc(ft_strlen(data->envp[data->i]) + 1,
					sizeof(char), data);
			ft_strlcpy(new_env[data->j], data->envp[data->i],
				ft_strlen(data->envp[data->i]) + 1);
			data->j++; 
		}
		data->i++;
	}
	ft_freeall(data->envp);
	data->envp = NULL;
	data->envp = new_env;
	free (to_find);
}
// TODO changer les messages d'erreurs avec stderr ou perror
