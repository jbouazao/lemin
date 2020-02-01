/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:02:00 by yjouaoud          #+#    #+#             */
/*   Updated: 2020/01/14 20:45:28 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_t_q(t_q *q)
{
	q->name = NULL;
	q->next = NULL;
}

void	init_t_s(t_s *dt)
{
	dt->st = NULL;
	dt->end = NULL;
}

void	init_t_rooms(t_rooms *rm)
{
	rm->name = NULL;
	rm->next = NULL;
	rm->prev = NULL;
}