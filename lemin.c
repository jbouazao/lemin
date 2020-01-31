/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:45:31 by jbouazao          #+#    #+#             */
/*   Updated: 2020/01/14 22:13:49 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_num(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_num_ants(char *line, t_s *dt)
{
	if (get_next_line(0, &line) > 0)
	{
		if (!(line[0] == '\0') && is_num(line))
			dt->ants = ft_atoi(line);
		else
		{
			ft_printf("error");
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	else
		return (0);
	return (1);
}

t_rooms	**get_rms_lnks(char *line, t_rooms **rm, t_s *dt)
{
	char	c;
	char	*temp;
	t_rooms	**ht;

	ht = NULL;
	while (get_next_line(0, &line) > 0 && (c = 'r'))
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		{
			c = line[2];
			ft_strdel(&line);
			get_next_line(0, &line);
			if (c == 's')
				dt->st = valid_room(line);
			else
				dt->end = valid_room(line);
			if (!add_to_list(rm, line))
				return (ht);
		}
		else if (line[0] == '#')
			ft_printf("comment\n");
		else if ((temp = valid_room(line)))
		{
			ft_strdel(&temp);
			if (!add_to_list(rm, line))
				return (ht);
		}
		else if (link_is_valid(line))
		{
			//should edit-------------
			if (!((*rm)->sz_lst = node_list_count(*rm)))
			{
				ft_printf("list is empty\n");
				return (ht);
			}
			ht = mk_hash_tab(rm);
			if (!get_links(ht, &line))
			{
				//should free hashtable
				return (NULL);
			}
			return (ht);
			//------------------------
		}
		else
			return (ht);
		ft_strdel(&line);
	}
	return (ht);
}

t_rooms		**get_data(t_s *dt, char *line)
{
	t_rooms	*rm;
	t_rooms	**ht;

	ht = NULL;
	rm = NULL;
	if (!check_num_ants(line, dt))
		return (ht);
	if (!(ht = get_rms_lnks(line, &rm, dt)))
		return (ht);
	// print_hash_tab(ht);
	return (ht);
}

t_rooms		*sch_inht(char *name, t_rooms **ht)
{
	int		id;
	t_rooms	*it_ht;

	id = hash_name(name);
	it_ht = ht[id];
	while (it_ht && ft_strcmp(it_ht->name, name))
		it_ht = it_ht->next;
	return (it_ht);
}

int     main(void)
{
	char    *line;
	t_s     dt;
	t_rooms	**ht;
	t_rooms	*tmp_ptr;

	line = NULL;
	init_t_s(&dt);
	if (!(ht = get_data(&dt, line)))
		return (0);
	//-------------------------------------
	fill_queue(dt, ht);
	// tmp_ptr = sch_inht(dt.end, ht);

	// while (tmp_ptr)
	// {
	// 	ft_printf("%s\n", tmp_ptr->name);
	// 	tmp_ptr = tmp_ptr->prev;
	// }
	return (0);
}
