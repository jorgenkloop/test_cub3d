/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graph.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:44:53 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/23 18:30:00 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_GRAPH_H
# define UTILS_GRAPH_H

# include "cub3d.h"

void	draw_rect(t_rect *rect, int	*img, int res_width);
void	draw_circle(t_circle *circle, int *img, int res_width);
void	draw_line(t_line *line, int *img, int res_width);

#endif
