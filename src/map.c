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

void	draw_tile(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x
		* TILE_SIZE, y * TILE_SIZE);
}

void	exit_game(t_game *game)
{
	int	i;

	i = 0;
	printf("Libération de la carte...\n");
	if (game->map)
	{
		while (i < game->rows)
		{
			if (game->map[i])
			{
				free(game->map[i]);
				game->map[i] = NULL;
			}
			i++;
		}
		free(game->map);
		game->map = NULL;
		printf("Carte libérée.\n");
	}
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		printf("MiniLibX libérée.\n");
	}
	printf("Toutes les ressources libérées.\n");
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

void	exit_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (i < game->rows)
		{
			if (game->map[i])
			{
				free(game->map[i]);
				game->map[i] = NULL;
			}
			i++;
		}
		free(game->map);
		game->map = NULL;
		printf("Carte libérée.\n");
	}
}
