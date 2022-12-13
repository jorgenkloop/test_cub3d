/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:58:00 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/23 18:31:14 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/*
** Function called once per frame after the game struct has been updated. It
** draws the elements onto an img. The order is important as some overwritte
** others
** @param:	- [t_game *] root struct
*/

void	find_door(t_map map)
{
	int	x;
	int	y;

	y = -1;
	while (++y != map.height)
	{
		x = -1;
		while (++x != map.width)
		{
			if (map.grid[y][x] == 'D')
				printf("door is here %d and %d\n", x, y);
		}
	}
	
}

void	draw_door(t_game *game)
{
	find_door(game->scene.map);
	//while (game->scene.map.grid[++y][++x] != 'D')
}

void	draw(t_game *game)
{
	draw_ceilling(game);
	draw_floor(game);
	draw_walls(game);
	draw_door(game);
	draw_sprites(game);
	draw_mini_map(game);
}

/*
** Draws a big rectangle the size of the half the screen with the color
** indicated on the .cub file
** @param:	- [t_game *] root struct
** Line-by-line comments:
** @4	Y position is the top the screen
*/

void	draw_ceilling(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.width = game->scene.res.width;
	rect.height = game->scene.res.height / 2;
	rect.border_width = 0;
	rect.fill_color = game->scene.ceilling.argb;
	draw_rect(&rect, game->mlx.img.data, game->scene.res.width);
}

/*
** Draws a big rectangle the size of the half the screen with the color
** indicated on the .cub file
** @param:	- [t_game *] root struct
** Line-by-line comments:
** @4	Y position is at half of the screen
*/

void	draw_floor(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = game->scene.res.height / 2;
	rect.width = game->scene.res.width;
	rect.height = game->scene.res.height / 2;
	rect.border_width = 0;
	rect.fill_color = game->scene.floor.argb;
	draw_rect(&rect, game->mlx.img.data, game->scene.res.width);
}
