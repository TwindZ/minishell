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
		ft_memcpy(enviro[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	return(enviro);
}
