/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:22:32 by yjouaoud          #+#    #+#             */
/*   Updated: 2020/01/10 11:03:10 by yjouaoud         ###   ########.fr       */
/*   Updated: 2020/01/10 11:03:10 by yjouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char			*valid_room(char *line)
{
	int		i;
	char	*ret;

	i = 0;
	if (line == NULL || line[0] == 'L' || line[0] == '#')
	{
		ft_printf("error because of 'L' or line is NULL\n");
		return (NULL);
	}
	while (line[i] && line[i] != '-' && line[i] != ' ')
		i++;
	ret = ft_strsub(line, 0, i);
	i += (line[i] == ' ') ? 1 : 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	i += (line[i] == ' ') ? 1 : 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (ft_strlen(line) == (size_t)i)
		return (ret);
	else
	{
		ft_strdel(&ret);
		return (NULL);
	}
}

int				hash_name(char *name)
{
	unsigned long	hash;
	int				i;

	i = 0;
	hash = 0;
	while (name[i])
		hash = hash * 63 + name[i++];
	hash = hash % COMPLEX;
	return (hash);
}

t_rooms				**mk_hash_tab(t_rooms **rm)
{
	int		tab_size;
	t_rooms	**hash_tab;
	t_rooms	*temp;
	int		temp_hash;
	t_rooms	*temp1;

	tab_size = (*rm)->sz_lst;
	temp = (*rm);
	temp_hash = 0;
	if (!tab_size)
		return (NULL);
	else
	{
		//this whole else will be in another function
		hash_tab = (t_rooms **)ft_memalloc(sizeof(t_rooms *) * COMPLEX);
		//hash_tab is not freed yet
		int i = 0;
		while (i < COMPLEX)
		{
			hash_tab[i] = (t_rooms *)ft_memalloc(sizeof(t_rooms));
			hash_tab[i++] = NULL;
		}
		while (temp)
		{
			temp_hash = hash_name(temp->name);
			if (hash_tab[temp_hash] == NULL)
				hash_tab[temp_hash] = node_dup_with_name(temp);
			else
			{
				temp1 = hash_tab[temp_hash];
				while (temp1->next != NULL)
					temp1 = temp1->next;
				temp1->next = node_dup_with_name(temp);
			}
			temp = temp->next;
		}
		free_list(rm);
		// print_hash_tab(hash_tab, tab_size);
	}
	return (hash_tab);
}

void			print_hash_tab(t_rooms **hash_tab)
{
	int		i;
	t_rooms	*temp_hash_tab;
	t_links	*temp_links;

	i = 0;
	while (i < COMPLEX)
	{
		temp_hash_tab = hash_tab[i];
		ft_printf("element %d:", i);
		if (temp_hash_tab)
			while (temp_hash_tab)
			{
				ft_printf(" %s => ", temp_hash_tab->name);
				if (temp_hash_tab->links)
					while (temp_hash_tab->links)
					{
						ft_printf("link: %s\n", temp_hash_tab->links->link);
						temp_hash_tab->links = temp_hash_tab->links->next;
					}
				temp_hash_tab = temp_hash_tab->next;
			}
		else
			ft_printf(" NULL");
		ft_printf("\n");
		i++;
	}
}

int		link_is_valid(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (line == NULL)
	{
		ft_printf("error because of 'L' or line is NULL\n");
		return (0);
	}
	while (line[i])
	{
		count += (line[i] == '-') ? 1 : 0;
		if (line[i] == ' ' || line[i++] == '\t')
			return (0);
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

void	add_link(t_rooms **element1, t_rooms **element2)
{
	if ((*element1)->links == NULL)
		(*element1)->links = creat_lnk_lst(element2);
	else
		add_lnk_lst(element2, &(*element1)->links);
	if ((*element2)->links == NULL)
		(*element2)->links = creat_lnk_lst(element1);
	else
		add_lnk_lst(element1, &(*element2)->links);
}

//see here
int		parse_link(t_rooms **hash_tab, char *line)
{
	int		i;
	char	**splitted;
	t_rooms	*it_hash1;
	t_rooms	*it_hash2;
	int		hash1;
	int		hash2;

	i = 0;
	splitted = ft_strsplit(line, '-');
	//not freed yet
	hash1 = hash_name(splitted[0]);
	hash2 = hash_name(splitted[1]);
	it_hash1 = hash_tab[hash1];
	it_hash2 = hash_tab[hash2];
	//temp not freed yet
	while (it_hash1)
	{
		if (!(ft_strcmp(it_hash1->name, splitted[0])))
		{
			while (it_hash2)
			{
				if (!(ft_strcmp(it_hash2->name, splitted[1])))
				{
					add_link(&it_hash1, &it_hash2);
					break ;
				}
				it_hash2 = it_hash2->next;
				if (!it_hash2)
					return (0);
			}
			break ;
		}
		it_hash1 = it_hash1->next;
		if (!it_hash1)
			return (0);
	}
	return (1);
}
//see here
int		get_links(t_rooms **hash_tab, char **line)
{
	if (link_is_valid(*line))
	{
		if (!(parse_link(hash_tab, *line)))
			return (0);
	}
	else
		return (0);
	ft_strdel(line);
	while (get_next_line(0, line) > 0)
	{
		if (link_is_valid(*line))
		{
			if (!(parse_link(hash_tab, *line)))
				return (0);
		}
		else
			return (0);
		ft_strdel(line);
	}
	//should free the line
	return (1);
}
