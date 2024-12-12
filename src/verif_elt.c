/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-11 10:59:45 by mgarsaul          #+#    #+#             */
/*   Updated: 2024-12-11 10:59:45 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_message(int player_count, int exit_count, int collectible_count)
{
	if (player_count != 1)
	{
		fprintf(stderr, "Error\nnombre de joueurs incorrect.\n");
		exit(0);
	}
	if (exit_count < 1)
	{
		fprintf(stderr, "Error\npas de sortie.\n");
		exit(0);
	}
	if (collectible_count < 1)
	{
		fprintf(stderr, "Error\npas de collectible.\n");
		exit(0);
	}
}

void	count_map_elements(t_game *game,
	int *player_count, int *exit_count, int *collectible_count)
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
			if (tile == 'P')
				(*player_count)++;
			else if (tile == 'E')
				(*exit_count)++;
			else if (tile == 'C')
				(*collectible_count)++;
			x++;
		}
		y++;
	}
}

void	validate_map(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	//validate_walls_and_rectangle(game);
	count_map_elements(game, &player_count, &exit_count, &collectible_count);
	error_message(player_count, exit_count, collectible_count);
}

void	check_reachability(t_game *game)
{
	char	**map_clone;

	map_clone = clone_map(game);
	flood_fill(map_clone, game->player_x, game->player_y, game->rows, game->cols);
	check_unreachable_collectibles(game->map, map_clone, game->rows, game->cols);
	check_unreachable_exit(game->map, map_clone, game->rows, game->cols);
	free_clone(map_clone, game->rows);
}

void	validate_playable_map(t_game *game)
{
	validate_map(game);
	check_reachability(game);
}