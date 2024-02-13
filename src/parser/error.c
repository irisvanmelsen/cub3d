/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-mel <ivan-mel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 22:12:03 by iris          #+#    #+#                 */
/*   Updated: 2024/02/12 14:37:36 by ivan-mel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_error_name(t_error error)
{
	static char	*str[] = {\
		[ERROR_CHARACTER] = "Invalid Amount of Positions!\n", \
		[ERROR_MLX] = "MLX Initialisation has Failed!\n", \
		[ERROR_IMAGE] = "MLX Image Initialisation has Failed!\n", \
		[ERROR_ALLOCATION] = "Allocation has Failed!\n"};

	return (str[error]);
}

int	print_error(char *str)
{
	write (STDERR_FILENO, str, ft_strlen(str));
	return (EXIT_FAILURE);
}
