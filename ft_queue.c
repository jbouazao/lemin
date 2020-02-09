/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:15:30 by jbouazao          #+#    #+#             */
/*   Updated: 2020/02/09 14:10:09 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_q			*init_queue(t_rooms *start)
{
	t_q		*start_node;

	start_node = (t_q *)ft_memalloc(sizeof(t_q));
	start_node->node = start;
	start_node->next = NULL;
	return (start_node);
}

void		add_to_queue(t_q **qu, t_links *it_lnk)
{
		t_q		*new_node;
		t_q		*it_qu;

		it_qu = *qu;
		new_node = (t_q *)ft_memalloc(sizeof(t_q));//should free if not allocated
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
		if (!ft_strcmp(dt.st, node->name) && it_lnk->flow > 0 && !it_lnk->lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			it_lnk->lnk->vstd = 1;
			it_lnk->lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && !tmp_node->prev->cap && tmp_node->cap &&
		it_lnk->flow == 2 && !it_lnk->lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			it_lnk->lnk->vstd = 1;
			it_lnk->lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && tmp_node->prev->cap && tmp_node->cap &&
		it_lnk->flow > 0 && !it_lnk->lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			it_lnk->lnk->vstd = 1;
			it_lnk->lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && !tmp_node->prev->cap && !tmp_node->cap &&
		it_lnk->flow > 0 && !it_lnk->lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			it_lnk->lnk->vstd = 1;
			it_lnk->lnk->prev = tmp_node;
		}
		else if (tmp_node->prev && tmp_node->prev->cap && !tmp_node->cap &&
		it_lnk->flow > 0 && !it_lnk->lnk->vstd)
		{
			add_to_queue(qu, it_lnk);
			it_lnk->lnk->vstd = 1;
			it_lnk->lnk->prev = tmp_node;
		}
		if (!ft_strcmp(it_lnk->lnk->name, dt.end) && it_lnk->flow > 0)
		{
			return (1);
		}
		it_lnk = it_lnk->next;
	}
	return (0);
}

void		correct_path(t_s dt, t_rooms **ht)
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
		while (it_lnk1 && it_ht->prev &&
		ft_strcmp(it_lnk1->lnk->name, it_ht->prev->name))
			it_lnk1 = it_lnk1->next;
		it_lnk1->flow += 1;
		it_lnk2 = it_lnk1->lnk->links;
		while (it_lnk2 && ft_strcmp(it_lnk2->lnk->name, it_ht->name))
			it_lnk2 = it_lnk2->next;
		it_lnk2->flow -= 1;
		it_ht = it_ht->prev;
		// printf("first lnk: %s | flow: %d\n", it_lnk1->lnk->name, it_lnk1->flow);
		// printf("second lnk: %s | flow: %d\n", it_lnk2->lnk->name, it_lnk2->flow);
		// printf("\n");
	}
}

void		free_queue(t_q **qu)
{
	t_q *current;
	t_q *next;

	current = *qu;
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
	int i;

	grp_count = 0;
	grp = 0;
	path = 0;
	grp_count = count_start_links(ht, dt.st);
	grps = (t_q ***)ft_memalloc(sizeof(t_q **) * grp_count);
	while (grp < grp_count)
	{
		grps[grp] = (t_q **)ft_memalloc(sizeof(t_q *) * (grp + 1));
		i = 0;
		while (i <= grp)
			grps[grp][i++] = NULL;
		grp++;
	}
	return (grps);
}

void	add_to_path(t_q **grps, t_rooms *node)
{
	t_q *path;
	t_q *it_grps;

	it_grps = *grps;
	path = (t_q *)ft_memalloc(sizeof(t_q));
	path->node = node;
	path->node->cap = 1;
	path->next = NULL;
	if (!it_grps)
		*grps = path;
	else
	{
		while (it_grps->next)
			it_grps = it_grps->next;
		it_grps->next = path;
	}
}

int		get_paths(t_rooms *it_ht, t_s dt, t_q **grps)
{
	t_links	*it_lnk;

	it_lnk = it_ht->links;
	while (it_lnk)
	{
		// printf("lnk: %s|flag: %d|flow: %d\n", it_lnk->lnk->name, it_lnk->lnk->flag, it_lnk->flow);
		if (it_lnk->lnk->flag == 0 && it_lnk->flow == 0)
		{
			if (ft_strcmp(it_lnk->lnk->name, dt.end))
				it_lnk->lnk->flag = 1;
			add_to_path(grps, it_lnk->lnk);
			it_ht = it_lnk->lnk;
			get_paths(it_ht, dt, grps);
			break ;
		}
		it_lnk = it_lnk->next;
	}
	return (1);
}

void		reini_rms(t_rooms **ht)
{
	int		i;
	t_rooms	*it_ht;

	i = 0;
	while (i < COMPLEX)
	{
		if (ht[i])
		{
			it_ht = ht[i];
			while (it_ht)
			{
				it_ht->flag = 0;
				it_ht->vstd = 0;
				it_ht = it_ht->next;
			}
		}
		i++;
	}
}

int			*calc_score(t_s dt, t_q ***groups, t_rooms **ht)
{
	int		num_nodes;
	int		grp_c;
	t_rooms	*it_ht;
	t_q		*it_qu;
	int		i;
	int		j;
	int		*grp_score;

	i = 0;
	num_nodes = 0;
	while (it_ht && ft_strcmp(dt.st, it_ht->name))
		it_ht = it_ht->next;
	grp_c = count_start_links(ht, dt.st);
	grp_score = (int *)ft_memalloc(sizeof(int) * grp_c);
	while (i < grp_c)
		grp_score[i++] = 10000000;
	i = 0;
	while (i < grp_c)
	{
		j = 0;
		num_nodes = 0;
		while (j <= i)//groups[i][j]
		{
			if (!groups[i][j])
				break ;
			if (groups[i][j])
			{
				it_qu = groups[i][j];
				while (it_qu && ft_strcmp(it_qu->node->name, dt.end))
					it_qu = 0 * num_nodes++ + it_qu->next;
			}
			j++;
			if (j >= i)
				grp_score[i] = ((dt.ants + num_nodes) % j == 0) ?
				(dt.ants + num_nodes) / j : ((dt.ants + num_nodes) / j) + 1;
		}
		i++;
	}
	return (grp_score);
}

void		sort_group(int *grp_score, t_q ***groups, int start_links)
{
	int 	i;
	int		min;
	int		min_i;
	int		j;
	int		count;
	int		count1;
	t_q		*swap;
	t_q		*it_path;

	i = 0;
	min = 10000000;
	while (i < start_links - 1)
	{
		if (min > grp_score[i])
		{
			min = grp_score[i];
			min_i = i;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < min_i)
	{
		j = 0;
		while (j < min_i - i)
		{
			count = 0;
			count1 = 0;
			it_path = groups[min_i][j];
			while (it_path)
			{
				count++;
				it_path = it_path->next;
			}
			it_path = groups[min_i][j + 1];
			while (it_path)
			{
				count1++;
				it_path = it_path->next;
			}
			if (count > count1)
			{
				swap = groups[min_i][j];
				groups[min_i][j] = groups[min_i][j + 1];
				groups[min_i][j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

int			fill_queue(t_s dt, t_rooms **ht)
{
	t_rooms	*it_ht;
	t_q		***groups;
	int		i;
	int		j;
	int		*grp_score;

	i = 0;
	it_ht = ht[hash_name(dt.st)];
	groups = alloc_grps(ht, dt);
	while (it_ht && ft_strcmp(dt.st, it_ht->name))
		it_ht = it_ht->next;
	if (it_ht && !ft_strcmp(dt.st, it_ht->name))
	{
		while (i < count_start_links(ht, dt.st))
		{
			t_q		*qu;
			qu = init_queue(it_ht);
			t_q		*temp = qu;
			t_q		*temp1 = qu;
			it_ht->vstd = 1;
			while (qu)
			{
				if (add_links_to_queue(&qu, qu->node, ht, dt))
				{
					j = 0;
					reini_rms(ht);
					correct_path(dt, ht);
					// while (temp)
					// {
					// 	printf("%s|flag: %d|cap: %d|vstd: %d\n", temp->node->name, temp->node->flag, temp->node->cap, temp->node->vstd);
					// 	temp = temp->next;
					// }
					// printf("\n");
					while (j <= i)
					{
						printf("[%d %d] ", i, j);
						// printf("temp->node: %s\n", temp1->node->name);
						get_paths(temp1->node, dt, &groups[i][j++]);
						t_q *tmp = groups[i][j-1];
						while (tmp)
						{
							printf("%s-", tmp->node->name);
							tmp = tmp->next;
						}
						printf("\n");
					}
					printf("\n");
					break ;
				}
				// if (i > 32)
				// {
				// 	if (!groups[i][0])
				// 		printf("%d test\n", i);
				// }
				qu = qu->next;
			}
			free_queue(&temp);
			i++;
		}
		grp_score = calc_score(dt, groups, ht);
		sort_group(grp_score, groups, count_start_links(ht, dt.st));
		i = 0;
		while (i < count_start_links(ht, dt.st))
		{
			printf("grp[%d]: %d\n", i, grp_score[i]);
			i++;
		}
		// i = 0;
		// t_q **gg = groups[3];
		// while (i < 4)
		// {
		// 	if (!gg[i])
		// 	{
		// 		printf("\ntest%d\n",i);
		// 	}
		// 	t_q *temp = gg[i];
		// 	while (temp)
		// 	{
		// 		printf("%s-", temp->node->name);
		// 		temp = temp->next;
		// 	}
		// 	printf("\n");
		// 	i++;
		// }
	}
	return (0);
}