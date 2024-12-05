/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-05 14:10:03 by mgarsaul          #+#    #+#             */
/*   Updated: 2024-12-05 14:10:03 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		exit_game(game);
	if (keycode == XK_w)
		move_player(game, 0, -1);
	else if (keycode == XK_s)
		move_player(game, 0, 1);
	else if (keycode == XK_a)
		move_player(game, -1, 0);
	else if (keycode == XK_d)
		move_player(game, 1, 0);
	return (0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (new_x < 0 || new_x >= game->cols || new_y < 0 || new_y >= game->rows)
		return ;
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
	{
		printf("Vous avez reussi en %d mouvements\n", game->move_count);
		exit_game(game);
	}
	else if (game->map[new_y][new_x] == 'E')
		return ;
	game->map[game->player_y][game->player_x] = '0';
	if (game->map[new_y][new_x] != '1')
	{
		game->player_x = new_x;
		game->player_y = new_y;
		game->move_count++;
		printf("mouvement numero : %d\n", game->move_count);
	}
	game->map[new_y][new_x] = 'P';
	draw_map(game);
}
