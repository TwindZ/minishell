/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/24 14:37:53 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_data *init_data()
// {
// 	static t_data *data;
	
// 	if(!data)
// 	{
// 		data = malloc(sizeof(data));
		
// 	}
// 	return (data);
// }
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

// -------------------readline loop------------------------------
	// char *line;

	// line = NULL;
	
	// while (1)
	// {
	// 	line = (char *)readline("MINISHELL DLA MORT QUI TUE >");
	// 	add_history(line);
	// 	ft_printf("Ligne lu : %s\n", line);
	// }

	char *argv1[] = {"ls", "-la", NULL};
	char path1[] = "/bin/ls";
	char *argv2[] = {"cat", "-e", NULL};
	char path2[] = "/bin/cat";
	char *argv3[] = {"wc", "-w", NULL};
	char path3[] = "usr/bin/wc";

// int	*ft_new_pipe()
// {
// 	int fd[2];

// 	pipe(fd);
// 	return (fd);
// }

void mini_execute()
{
	int id;
	int fd[2];
	int front_pipe;
	int back_pipe;

	front_pipe = 0;
	back_pipe = 0;
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		front_pipe = 1;
		back_pipe = 0;
		if (back_pipe)
			dup2(fd[0], STDIN_FILENO);
		if (front_pipe)
			dup2(fd[1], STDOUT_FILENO);
		execve(path1, argv1, NULL);
	}
	wait ();
	ft_printf("test");
	id = fork();
	if (id == 0)
	{
		front_pipe = 0;
		back_pipe = 1;
		if (back_pipe)
			dup2(fd[0], STDIN_FILENO);
		if (front_pipe)
			dup2(fd[1], STDOUT_FILENO);
		execve(path2, argv2, NULL);
	}
	ft_printf("test");
	wait (NULL);
	ft_printf("test");
	id = fork();
	if (id == 0)
	{
		front_pipe = 0;
		back_pipe = 1;
		if (back_pipe)
			dup2(fd[0], STDIN_FILENO);
		if (front_pipe)
			dup2(fd[1], STDOUT_FILENO);
		execve(path3, argv3, NULL);
	}
	
	
	
}

// int	*ft_pipe()
// {
// 	int *fd[2];

// 	pipe(fd);
	
// }
	
	// t_data data;
	// int fd;
	// // int ret;
	// int id ;
	// char *argv[] = {"ls", "-la", "-la", "-la", "-la", "-la", "/bin", NULL};
	// char path[] = "/bin/ls";
	// char *argv2[] = {"allo", "-e", NULL};
	// char path2[] = "/bin/cat";
	// int pfd[2];
	
	// pipe(pfd);
	// data.pfdr = pfd[0];
	// data.pfdw = pfd[1];
	
	// fd = open("allo.txt", O_RDWR);
	
	// // ft_printf("%d\n", fd);
	// // dup2(fd, pfd);
	// id = fork();
	// if(id == 0)
	// {
	// 	dup2(pfd[1], STDOUT_FILENO);
	// 	execve(path, argv, NULL);
	// }
	// id = fork();
	// if(id == 0)
	// {
	// 	dup2(pfd[0], STDIN_FILENO);
	// 	execve(path2, argv2, NULL);
	// }
	// close(data.pfdr);
	// close(data.pfdw);
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
	// ft_printf("%s\n", getenv("PATH"));
	// envarr = ft_split(getenv("PATH"),':');
	// chdir("/usr/bin/");
	// ft_printf("%s\n", getcwd(NULL, 0));
	// if(pipe == 0)
	// 	ft_execute(path, argv, STDOUT_FILENO);
	// else
	// {	
	// 	ft_execute(path, argv);
	// }
	// ft_printf("apres execute #1\n");

