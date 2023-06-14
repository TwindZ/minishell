/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:01 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/14 11:07:42 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"

// void	check_path(t_data *data, char **arg)
// {
// 	char	*path;
// 	int i;
	
// 	i = 0;
// 	path = NULL;
// 	path = ft_split(getenv("PATH"), ':');
// 	while (path[i])
// 	{
// 		path = ft_strjoin(path[i], "/", 0);
// 		path = ft_strjoin(path, arg[data->i], 1);//temporaire
// 		;
// 		if (!access(path, X_OK))
// 		{
// 			data
// 			break ;
// 		}
// 		i++;
// 		free (path);
// 	}
// 	if(data->i == -1)
// 		ft_printf("Minishell: %s: command not found\n", data->ltkn->arg[0]);
// }
