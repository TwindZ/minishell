/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/17 18:06:17 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char *path, char **argv, int fd)
{
	int id;
	id = fork();
	if (id == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(path, argv, NULL);
		exit(EXIT_SUCCESS);
	}
	wait (NULL);
}

int	*ft_pipe()
{
	int *fd[2];

	pipe(fd);
	
}

int main()
{
	t_data *data;
	
	char **envarr;
	int i;
	int pipe;
	char *argv[] = {"ls", "-la", NULL};
	char path[] = "/bin/ls";
	char *argv2[] = {"cat", NULL};
	char path2[] = "/bin/cat";
	pipe = 0;
	i = 0;
	ft_printf("%d\n", access("/bin/ls", X_OK));
	ft_printf("%s\n", getcwd(NULL, 0));
	ft_printf("%d\n", chdir("./srcs"));
	ft_printf("%s\n", getenv("PATH"));
	envarr = ft_split(getenv("PATH"),':');
	chdir("/usr/bin/");
	ft_printf("%s\n", getcwd(NULL, 0));
	if(pipe == 0)
		ft_execute(path, argv, STDOUT_FILENO);
	else
	{	
		
		ft_execute(path, argv);
	}
	ft_printf("apres execute #1\n");
	

	return(0);
}