/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:15:30 by jbouazao          #+#    #+#             */
/*   Updated: 2020/01/25 13:24:37 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_q			*init_queue(char *start)
{
	t_q		*start_node;

	start_node = (t_q *)ft_memalloc(sizeof(t_q));
	start_node->name = ft_strdup(start);//should be freed
	start_node->next = NULL;
	return (start_node);
}

void		add_to_queue(t_q **qu, t_links *it_lnk)
{
		t_q *new_node;
		t_q	*it_qu;

		it_qu = *qu;
		new_node = (t_q *)ft_memalloc(sizeof(t_q));
		new_node->name = ft_strdup(it_lnk->link);
		new_node->next = NULL;
		while (it_qu->next)
			it_qu = it_qu->next;
		it_qu->next = new_node;
}

int			add_links_to_queue(t_q **qu, char *name, t_rooms **ht, t_s dt)
{
	t_links	*it_lnk;
	t_rooms	*tmp_node;

	tmp_node = ht[hash_name(name)];
	while (tmp_node && ft_strcmp(tmp_node->name, name))
		tmp_node = tmp_node->next;
	it_lnk = tmp_node->links;
	while (it_lnk)
	{
		t_rooms	*tmp_lnk;//the link "it_lnk->link" in the hashtable
		tmp_lnk = ht[hash_name(it_lnk->link)];
		while (tmp_lnk && ft_strcmp(tmp_lnk->name, it_lnk->link))
			tmp_lnk = tmp_lnk->next;
		if (!ft_strcmp(dt.st, name) && it_lnk->flow > 0 && !tmp_lnk->vstd)
		{
			ft_printf("1\n");
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && !tmp_lnk->prev->cap && tmp_lnk->cap &&
		it_lnk->flow == 2 && !tmp_lnk->vstd)
		{
			ft_printf("2\n");
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && tmp_lnk->prev->cap && tmp_lnk->cap &&
		it_lnk->flow > 0 && !tmp_lnk->vstd)
		{
			ft_printf("3\n");
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && !tmp_lnk->prev->cap && !tmp_lnk->cap &&
		it_lnk->flow > 0 && !tmp_lnk->vstd)
		{
			ft_printf("4\n");
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}
		if (!ft_strcmp(tmp_lnk->name, dt.end) && it_lnk->flow > 0)//should free queue
		{
			ft_printf("5\n");
			return (1);
		}
		it_lnk = it_lnk->next;
	}
	return (0);
}

int			fill_queue(t_s dt, t_rooms **ht)
{
	t_rooms	*it_ht;

	it_ht = ht[hash_name(dt.st)];
	while (it_ht)
	{
		if (ft_strcmp(dt.st, it_ht->name))
			it_ht = it_ht->next;
		else
		{
			t_q		*qu;
			qu = init_queue(it_ht->name);
			t_q		*temp = qu;
			it_ht->vstd = 1;
			while (qu)
			{
				// printf("Q --> %s\n", qu->name);
				if (add_links_to_queue(&qu, qu->name, ht, dt))
					return (1);
				qu = qu->next;
			}
			// while (temp)
			// {
			// 	ft_printf("%s\n", temp->name);
			// 	temp = temp->next;
			// }
			break ;
		}
	}
	return (0);
}