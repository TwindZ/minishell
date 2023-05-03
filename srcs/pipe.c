/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:23:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/05/03 13:29:23 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe()
{
	int fd[2];
	int id;

	pipe(fd);
	id = fork();
	if(id == 0)
	{
		
	}
	else
	{
		
	}
}

int main()
{
	int x;
	int y;
	int fd[2];
	int fd2[2];
	int fd3[2];
	int id;
	int id2;
	int id3;
	
	pipe(fd);
	id = fork();
	if(id == 0)
	{
		pipe(fd2);
		id2 = fork();
		if(id2 == 0)
		{
			x = 5;
			ft_printf("1 %d\n", x);
		}
		else
		{
			x = 9;
			ft_printf("2 %d\n", x);
		}
		if(id2 == 0)
		{
			close(fd2[0]);
			write(fd2[1], &x, sizeof(x));
			close(fd2[1]);
		}
		else
		{
			close(fd2[1]);
			read(fd2[0], &y, sizeof(y));
			close(fd2[0]);
			wait(NULL);
			x = x + y;
		}
		if(id2 != 0)
			ft_printf("3 %d\n", x);
	}
	else
	{
		pipe(fd3);
		id3 = fork();
		if(id3 == 0)
		{
			x = 20;
			ft_printf("4 %d\n", x);
		}
		else
		{
			x = 3;
			ft_printf("5 %d\n", x);
		}
		if(id3 == 0)
		{
			close(fd3[0]);
			write(fd3[1], &x, sizeof(x));
			close(fd3[1]);
		}
		else
		{
			close(fd3[1]);
			read(fd3[0], &y, sizeof(y));
			close(fd3[0]);
			wait(NULL);
			x = x + y;
		}
		if(id3 != 0)
			ft_printf("6 %d\n", x);
	}
	if(id == 0)
	{
		ft_printf("7 %d\n", x);
		close(fd[0]);
		write(fd[1], &x, sizeof(x));
		close(fd[1]);
	}
	else if(id != 0 && id3 != 0)
	{
		close(fd[1]);
		read(fd[0], &y, sizeof(y));
		close(fd[0]);
		wait(NULL);
		ft_printf("8 %d\n", y);
		x += y;
		ft_printf("9 %d\n", x);
	}
	else 
		;
	if(id != 0 && id3 != 0)
		ft_printf("10 %d\n", x);
}