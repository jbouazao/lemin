/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:15:30 by jbouazao          #+#    #+#             */
/*   Updated: 2020/02/04 17:15:12 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_q			*init_queue(t_rooms *start)
{
	t_q		*start_node;

	start_node = (t_q *)ft_memalloc(sizeof(t_q));
	// start_node->name = ft_strdup(start);//should be freed//temp
	start_node->node = start;
	start_node->next = NULL;
	return (start_node);
}

void		add_to_queue(t_q **qu, t_links *it_lnk)
{
		t_q		*new_node;
		t_q		*it_qu;
		t_rooms	*temp;

		it_qu = *qu;
		new_node = (t_q *)ft_memalloc(sizeof(t_q));//should free if not allocated
		// new_node->name = ft_strdup(it_lnk->link);//thinking to remove this
		new_node->node = it_lnk->lnk;
		new_node->next = NULL;
		while (it_qu->next)
			it_qu = it_qu->next;
		it_qu->next = new_node;
}

int			add_links_to_queue(t_q **qu, t_rooms *node, t_rooms **ht, t_s dt)
{
	t_links	*it_lnk;
	t_rooms	*tmp_node;

	tmp_node = node;
	it_lnk = tmp_node->links;
	while (it_lnk)
	{
		t_rooms	*tmp_lnk;
		tmp_lnk = it_lnk->lnk;
		// while (tmp_lnk && ft_strcmp(tmp_lnk->name, it_lnk->link))
		// 	tmp_lnk = tmp_lnk->next;
		if (!ft_strcmp(dt.st, node->name) && it_lnk->flow > 0 && !tmp_lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && !tmp_node->prev->cap && tmp_node->cap &&
		it_lnk->flow == 2 && !tmp_lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && tmp_node->prev->cap && tmp_node->cap &&
		it_lnk->flow > 0 && !tmp_lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && !tmp_node->prev->cap && !tmp_node->cap &&
		it_lnk->flow > 0 && !tmp_lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			tmp_lnk->vstd = 1;
			tmp_lnk->prev = tmp_node;
		}//should add the condition where cap is 0 and prev cap is 1
		// else if (tmp_node->prev && tmp_node->prev->cap && !tmp_node->cap &&
		// it_lnk->flow > 0 && !tmp_lnk->vstd)
		// {
		// 	add_to_queue(qu, it_lnk);
		// 	tmp_lnk->vstd = 1;
		// 	tmp_lnk->prev = tmp_node;
		// }
		if (!ft_strcmp(tmp_lnk->name, dt.end) && it_lnk->flow > 0)
		{
			return (1);
		}
		it_lnk = it_lnk->next;
	}
	return (0);
}

void		correct_path(t_q *qu, t_s dt, t_rooms **ht)
{
	t_rooms	*it_ht;
	t_links	*it_lnk1;
	t_links	*it_lnk2;

	it_ht = ht[hash_name(dt.end)];
	while (it_ht && ft_strcmp(dt.end, it_ht->name))
		it_ht = it_ht->next;
	while (ft_strcmp(it_ht->name, dt.st))
	{
		it_lnk1 = it_ht->links;
		// printf("%s\n", it_ht->name);
		while (it_lnk1 && it_ht->prev &&
		ft_strcmp(it_lnk1->lnk->name, it_ht->prev->name))
			it_lnk1 = it_lnk1->next;
		it_lnk1->flow += 1;
		it_lnk2 = it_lnk1->lnk->links;
		while (it_lnk2 && ft_strcmp(it_lnk2->lnk->name, it_ht->name))
			it_lnk2 = it_lnk2->next;
		it_lnk2->flow -= 1;
		it_ht = it_ht->prev;
		printf("first lnk: %s | flow: %d\n", it_lnk1->lnk->name, it_lnk1->flow);
		printf("second lnk: %s | flow: %d\n", it_lnk2->lnk->name, it_lnk2->flow);
		printf("\n");
	}
}

void		free_queue(t_q **qu)
{
	t_q *current = *qu;
	t_q *next;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*qu = NULL;
}

t_q		***alloc_grps(t_rooms **ht, t_s dt)
{
	t_q	***grps;
	int grp_count;
	int	grp;
	int	path;

	grp_count = 0;
	grp = 0;
	path = 0;
	grp_count = count_start_links(ht, dt.st);
	while (grp < grp_count)
	{
		path = 0;
		grps = (t_q ***)ft_memalloc(sizeof(t_q **));
		while (path < grp_count)
		{
			grps[grp] = (t_q **)ft_memalloc(sizeof(t_q *));
			path++;
		}
		grp++;
	}
	return (grps);
}

int		get_path(t_rooms *it_ht, t_s dt)
{
	t_links	*it_lnk;

	// it_ht = ht[hash_name(dt.st)];
	// while (it_ht && ft_strcmp(it_ht->name, dt.st))
	// 	it_ht = it_ht->next;
	// it_lnk = it_ht->links;
	// while (it_lnk && it_lnk->lnk->flag == 0 && it_lnk->flow == 0)
	// {
	// 	while (it_ht && )
	// 	{

	// 	}
	// }
	it_lnk = it_ht->links;
	while (it_lnk)
	{
		while (it_lnk->lnk->flag == 0 && it_lnk->flow == 0)
		{
			it_lnk->lnk->flag = 1;
			it_ht = it_lnk->lnk;
			//we should add the node to queue in the thirs dimension (still not allocated)
			if (!ft_strcmp(it_ht->name, dt.end))//not sure about that in case of having multiple links and we coincidently bumped in the end node first
				return (0);
			get_path(it_ht, dt);
		}
		it_lnk = it_lnk->next;
	}
	return (1);
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
			qu = init_queue(it_ht);
			t_q		*temp = qu;
			it_ht->vstd = 1;
			while (qu)
			{
				if (add_links_to_queue(&qu, qu->node, ht, dt))
				{
					correct_path(qu, dt, ht);
					// while (temp)
					// {
					// 	printf("%s\n", temp->node->name);
					// 	// ft_memdel((void **)&temp);
					// 	temp = temp->next;
					// }
					free_queue(&temp);
					// get_path()
					return (1);
				}
				qu = qu->next;
			}
			break ;
		}
	}
	return (0);
}