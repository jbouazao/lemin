/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:02:00 by yjouaoud          #+#    #+#             */
/*   Updated: 2019/12/03 16:44:57 by yjouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_t_s(t_s *dt)
{
	dt->ants = 0;
}

void	init_t_rooms(t_rooms *rm)
{
	rm->name = NULL;
	rm->next = NULL;
	rm->st = NULL;
	rm->end = NULL;
	rm->st = NULL;
}