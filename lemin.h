/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:45:35 by jbouazao          #+#    #+#             */
/*   Updated: 2019/12/08 14:00:23 by yjouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "./ft_printf/src/ft_printf.h"
# include "get_next_line.h"
# define COMPLEX 10000

typedef struct		s_s
{
	int				ants;
}					t_s;

typedef struct		s_links
{
	char			*link;
	struct s_links	*next;
}					t_links;

typedef struct		s_rooms
{
	char			*name;
	struct s_rooms	*next;
	char			rm;
	int				sz_lst;
	t_links			*links;

}					t_rooms;

/*
** LIST
*/
void				prnt_rms_lst(t_rooms *rm);
int					add_to_list(t_rooms **rm, char *line, char c);
void				free_list(t_rooms **rm);
int					node_list_count(t_rooms *rm);
t_rooms				*node_dup_with_name(char *name);
/*
** COMMENT
*/
int					check_num_ants(char *line, t_s *dt);
int					get_data(t_s *dt, char *line);
int					is_num(char *line);
void				init_t_rooms(t_rooms *rm);
int					get_rms_lnks(char *line, t_rooms **rm);
char				*valid_room(char *line);
int					link_is_valid(char *line);
int					get_links(t_rooms **hash_tab, char **line);
/*
** HASH_TABLE
*/
int					hash_name(char *name);
t_rooms				**mk_hash_tab(t_rooms *rm);
void				print_hash_tab(t_rooms **hash_tab, int list_size);
int					parse_link(t_rooms **hash_tab, char *line);
void				add_link(t_rooms **element1, t_rooms **element2);
#endif
