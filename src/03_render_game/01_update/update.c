/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:31:36 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/23 18:31:46 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

/*
** Each frame, we check if the values of our struct have to be update
** because of user interactions (mouse motions or key presses). For rays and
** sprites, the values are recalculated whether the player moves or not so room
** for improvement here
** @param:	- [t_game *] root struct
*/

// void	update_door_visibility(t_game *game, t_door *door)
// {
// 	double	delta_angle;
// 	double	angle;
// 	double	dx;
// 	double	dy;
	
// 	//printf("doorx %d and doory %d player x %f player y %f\t", door->x, door->y, game->player.x, game->player.y);
// 	dx = door->x - game->player.x;
// 	dy = door->y - game->player.y;
// 	//printf("dy %f and dx %f\t", dy, dx);
// 	angle = atan2(dy, dx) - game->player.rotation_angle;
// 	//printf("rotation angle %f and orientation %f dydx %f\t", rad_to_deg(angle), door->orientation, atan2(dy, dx));
// 	angle = normalize_radian(angle);
// 	door->rotation_angle = angle;
// 	printf("%f\t", rad_to_deg(door->rotation_angle));
// 	delta_angle = angle + game->player.rotation_angle;
// 	delta_angle = game->player.rotation_angle - delta_angle;
// 	//door->rotation_angle = atan2(-dy, dx);
// 	// if (door->rotation_angle < 0)
// 	// 	door->rotation_angle += 2 * M_PI;
// 	// else if (door->rotation_angle > (2 * M_PI))
// 	// 	door->rotation_angle -= 2 * M_PI;
// 	//door->rotation_angle = normalize_radian(door->rotation_angle);
// 	//printf("after %f\t", rad_to_deg(door->rotation_angle));
// 	//printf("rotation angle2 %f\n", rad_to_deg(angle));
// 	// delta_angle = angle + game->player.rotation_angle;
// 	// delta_angle = game->player.rotation_angle - delta_angle;
// 	//printf("delta angle %f and angle %f\n", delta_angle, angle);
// 	if (delta_angle < -M_PI)
// 		delta_angle += 2.0 * M_PI;
// 	if (delta_angle > M_PI)
// 		delta_angle -= 2.0 * M_PI;
// 	delta_angle = fabs(delta_angle);
// 	//printf("delta_angle %f\t", delta_angle);
// 	if (delta_angle < game->rays.view_angle / 2 + deg_to_rad(4))
// 		door->is_visible = 1;
// 	else
// 		door->is_visible = 0;
// 	//printf("is visible %d\t", door->is_visible);
// }

// void	update_door_distance(t_game *game, t_door *door)
// {
// 	double		dx;
// 	double		dy;

// 	dx = door->x - game->player.x;
// 	dy = door->y - game->player.y;
// 	door->distance = sqrt(pow(dx, 2) + pow(dy, 2));
// }

// void	update_door(t_game *game)
// {
// 	int		i;
// 	t_door	*door;

// 	i = -1;
// 	while (++i < game->scene.total_doors)
// 	{
// 		door = &game->scene.doors[i];
// 		update_door_visibility(game, door);
// 		update_door_distance(game, door);
// 	}
// }

void	update(t_game *game)
{
	//if (game->scene.map.grid[(int)game->player.y][(int)game->player.x - 1] == 'D' && game->scene.map.grid[(int)game->player.y - 1][(int)game->player.x] == 'D')
	//	printf("angle %f and %f and %f\n", rad_to_deg(game->player.rotation_angle), game->player.x, game->player.y);
	update_player_position(&game->player, game->scene.map.grid);
	update_player_orientation(&game->player);
	update_rays(game);
	update_sprites(game);
	//update_door(game);
}

/*
** Updating the player position based on the WASD movement
** @param:	- [t_player *] player struct
**			- [char **] map formatted in a 2d array of chars
** Line-by-line comments:
** @4-5		Case: the user hasn't pressed WASD
** @6-7		Case: moving front (i.e. W key press). Default case as if other key
**			than W pressed one or both values will get overwritten
** @8-9		Case: moving back (i.e. S key press). Same orientation but the
**			opposite way
** @10-14	Case: moving left (i.e. A key press). We are looking right and
**			moving backward
** @15-16	Case: moving right (i.e. D key press). We are looking right and
**			moving forward
** @17-18	Updating the positions of the player. Here move_step = hypotenuse
**			because we know the distance to cross
** @17		Adding to x the adjacent (go left...)
** @18		Adding to y the opposite (...and up)
** @19-23	If the new position is in a wall, then we go back to previous
**			position
*/

