/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:21:26 by ahmansou          #+#    #+#             */
/*   Updated: 2019/05/08 17:28:08 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1
# define FD_LIMIT 4864

# include "./ft_printf/libft/libft.h"
# include <fcntl.h>

int	get_next_line(const int fd, char **line);

#endif
