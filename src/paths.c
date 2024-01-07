/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iris <iris@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:58:37 by iris              #+#    #+#             */
/*   Updated: 2024/01/07 18:41:33 by iris             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	get_north_path(t_textures *texture, char *path)
{
	printf("gets into function?\n");
	if (texture->north)
	{
		printf("Double element! NO should only be used once.\n");
		return (false);
	}
	// path = "./path_to_the_north_texture";
	printf("path: %s\n", path);
	texture->north = mlx_load_png(path);
	if (!texture->north)
		return (false);
	return (true);
}

bool	get_south_path(t_textures *texture, char *path)
{
	if (texture->south)
	{
		printf("Double element! SO should only be used once.\n");
		return (false);
	}
	texture->south = mlx_load_png(path);
	if (!texture->south)
		return (false);
	return (true);
}

bool	get_west_path(t_textures *texture, char *path)
{
	if (texture->west)
	{
		printf("Double element! WE should only be used once.\n");
		return (false);
	}
	texture->west = mlx_load_png(path);
	if (!texture->west)
		return (false);
	return (true);
}

bool	get_east_path(t_textures *texture, char *path)
{
	if (texture->east)
	{
		printf("Double element! EA should only be used once.\n");
		return (false);
	}
	texture->east = mlx_load_png(path);
	if (!texture->east)
		return (false);
	return (true);
}