/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:22:32 by yjouaoud          #+#    #+#             */
/*   Updated: 2019/12/08 14:06:14 by yjouaoud         ###   ########.fr       */
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
	hash = hash % COMPLEX;//consider making tab_size big enough so we have distinct hashes
	return (hash);
}

t_rooms				**mk_hash_tab(t_rooms *rm)
{
	int		tab_size;
	t_rooms	**hash_tab;
	t_rooms	*temp;
	int		temp_hash;
	t_rooms	*temp1;

	tab_size = rm->sz_lst;
	temp = rm;
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
				hash_tab[temp_hash] = node_dup_with_name(temp->name);
			else
			{
				temp1 = hash_tab[temp_hash];
				while (temp1->next != NULL)
					temp1 = temp1->next;
				temp1->next = node_dup_with_name(temp->name);
			}
			temp = temp->next;
		}
		free_list(&rm);
		// print_hash_tab(hash_tab, tab_size);
	}
	return (hash_tab);
}

void			print_hash_tab(t_rooms **hash_tab, int list_size)
{
	int		i;
	t_rooms	*temp;

	i = 0;
	while (i < list_size)
	{
		temp = hash_tab[i];
		ft_printf("element %d:", i);
		if (temp)
			while (temp)
			{
				ft_printf(" %s => ", temp->name);
				temp = temp->next;
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

	i = 0;
	if (line == NULL || line[0] == 'L' || line[0] == '#')
	{
		ft_printf("error because of 'L' or line is NULL\n");
		return (0);
	}
	while (line[i] && line[i] != ' ')
		i++;
	i += (line[i] == '-') ? 1 : 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (ft_strlen(line) == (size_t)i)
		return (1);
	else
		return (0);
}

void	add_link(t_rooms **element1, t_rooms **element2)
{
	// should make functions like the add_to_list for links
}

//should edit
int		parse_link(t_rooms **hash_tab, char *line)
{
	int		i;
	char	**splitted;
	t_rooms	**it_hash;
	int		hash1;
	int		hash2;

	i = 0;
	it_hash = hash_tab;
	splitted = ft_strsplit(line, '-');
	hash1 = hash_name(splitted[0]);
	hash2 = hash_name(splitted[1]);
	//temp not freed yet//took the first name and
	//after that i should compare with the list of each instance of the hashtable
	while (it_hash[hash1])
	{
		if (!(ft_strcmp(it_hash[hash1]->name, splitted[0])))
		{
			while (it_hash[hash2])
			{
				if (!(ft_strcmp(it_hash[hash2]->name, splitted[1])))
				{
					add_link(&it_hash[hash1], &it_hash[hash2]);
					break ;
				}
				it_hash[hash2] = it_hash[hash2]->next;
				if (!it_hash[hash2])
					return (0);
			}
			break ;
		}
		it_hash[hash1] = it_hash[hash1]->next;
		if (!it_hash[hash1])
			return (0);
	}
	return (1);
}
//should edit
int		get_links(t_rooms **hash_tab, char **line)
{
	if (link_is_valid(*line))
		if (!(parse_link(hash_tab, *line)))
			return (0);
	ft_strdel(line);
	while (get_next_line(0, line) > 0)
	{
		if (link_is_valid(*line))
			if (!(parse_link(hash_tab, *line)))
				return (0);
		ft_strdel(line);
	}
	//should free the line
	return (1);
}
