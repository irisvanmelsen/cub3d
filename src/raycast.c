/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 18:06:51 by mde-cloe      #+#    #+#                 */
/*   Updated: 2024/03/01 18:06:51 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//wanted to simplify but not worth effort
// static double	calc_side_dist_new(double raydir, double exact_pos, \
// 									double map_pos, double delta_dist)
// {
// 	if (raydir < 0)
// 		return ((exact_pos - map_pos) * delta_dist);
// 	else
// 		return ((map_pos + 1.0 - exact_pos) * delta_dist);
// }
static t_vector	calc_delta_dist(t_vector raydir);
static void	calc_side_dist(t_raycast_data *raycast, t_player *player);

void	raycaster(void *param)
{
	t_raycast_data	*raycast; // remove
	t_player		*player;

	raycast = (t_raycast_data *)param; //rm
	player = &raycast->data->player;
	int	x;
	double cameraX;
	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * (x / (double)WIDTH) - 1;
		raycast->mapX = player->pos.x;
		raycast->mapY = player->pos.y;
		raycast->raydir.x = player->dir.x + player->plane.x * cameraX;
		raycast->raydir.y = player->dir.y + player->plane.y * cameraX;
		raycast->delta_dist = calc_delta_dist(raycast->raydir);
		// raycast->side_dist.x = calc_side_dist_new(raycast->raydir.x,\
		// 				 player->pos.x, raycast->mapX, raycast->delta_dist.x);
		// raycast->side_dist.y = calc_side_dist_new(raycast->raydir.y,\
		// 				 player->pos.y, raycast->mapY, raycast->delta_dist.y);
		calc_side_dist(raycast, player);
		keep_lookin(raycast);
		if (raycast->side_hit == HORIZONTAL)
			raycast->perp_dist = (raycast->side_dist.x - raycast->delta_dist.x);
		else
			raycast->perp_dist = (raycast->side_dist.y - raycast->delta_dist.y);
		draw_line(raycast, x);
		x++;
	}
}

void	keep_lookin(t_raycast_data *raycast)
{
	while (1)
	{
		if (raycast->side_dist.x < raycast->side_dist.y)
		{
			raycast->side_dist.x += raycast->delta_dist.x;
			raycast->mapX += raycast->stepX;
			raycast->side_hit = HORIZONTAL;
		}
		else
		{
			raycast->side_dist.y += raycast->delta_dist.y;
			raycast->mapY += raycast->stepY;
			raycast->side_hit = VERTICAL;
		}
		if (raycast->data->map->content[raycast->mapY][raycast->mapX] == '1')
			break;
	}
}

static t_vector	calc_delta_dist(t_vector raydir) //take raydir, return delta dist
{
	t_vector	delta_dist;


	if (raydir.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs((float)1 / raydir.x);
	if (raydir.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs((float)1 / raydir.y);
	return (delta_dist);
}


//calculates the side_distance, which is the distnace from the starting pos
// to the nearest gridline, as well as checking if we need the step adjustment
static void	calc_side_dist(t_raycast_data *raycast, t_player *player) //take raydir
{
	if (raycast->raydir.x < 0)
	{
		raycast->stepX = NEGATIVE;
		raycast->side_dist.x = (player->pos.x - raycast->mapX) * raycast->delta_dist.x;
	}
	else
	{
		raycast->stepX = POSITIVE;
		raycast->side_dist.x =(raycast->mapX+ 1.0 - player->pos.x) * raycast->delta_dist.x;
	}
	if (raycast->raydir.y < 0)
	{
		raycast->stepY = NEGATIVE;
		raycast->side_dist.y =(player->pos.y - raycast->mapY) * raycast->delta_dist.y;
	}
	else
	{
		raycast->stepY = POSITIVE;
		raycast->side_dist.y =(raycast->mapY + 1.0 -  player->pos.y) * raycast->delta_dist.y;
	}
}


static int	stepdir(double raydir)
{
	if (raydir < 0)
		return (NEGATIVE);
	else
		return (POSITIVE);
}

void	draw_line(t_raycast_data *raycast, int x) //take perpdist and wall object
{
	long	draw_start;
	long	draw_end;
	int	lineheight = (int)HEIGHT / raycast->perp_dist;

	draw_start = -lineheight / 2 + HEIGHT / 2;
	if(draw_start < 0)
		draw_start = 0;
	draw_end = lineheight / 2 + HEIGHT / 2;
	if(draw_end >= HEIGHT)
	  	draw_end = HEIGHT - 1;
	while (draw_start < draw_end)
	{
		mlx_put_pixel(raycast->data->wall, x, draw_start, get_rgba(0, 255, 0, 255));
		draw_start++;
	}
}
