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

// void	find_door(t_map map)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y != map.height)
// 	{
// 		x = -1;
// 		while (++x != map.width)
// 		{
// 			if (map.grid[y][x] == 'D')
// 				printf("door is here %d and %d\n", x, y);
// 		}
// 	}
	
// }

void	draw_door_strip(t_rect *rect, t_game *game, int x_tex, int x_img)
{
	double	step;
	double	tex_pos;
	int		y;
	int		y_tex;
	int		color;

	step = 1.0 * rect->door->tex->height / rect->height;
	tex_pos = (rect->y - game->scene.res.height / 2 + rect->height / 2) * step;
	y = -1;
	while (++y < rect->height && y < game->scene.res.height)
	{
		y_tex = (int)tex_pos & (rect->door->tex->height - 1);
		tex_pos += step;
		color = rect->door->tex->img.data[y_tex
			* rect->door->tex->height + x_tex];
		if (color < 0)
			continue ;
		game->mlx.img.data[(rect->y * game->scene.res.width)
			+ (y * game->scene.res.width) + x_img] = color;
	}
}

int		get_y_door_position(t_game *game, double door_height)
{
	int	center_screen;
	int	center_door;
	int	y;

	center_screen = game->scene.res.height / 2;
	center_door = door_height / 2;
	y = center_screen - center_door;
	if (y < 0)
		y = 0;
	return (y);
}

// int		get_x_door_position(t_game *game,
// 							t_door *door,
// 							double door_width)
// {
// 	double	center_door;
// 	int		center_screen;
// 	double	begin_door;

// 	center_screen = game->scene.res.width / 2;
// 	center_door = tan(door->rotation_angle) * game->rays.dist_proj_plane;
// 	begin_door = center_screen + center_door - door_width / 2;
// 	return (begin_door);
// }

double	get_door_height(t_game *game, double distance)
{
	double	scaled_distance;
	double	door_height;

	scaled_distance = distance * SCALE;
	door_height = (SCALE / scaled_distance) * game->rays.dist_proj_plane;
	return (door_height);
}

void	draw_single_door(t_game *game, t_door *door)
{
	t_rect	rect;
	double	column_width;
	int		i;
	int		j;
	int		pos_x;

	rect.height = get_door_height(game, door->distance);
	rect.y = get_y_door_position(game, rect.height);
	rect.door = door;
	column_width = rect.height / door->tex->height;
	i = -1;
	while (++i < door->tex->width)
	{
		j = -1;
		while (++j < column_width)
		{
			rect.x = i;
			pos_x = (int)(rect.x + (i - 1) * column_width + j);
			if (pos_x >= 0 && pos_x <= game->scene.res.width - 1
				&& door->distance < game->rays.arr[pos_x].size)
			{
				draw_door_strip(&rect, game, i, pos_x);
			}
		}
	}
}

void	draw_door(t_game *game)
{
	int		i;
	t_door	*door;

	i = -1;
	while (++i < game->scene.total_doors)
	{
		door = &game->scene.doors[i];
		if (door->is_visible)
			draw_single_door(game, &game->scene.doors[i]);
	}
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
