/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:45:31 by jbouazao          #+#    #+#             */
/*   Updated: 2019/12/08 13:53:34 by yjouaoud         ###   ########.fr       */
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

int		get_rms_lnks(char *line, t_rooms **rm)
{
	char	c;
	char	*temp;

	while (get_next_line(0, &line) > 0 && (c = 'r'))
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			if (!add_to_list(rm, line, c = line[2]))
				return (0);
		}
		else if (line[0] == '#')
			ft_printf("comment\n");
		else if ((temp = valid_room(line)))
		{
			ft_strdel(&temp);
			if (!add_to_list(rm, line, c))
				return (0);
		}
		else if (link_is_valid(line))
		{
			//should edit-------------
			if (!((*rm)->sz_lst = node_list_count(*rm)))
			{
				ft_printf("list is empty\n");
				return (0);
			}
			get_links(mk_hash_tab(*rm), &line);
			return (1);
			//------------------------
		}
		else
			return (0);
		ft_strdel(&line);
	}
	return (1);
}

// int		get_rms_lnks1(char *line, t_rooms **rm)
// {
// 	char	c;
// 	char	*temp;

// 	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
// 	{
// 		ft_strdel(&line);
// 		get_next_line(0, &line);
// 		if (!add_to_list(rm, line, c = line[2]))
// 			return (0);
// 	}
// 	else if (line[0] == '#')
// 		ft_printf("comment\n");
// 	else if ((temp = valid_room(line)))
// 	{
// 		ft_strdel(&temp);
// 		if (!add_to_list(rm, line, c))
// 			return (0);
// 	}
// 	return (1);
// }

// int		get_rms_lnks2(char *line, t_rooms **rm)
// {
// 	if (valid_link)
// 	{

// 	}
// 	else
// 		return(0);
// }

int		get_data(t_s *dt, char *line)
{
	t_rooms	*rm;
	int		temp;

	rm = NULL;
	temp = 0;
	if (!check_num_ants(line, dt))
		return (0);
	if (!get_rms_lnks(line, &rm))
		return (0);
	//-----------------------------
	// while (get_next_line(0, &line) > 0)
	// {
	// 	if (!get_rms_lnks(line, &rm))
	// 	{
	// 		ft_strdel(&line);
	// 		break ;
	// 	}
	// 	if (!links())
	// 	{
	// 		ft_strdel(&line);
	// 		break ;
	// 	}
	// 	ft_strdel(&line);
	// }
	//-----------------------------
	ft_printf("count1 = %d\n", node_list_count(rm));
	return (1);
}

int     main(void)
{
	char    *line;
	t_s     dt;
	int		ret;

	line = NULL;
	if (!(ret = get_data(&dt, line)))
		return (0);
	return (0);
}
