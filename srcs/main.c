/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/29 10:26:12 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define emman 1
#define frank 0

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	if(emman)
	{
		int i;
		i = 0;
		ft_printf("emman\n");
		// while(ft_strncmp(envp[i], "_=", 2))
		// {
		// 	ft_printf("%s\n", envp[i++]);
		// }
		mini_execute();
	}

// test
	if(frank)
	{
		ft_printf("frank\n");
	}
	
}