/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:38:51 by jbouazao          #+#    #+#             */
/*   Updated: 2019/12/07 13:10:42 by yjouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	creat_rm_lst(t_rooms **rm, char *line, char c)
{
	(*rm) = (t_rooms *)ft_memalloc(sizeof(t_rooms));
	(*rm)->name = NULL;
	(*rm)->next = NULL;
	if (!((*rm)->name = valid_room(line)))
	{
		ft_printf("error: room is not valid\n");
		ft_memdel((void **)rm);
		return (0);
	}
	(*rm)->rm = c;
	return (1);
}

static int	add_rm_lst(t_rooms **rm, char *line, char c)
{
	t_rooms	*temp;
	t_rooms	*node;

	temp = *rm;
	node = (t_rooms *)ft_memalloc(sizeof(t_rooms));
	node->name = NULL;
	node->next = NULL;
	node->rm = c;
	while (temp->next != NULL)
		temp = temp->next;
	if (!(node->name = valid_room(line)))
	{
		ft_printf("error: room is not valid\n");
		ft_memdel((void **)&node);
		return (0);
	}
	temp->next = node;
	return (1);
}

int			add_to_list(t_rooms **rm, char *line, char c)
{
	if (!(*rm))
	{
		if (!creat_rm_lst(rm, line, c))
		{
			ft_strdel(&line);
			return (0);
		}
	}
	else if (!add_rm_lst(rm, line, c))
	{
		ft_strdel(&line);
		free_list(rm);
		return (0);
	}
	return (1);
}

void		prnt_rms_lst(t_rooms *rm)
{
	t_rooms	*temp;

	temp = rm;
	if (temp == NULL)
		ft_printf("list is empty\n");
	while (temp != NULL)
	{
		ft_printf("name = %s| rm = %c\n", temp->name, temp->rm);
		temp = temp->next;
	}
}

void		free_list(t_rooms **rm)
{
	t_rooms *temp;

	temp = *rm;
	while (*rm)
	{
		*rm = (*rm)->next;
		ft_strdel(&temp->name);
		ft_memdel((void **)&temp);
		temp = *rm;
	}
}

t_rooms		*node_dup_with_name(char *name)
{//dupped not freed yet 
	t_rooms		*dupped;

	if (!(dupped = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
	{
		ft_printf("couldnt allocate node in node_dup_with_name\n");
		return (NULL);
	}
	else
	{
		if (name == NULL)
		{
			ft_memdel((void *)dupped);
			return (NULL);
		}
		dupped->name = ft_strdup(name);
		dupped->rm = 0;
		dupped->next = NULL;
	}
	return (dupped);
}

int			node_list_count(t_rooms *rm)
{
	int		count;
	t_rooms	*temp;

	count = 0;
	temp = rm;
	if (rm)
		while (temp)
		{
			count++;
			temp = temp->next;
		}
	else
		return (0);
	return (count);
}