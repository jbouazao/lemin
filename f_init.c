/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:02:00 by yjouaoud          #+#    #+#             */
/*   Updated: 2020/01/12 11:11:26 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_t_s(t_s *dt)
{
	dt->st = NULL;
	dt->end = NULL;
}

void	init_t_rooms(t_rooms *rm)
{
	rm->name = NULL;
	rm->next = NULL;
}