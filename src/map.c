/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-05 14:13:51 by mgarsaul          #+#    #+#             */
/*   Updated: 2024-12-05 14:13:51 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	on_destroy_bouton(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

void	draw_tile(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x
		* TILE_SIZE, y * TILE_SIZE);
}

void	exit_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->rows)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->floor_img);
	mlx_destroy_image(game->mlx, game->player_img);
	mlx_destroy_image(game->mlx, game->collectible_img);
	mlx_destroy_image(game->mlx, game->exit_img);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	char	tile;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->cols)
		{
			tile = game->map[y][x];
			draw_tile(game, x, y, game->floor_img);
			if (tile == '1')
				draw_tile(game, x, y, game->wall_img);
			else if (tile == 'P')
				draw_tile(game, x, y, game->player_img);
			else if (tile == 'C')
				draw_tile(game, x, y, game->collectible_img);
			else if (tile == 'E')
				draw_tile(game, x, y, game->exit_img);
			x++;
		}
		y++;
	}
}
