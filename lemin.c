/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:45:31 by jbouazao          #+#    #+#             */
/*   Updated: 2020/01/12 11:27:43 by jbouazao         ###   ########.fr       */
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

int		get_data(t_s *dt, char *line)
{
	t_rooms	*rm;
	int		temp;
	t_rooms	**ht;

	rm = NULL;
	temp = 0;
	if (!check_num_ants(line, dt))
		return (0);
	if (!(ht = get_rms_lnks(line, &rm, dt)))
		return (0);
	// print_hash_tab(ht);
	return (1);
}

int     main(void)
{
	char    *line;
	t_s     dt;
	int		ret;

	line = NULL;
	init_t_s(&dt);
	if (!(ret = get_data(&dt, line)))
		return (0);
	return (0);
}
