/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:38:51 by jbouazao          #+#    #+#             */
/*   Updated: 2020/02/01 11:30:33 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//should redo this
t_links		*creat_lnk_lst(t_rooms **rm)
{
	t_links	*elmnt;
	
	//not freed yet
	elmnt = (t_links *)ft_memalloc(sizeof(t_links));
	elmnt->link = (*rm)->name;//should remove this because we changed the logic
	elmnt->lnk = *rm;
	elmnt->flow = 1;
	elmnt->next = NULL;
	return (elmnt);
}

void		add_lnk_lst(t_rooms **rm, t_links **lnk_lst)
{
	t_links	*temp;
	t_links	*node;

	temp = *lnk_lst;
	//not freed yet
	node = (t_links *)ft_memalloc(sizeof(t_links));
	node->link = (*rm)->name;
	node->lnk = *rm;
	node->flow = 1;
	node->next = NULL;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
}
//-----------------------------------------------------------------------
static int	creat_rm_lst(t_rooms **rm, char *line)
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
	return (1);
}

static int	add_rm_lst(t_rooms **rm, char *line)
{
	t_rooms	*temp;
	t_rooms	*node;

	temp = *rm;
	node = (t_rooms *)ft_memalloc(sizeof(t_rooms));
	node->name = NULL;
	node->next = NULL;
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

int			add_to_list(t_rooms **rm, char *line)
{
	if (!(*rm))
	{
		if (!creat_rm_lst(rm, line))
		{
			ft_strdel(&line);
			return (0);
		}
	}
	else if (!add_rm_lst(rm, line))
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

t_rooms		*node_dup_with_name(t_rooms *temp)
{//dupped not freed yet 
	t_rooms		*dupped;

	if (!(dupped = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
	{
		ft_printf("couldnt allocate node in node_dup_with_name\n");
		return (NULL);
	}
	else
	{
		if (temp->name == NULL)
		{
			ft_memdel((void *)dupped);
			return (NULL);
		}
		dupped->name = ft_strdup(temp->name);
		dupped->rm = temp->rm;
		dupped->vstd = 0;
		dupped->flag = 0;
		dupped->cap = 0;
		dupped->prev = NULL;
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