/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:50:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/20 12:14:24 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**env_cpy(char **envp, int exp)
{
	int	i;
	char	**enviro;

	i = 0;
	while (envp[i])
		i++;
	enviro = ft_calloc(i + 1, sizeof(char *));
	if (!enviro)
		exit(1);
	i = 0;
	while (envp[i])
	{
		enviro[i] = ft_calloc(ft_strlen(envp[i]) + 1 + exp, sizeof(char));
		if (!enviro)
			exit(1);
		ft_memcpy(enviro[i], envp[i], ft_strlen(envp[i]));
		i++;
	}
	return(enviro);
}

char	*getenvp(t_data *data, char *var, int extract)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	result = NULL;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if ((ft_strncmp(data->envp[i], var, len) == 0) && extract == 1)
		{
			j = len + 2;
			while (data->envp[i][j])
			{
				k++;
				j++;
			}
			result = ft_calloc(k + 1, sizeof(char));
			if (!result)
				mini_free(data);
			j = len + 2;
			k = 0;
			while (data->envp[i][j])
				result[k++] = data->envp[i][j++];
			return (result);
		}
		else if ((ft_strncmp(data->envp[i], var, len) == 0) && extract == 0)
		{
			j = len + 2;
			return ("ok");
		}
		i++;
	}
	return (0);
}
