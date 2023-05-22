/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:39:22 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/22 13:17:33 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_data()
{
	static t_data *data;
	
	if(!data)
	{
		data = malloc(sizeof(data));
		
	}
	return (data)
}
// void	ft_execute(char *path, char **argv, int fd)
// {
// 	int id;
// 	id = fork();
// 	if (id == 0)
// 	{
		
// 		execve(path, argv, NULL);
// 		exit(EXIT_SUCCESS);
// 	}
// 	wait (NULL);
// }

// int	*ft_pipe()
// {
// 	int *fd[2];

// 	pipe(fd);
	
// }

int main()
{
	t_data data;
	int fd;
	// int ret;
	int id ;
	char *argv[] = {"ls", "-la", "-la", "-la", "-la", "-la", "/bin", NULL};
	char path[] = "/bin/ls";
	char *argv2[] = {"allo", "-e", NULL};
	char path2[] = "/bin/cat";
	int pfd[2];
	
	pipe(pfd);
	data.pfdr = pfd[0];
	data.pfdw = pfd[1];
	
	fd = open("allo.txt", O_RDWR);
	
	// ft_printf("%d\n", fd);
	// dup2(fd, pfd);
	id = fork();
	if(id == 0)
	{
		dup2(pfd[1], STDOUT_FILENO);
		execve(path, argv, NULL);
	}
	id = fork();
	if(id == 0)
	{
		dup2(pfd[0], STDIN_FILENO);
		execve(path2, argv2, NULL);
	}
	close(data.pfdr);
	close(data.pfdw);
	// ft_printf("%d\n", fd);
	// ft_printf("%d\n", ret);
	// ft_printf("%d\n", STDIN_FILENO);
	// t_data *data;
	
	// char **envarr;
	// int i;
	// int pipe;
	// char *argv[] = {"ls", "-la", NULL};
	// char path[] = "/bin/ls";
	// char *argv2[] = {"cat", NULL};
	// char path2[] = "/bin/cat";
	// pipe = 0;
	// i = 0;
	// ft_printf("%d\n", access("/bin/ls", X_OK));
	// ft_printf("%s\n", getcwd(NULL, 0));
	// ft_printf("%d\n", chdir("./srcs"));
	ft_printf("%s\n", getenv("PATH"));
	envarr = ft_split(getenv("PATH"),':');
	// chdir("/usr/bin/");
	// ft_printf("%s\n", getcwd(NULL, 0));
	// if(pipe == 0)
	// 	ft_execute(path, argv, STDOUT_FILENO);
	// else
	// {	
	// 	ft_execute(path, argv);
	// }
	// ft_printf("apres execute #1\n");
	test commit encore
	on essai d'autre chose
	encore autre chose
	
	return(0);
}