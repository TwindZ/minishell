/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/03 15:18:10 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	struct stat *test;
	char **envarr;
	int i;
	int j;
	char *argv[] = {"ls", "-la", NULL};

	j = 0;
	i = 0;
	test = NULL;
	ft_printf("%d\n", access("/bin/ls", X_OK));
	ft_printf("%s\n", getcwd(NULL, 0));
	ft_printf("%d\n", chdir("./srcs"));
	ft_printf("%s\n", getenv("PATH"));
	envarr = ft_split(getenv("PATH"),':');
	chdir("../../..");
	getcwd(NULL, 0);
	execve("/bin/ls", argv, NULL);


	
	
}