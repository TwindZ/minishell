/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:25:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/29 15:25:07 by emlamoth         ###   ########.fr       */
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

	char *argv1[] = {"env", NULL};
	char path1[] = "/usr/bin/env";
	char *argv2[] = {"grep", "PATH", NULL};
	char path2[] = "/usr/bin/grep";
	char *argv3[] = {"cat", "-e", NULL};
	char path3[] = "/bin/cat";

void ft_new_pipe(t_data *data)
{
	int fd[2];
	
	pipe(fd);
	data->pfdr = fd[0];
	data->pfdw = fd[1];
	ft_printf("%d\n", fd[0]);
	ft_printf("%d\n", fd[1]);
}

void mini_execute(t_data *data)
{
	int id;
	int fd[2];
	int front_pipe;
	int back_pipe;

	front_pipe = 1;
	back_pipe = 0;
	if(front_pipe == 1)
	{
		pipe(fd);
	}
	id = fork();
	if (id == 0)
	{
		if (back_pipe)
		{
			dup2(fd[0], STDIN_FILENO);
		}
		else
		{
			close(fd[0]);
		}
		if (front_pipe)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		else
		{
			close(fd[1]);
		}
		execve(path1, argv1, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
	}
	wait (NULL);
	front_pipe = 1;
	back_pipe = 1;
	if(front_pipe == 1)
	{
		data->pfdr = fd[0];
		pipe(fd);
	}
	id = fork();
	if (id == 0)
	{
		if (back_pipe)
		{
			
			dup2(data->pfdr, STDIN_FILENO);
		}
		else
		{
			close(fd[1]);
		}
		if (front_pipe)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		else
		{
			close(fd[1]);
		}
		execve(path2, argv2, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
	}
	front_pipe = 0;
	back_pipe = 1;
	if(front_pipe == 1)
	{
		data->pfdr = fd[0];
		pipe(fd);
	}
	id = fork();
	if (id == 0)
	{
		if (back_pipe)
		{
			dup2(data->pfdr, STDIN_FILENO);
		}
		else
		{
			close(fd[1]);
		}
		if (front_pipe)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		else
		{
			close(fd[1]);
		}
		execve(path3, argv3, data->envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
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

