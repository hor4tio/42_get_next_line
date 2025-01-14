/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 12:05:26 by hor4tio      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 18:10:50 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

void	safe_free(char **tab)
{
	if (*tab)
		free(*tab);
	*tab = NULL;
}

t_list	*lstnew(int fd)
{
	t_list *list;

	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->fd = fd;
	list->rest = NULL;
	list->rest2 = NULL;
	list->next = NULL;
	return (list);
}

t_list	*fd_check(t_list **list, int fd)
{
	t_list	*tmp;
	t_list	*new;

	if (!(*list))
		return (*list = lstnew(fd));
	tmp = *list;
	while (tmp && tmp->fd != fd)
	{
		if (tmp->next == NULL)
		{
			new = lstnew(fd);
			tmp->next = new;
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int		lst_del(int return_value, t_list **list,
					t_list **to_delete, char **str)
{
	t_list	*tmp;

	if ((*str) != NULL)
		safe_free(str);
	if (*list && *to_delete)
	{
		tmp = *list;
		if (*to_delete == *list)
			*list = (*to_delete)->next;
		else
		{
			while (tmp->next != *to_delete)
				tmp = tmp->next;
			tmp->next = (*to_delete)->next;
		}
		safe_free(&((*to_delete)->rest));
		safe_free(&((*to_delete)->rest2));
		free(*to_delete);
		*to_delete = NULL;
	}
	return (return_value);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if (!(dst = (char *)malloc(i + j + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		dst[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	return (dst);
}
