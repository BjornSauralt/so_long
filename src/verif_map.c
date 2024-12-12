/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-11 11:40:24 by mgarsaul          #+#    #+#             */
/*   Updated: 2024-12-11 11:40:24 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	validate_rectangle(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->rows)
	{
		if ((int)ft_strlen(game->map[y]) != game->cols)
		{
			fprintf(stderr, "Error\nMap non rectangulaire\n");
			exit(0);
		}
		y++;
	}
}

void	validate_top_and_bottom_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->cols)
	{
		if (game->map[0][x] != '1' || game->map[game->rows - 1][x] != '1')
		{
			fprintf(stderr, "Error\nMurs non completes\n");
			exit(0);
		}
		x++;
	}
}

void	validate_side_walls(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->rows)
	{
		if (game->map[y][0] != '1' || game->map[y][game->cols - 1] != '1')
		{
			fprintf(stderr, "Error\nMurs non completes\n");
			exit(0);
		}
		y++;
	}
}

void	validate_walls_and_rectangle(t_game *game)
{
	validate_rectangle(game);
	validate_top_and_bottom_walls(game);
	validate_side_walls(game);
}
