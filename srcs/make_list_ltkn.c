/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_ltkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:39 by fbouchar          #+#    #+#             */
/*   Updated: 2023/06/19 16:03:09 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_meta(t_data *data, char **arg)
{
	if(!ft_strncmp(arg[data->i], "<<\0", 3)
		|| !ft_strncmp(arg[data->i], "<\0", 2)
		|| !ft_strncmp(arg[data->i], ">>\0", 3)
		|| !ft_strncmp(arg[data->i], ">\0", 2))
		return(1);
	return (0);
}

void	set_meta(t_data *data, char **arg)
{
	t_ltkn *temp;

	temp = data->ltkn;
	temp = ft_lstlast_tkn(temp);
	if(ft_strncmp(arg[data->i], ">\0", 2) == 0)
	{
		free(arg[data->i++]);
		if (is_meta(data, arg) == 0)
		{
			open_outfile(data, arg[data->i], 0); //TODO si fichier qui suis est un token besoin d'erreur
			data->temp_out_mod = 1;
			if(data->temp_outfile)
				free(data->temp_outfile);
			data->temp_outfile = arg[data->i];
		}
		else
		{
			ft_putstr_fd("erreur de syntaxe deux meta", 2);
			exit(EXIT_FAILURE);
		}
	}
	else if (ft_strncmp(arg[data->i], ">>\0", 3) == 0)
	{
		free(arg[data->i++]);
		if (is_meta(data, arg) == 0)
		{
			open_outfile(data, arg[data->i], 0); //TODO si fichier qui suis est un token besoin d'erreur
			data->temp_out_mod = 2;
			if(data->temp_outfile)
				free(data->temp_outfile);
			data->temp_outfile = arg[data->i];
		}
		else
		{
			ft_putstr_fd("erreur de syntaxe deux meta", 2);
			exit(EXIT_FAILURE);
		}
	}
	else if (ft_strncmp(arg[data->i], "<\0", 2) == 0)//TODO si fichier qui suis est un token besoin d'erreur
	{
		free(arg[data->i++]);
		if (is_meta(data, arg) == 0)
		{
			data->temp_in_mod = 1;
			data->temp_infile = arg[data->i];
		}
		else
		{
			ft_putstr_fd("erreur de syntaxe deux meta", 2);
			exit(EXIT_FAILURE);
		}
	}
	
	else if (ft_strncmp(arg[data->i], "<<\0", 3) == 0)//TODO si fichier qui suis est un token besoin d'erreur
	{
		free(arg[data->i++]);
		if (is_meta(data, arg) == 0)
		{
			data->temp_in_mod = 2;
			data->temp_infile = arg[data->i];
		}
		else
		{
			ft_putstr_fd("erreur de syntaxe deux meta", 2);
			exit(EXIT_FAILURE);
		}

	}
}

void build_cmd_param(t_data *data, char **arg)
{
	t_ltkn *temp;

	temp = data->ltkn;
	temp = ft_lstlast_tkn(temp);
	if(strncmp(arg[data->i], "|\0", 2) == 0)
	{
		temp->front_pipe = 1;
		data->j = 0;
		return ;
	}	
	else if(is_meta(data, arg))
	{
		set_meta(data, arg);
	}
	else
	{
		temp->arg[data->j++] = arg[data->i];
	}
}

int ft_count_arg(char **arg, int i)
{
	int j;
	
	j = 0;
	while((ft_strncmp(arg[i], "|\0", 2)) && arg[i++])
		j++;
	return (j);
	ft_printf("%d\n", j);
}

void	make_list_ltkn(t_data *data)
{
	char	**arg;
	t_ltkn	*temp;
	int nbarg;
	
	nbarg = 0;
	temp = NULL;
	data->i = 0;
	data->j = 0;
	arg = NULL;
	arg = ft_split(data->line, '\t');
	// TODO if (!arg)
	while (arg[data->i])
	{
		if(data->j == 0 && is_meta(data, arg) == 0)
		{
			nbarg = ft_count_arg(arg, data->i);
			if(!data->ltkn)
			{	
				temp = ft_lstnew_tkn(arg[data->i], nbarg, data->j);
				data->ltkn = temp;
			}			
			else
			{
				temp->next = ft_lstnew_tkn(arg[data->i], nbarg, data->j);
				temp = temp->next;
			}
			check_path(data, arg, temp);
			data->j++;
		}
		else
			build_cmd_param(data, arg);
		if(temp && data->j > 0)
		{
			temp->in_mod = data->temp_in_mod;	
			temp->out_mod = data->temp_out_mod;	
			temp->infile = data->temp_infile;	
			temp->outfile = data->temp_outfile;
		}
		if (strncmp(arg[data->i], "|\0", 2) == 0)
		{
			data->temp_in_mod = 0;
			data->temp_out_mod = 0;
			data->temp_infile = NULL;
			data->temp_outfile = NULL;
			free(arg[data->i]);
		}
		data->i++;
	}
	free(arg);
	//TODO a optimiser if/else + cur_ltkn;
}


t_ltkn	*ft_lstnew_tkn(char *content, int nbarg, int index)
{
	t_ltkn	*ltkn;

	ltkn = ft_calloc(1, sizeof(t_ltkn));
	ltkn->arg = ft_calloc(nbarg + 1, sizeof(char *));
	if (!ltkn)
		return (NULL);
	ltkn->arg[index] = content;
	ltkn->next = NULL;
	return (ltkn);
}

t_ltkn	*ft_lstlast_tkn(t_ltkn *ltkn)
{
	if (ltkn)
	{
		while (ltkn->next)
			ltkn = ltkn->next;
	}
	return (ltkn);
}

void	print_list(t_data *data)
{
	t_ltkn	*temp;
	int i;

	temp = data->ltkn;
	while (temp != NULL)
	{
		i = 0;
		ft_printf("\npath : %s\n", temp->path);
		ft_printf("argv : ");
		while(temp->arg[i])
			ft_printf("%s, ", temp->arg[i++]);
		ft_printf("\n");
		ft_printf("infile : %s\n", temp->infile);
		ft_printf("infile : %d\n", temp->in_mod);
		ft_printf("outfile : %s\n", temp->outfile);
		ft_printf("infile : %d\n", temp->out_mod);
		ft_printf("frontpipe : %i\n\n", temp->front_pipe);
		
		
		temp = temp->next;
	}	
}
