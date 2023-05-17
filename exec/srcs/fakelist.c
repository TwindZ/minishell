#include "minishell.h"

t_lst	*ft_listnew_cmd(char *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_lst));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

t_lst	*ft_listlast(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_listadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = ft_listlast(*lst);
			last->next = new;
		}
	}
}

int main()
{
	t_data	data;
	t_lst	lst;

	ft_listnew_cmd("ls")
	ft_listadd_back()
}