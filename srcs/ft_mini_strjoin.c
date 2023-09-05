/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:56:57 by fbouchar          #+#    #+#             */
/*   Updated: 2023/08/31 20:38:39 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*This function is a custom strjoin implementation for minishell, utilizing
safe_calloc.*/
char	*ft_mini_strjoin(char *s1, char *s2, int fr, t_data *data)
{
	unsigned int	lens1;
	unsigned int	lens2;
	char			*newstr;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	newstr = ft_safe_calloc(lens1 + lens2 + 1, sizeof(char), data);
	ft_memcpy(newstr, s1, lens1);
	ft_memcpy(newstr + lens1, s2, lens2);
	newstr[lens1 + lens2] = '\0';
	if (fr == 1)
		free(s1);
	return (newstr);
}
