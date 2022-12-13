/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_game_others.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dds <dda-silv@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 08:49:19 by dda-silv          #+#    #+#             */
/*   Updated: 2021/03/01 17:07:38 by dds              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ready_game_others.h"

/*
** A lot of the setting up can only happens once the mlx_init has been done
** @param:	- [t_game *] root struct
** Line-by-line comments:
** @1	Makes sure the resolution in .cub isn't bigger than the screen res of
**		the user
** @2	The size of the mini map adapts itself to the size of the screen
** @4	Load the xpm files into the struct
*/

void	ready_game_others(t_game *game)
{
	game->scene.mini_map_tile_size = game->scene.res.width / MINIMAP_RATIO;
	set_rays(game);
	load_texture(game->mlx.mlx_ptr, &game->scene.no_tex);
	load_texture(game->mlx.mlx_ptr, &game->scene.so_tex);
	load_texture(game->mlx.mlx_ptr, &game->scene.we_tex);
	load_texture(game->mlx.mlx_ptr, &game->scene.ea_tex);
	load_texture(game->mlx.mlx_ptr, &game->scene.sprite_tex);
	load_texture(game->mlx.mlx_ptr, &game->scene.door_tex);
}

/*
** @param:	- [t_game *] root struct
** Line-by-line comments:
** @1		Number of rays = res width. Each ray is represented by a t_ray
** @4		Easier to work with radians
** @5		Distance to projection plane formula.
**			We form a rectangle between player and projection plane.
**			res.width / 2 = opposite of the triangle
**			FOV / 2 = angle of that triangle
**			adjacent = opposite / tan(FOV / 2)
**			Here the adjacent represents the distance to the projection plane
*/

//calculate the distance to the projection plane here using trigo
void	set_rays(t_game *game)
{
	game->rays.arr = malloc(game->scene.res.width * sizeof(t_ray));
	if (!game->rays.arr)
		exit(EXIT_SUCCESS);
	game->rays.view_angle = deg_to_rad(VIEW_ANGLE);
	game->rays.dist_proj_plane = (game->scene.res.width / 2)
		/ tan(game->rays.view_angle / 2);
}

void	load_texture(void *mlx, t_texture *texture)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx, texture->path,
			&texture->width, &texture->height);
	texture->img.data = (int *)mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bpp,
			&texture->img.size_l,
			&texture->img.endian);
}
