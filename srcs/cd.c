/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:19:05 by fbouchar          #+#    #+#             */
/*   Updated: 2023/07/18 17:16:39 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_cd(t_data *data, t_ltkn *temp)
{
	char	*home;

	data->i = 0;
	change_oldpwd(data);
	home = NULL;
	home = getenvp(data, "HOME=", 1);
	if (!home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", STDERR_FILENO);
		data->prevout = 1;
		return ;
	}
	while (temp->arg[data->i])
		data->i++;
	change_dir(data, temp, home);
	free(home);
	data->lastwd = getenvp(data, "PWD=", 1);
	data->lastwd = ft_mini_strjoin(data->lastwd, "/", 1, data);
	data->lastwd = ft_mini_strjoin(data->lastwd, temp->arg[data->i], 1, data);
	change_pwd(data);
}

void	change_pwd(t_data *data)
{
	t_ltkn	*export;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	export = ft_lstnew_tkn(ft_mini_strjoin(NULL, "export", 0, data), 2, 0);
	export->arg[1] = ft_mini_strjoin("PWD=", cwd, 0, data);
	mini_export(1, data, export);
	free(cwd);
	cwd = NULL;
	free_list_ltkn(export);
}

void	change_oldpwd(t_data *data)
{
	t_ltkn	*export;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	export = ft_lstnew_tkn(ft_mini_strjoin(NULL, "export", 0, data), 2, 0);
	export->arg[1] = ft_mini_strjoin("OLDPWD=", cwd, 0, data);
	mini_export(1, data, export);
	free(cwd);
	cwd = NULL;
	free_list_ltkn(export);
}

void	change_dir(t_data *data, t_ltkn *temp, char *home)
{
	int	result;

	result = 0;
	if (data->i == 2)
	{
		data->i = 1;
		result = chdir(temp->arg[data->i]);
		if (result != 0)
			error_directory(data, temp);
		return ;
	}
	else if (data->i == 1)
	{
		result = chdir(home);
		if (result != 0)
			ft_putstr_fd("Minishell: cd: cant't find HOME directory\n",
				STDERR_FILENO);
		data->prevout = 1;
		return ;
	}
	else if (data->i > 2)
		error_arguments(data);
}