static int	check_corners(t_player *player, char **grid, int b_x, int b_y)
{
	if (player->rotation_angle > 0 && player->rotation_angle < (0.5 * M_PI))
	{
		if ((b_x == (int)player->x - 1 && b_y == (int)player->y - 1) && (grid[(int)player->y][(int)player->x - 1] == 'D' && grid[(int)player->y - 1][(int)player->x] == 'D'))
			return (1);
	}
	if (player->rotation_angle > (0.5 * M_PI) && player->rotation_angle < M_PI)
	{
		if ((b_x == (int)player->x + 1 && b_y == (int)player->y - 1) && (grid[(int)player->y][(int)player->x + 1] == 'D' && grid[(int)player->y - 1][(int)player->x] == 'D'))
			return (1);
	}
	if (player->rotation_angle > M_PI && player->rotation_angle < (M_PI * 1.5))
	{
		if ((b_x == (int)player->x + 1 && b_y == (int)player->y + 1) && (grid[(int)player->y][(int)player->x + 1] == 'D' && grid[(int)player->y + 1][(int)player->x] == 'D'))
			return (1);
	}
	if (player->rotation_angle > (1.5 * M_PI) && player->rotation_angle < (2 * M_PI))
	{
		if ((b_x == (int)player->x - 1 && b_y == (int)player->y + 1) && (grid[(int)player->y][(int)player->x - 1] == 'D' && grid[(int)player->y + 1][(int)player->x] == 'D'))
			return (1);
	}
	return (0);
}

void	update_player_position(t_player *player, char **grid)
{
	double	move_step;
	double	rotation;
	int		b_x;
	int		b_y;

	b_x = (int)player->x;
	b_y = (int)player->y;
	if (player->walk_direction == 0)
		return ;
	move_step = player->move_speed;
	rotation = player->rotation_angle;
	if (player->walk_direction == 's')
		move_step = (-1) * player->move_speed;
	else if (player->walk_direction == 'a')
	{
		move_step = (-1) * player->move_speed;
		rotation = player->rotation_angle + deg_to_rad(90);
	}
	else if (player->walk_direction == 'd')
		rotation = player->rotation_angle + deg_to_rad(90);
	player->x += cos(rotation) * move_step;
	player->y += sin(rotation) * move_step;
	if (player->door_status == 1 && (ft_strchr("12D", grid[(int)player->y][(int)player->x]) || check_corners(player, grid, b_x, b_y)))
	{
		player->x -= cos(rotation) * move_step;
		player->y -= sin(rotation) * move_step;
	}
	else if (player->door_status == 0 && ft_strchr("12", grid[(int)player->y][(int)player->x]))
	{
		player->x -= cos(rotation) * move_step;
		player->y -= sin(rotation) * move_step;
	}
}

/*
** Update player rotation based on the left / right arrow clicks
** @param:	- [t_player *] player
** Line-by-line comments:
** @3-4		The player isn't pressing in left / right arrow
** @5		The width of the rotation depends on the rotation speed
** 			The turn_direction is -1 if left and +1 if right
*/

void	update_player_orientation(t_player *player)
{
	double	rotation;

	if (player->turn_direction == 0)
		return ;
	rotation = player->turn_direction * player->rotation_speed;
	player->rotation_angle += rotation;
	//printf("angle %f\n", rad_to_deg(player->rotation_angle));
}

/*
** Update all the rays being casted even if no movement
** @param:	- [t_game *] root struct
** Line-by-line comments:
** @4		Get the left-most ray's angle. For instance, for a 60° degree
**			view angle and a player facing north (i.e. 270°)
**			ray_angle = 270 - 60 / 2 = 240
**			Example here in degree but values are in radians
** @6		Number of rays casted = resolution's width
** @10		We increment the ray angle by simpliting the view_angle by the
**			number of rays casted (e.g. 60° / 1920)
*/

void	update_rays(t_game *game)
{
	double	ray_angle;
	int		i;

	game->scene.map.door_s = game->player.door_status;
	//if player is looking at 270 deg, ray angle is 240 deg
	ray_angle = game->player.rotation_angle - game->rays.view_angle / 2;
	i = -1;
	//loops until ray angle is 300 deg (if player is looking at 270 deg)
	//so whole 60 deg FOV is looped from 240 to 300
	while (++i < game->scene.res.width)
	{
		game->rays.arr[i].angle = ray_angle;
		cast_ray(&game->rays.arr[i], &game->scene.map, &game->player);
		ray_angle += game->rays.view_angle / game->scene.res.width;
	}
}

/*
** Update sprite array even if no movement
** @param:	- [t_game *] root struct
** Line-by-line comments:
** @8		Gives the sprite the necessary angle to be facing the player
** @9		Determines if the sprite should be visible or not. Here only based
**			on the field of view. So even if being a wall, it will be deemed as
**			visible. Later, we'll check for that
** @10		Gives the distance between the sprite and the player
** @12		Orders the sprites from farther to closer. Sprites needs to be
**			printed in that order because the closer goes on top the farther
**			pixel-wise
*/

void	update_sprites(t_game *game)
{
	int			i;
	t_sprite	*sprite;

	i = -1;
	while (++i < game->scene.total_sprites)
	{
		sprite = &game->scene.sprites[i];
		update_sprite_angle(game, sprite);
		update_sprite_visibility(game, sprite);
		update_sprite_distance(game, sprite);
	}
	update_sprites_order(game, game->scene.sprites);
}
