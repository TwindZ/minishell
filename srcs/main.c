/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/03 16:50:55 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char *path, char **argv)
{
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
	char *argv[] = {"rm", "-rf", "-rf", NULL};
	char path[] = "/bin/rm";

	i = 0;
	ft_printf("%d\n", access("/bin/ls", X_OK));
	ft_printf("%s\n", getcwd(NULL, 0));
	ft_printf("%d\n", chdir("./srcs"));
	ft_printf("%s\n", getenv("PATH"));
	envarr = ft_split(getenv("PATH"),':');
	// chdir("/usr/bin/");
	ft_printf("%s\n", getcwd(NULL, 0));
	
	ft_execute(path, argv);
	ft_printf("apres execute\n");
}