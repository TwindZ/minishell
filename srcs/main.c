/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/17 13:08:55 by emlamoth         ###   ########.fr       */
=======
/*   Updated: 2023/05/17 11:07:09 by fbouchar         ###   ########.fr       */
>>>>>>> 7bcd9386626e5c22899c46b6486db52e125282f2
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char *path, char **argv)
{
	// allo man
	int id;
	id = fork();
	if (id == 0)
	{
		execve(path, argv, NULL);
		exit(EXIT_SUCCESS);
	}
	wait (NULL);
}

int main()
{

	
	char **envarr;
	int i;
	char *argv[] = {"ls", "-la", NULL};
	char path[] = "/bin/ls";

	i = 0;
	ft_printf("%d\n", access("/bin/ls", X_OK));
	ft_printf("%s\n", getcwd(NULL, 0));
	ft_printf("%d\n", chdir("./srcs"));
	ft_printf("%s\n", getenv("PATH"));
	envarr = ft_split(getenv("PATH"),':');
	chdir("/usr/bin/");
	ft_printf("%s\n", getcwd(NULL, 0));
	
	ft_execute(path, argv);
	ft_printf("apres execute\n");
}