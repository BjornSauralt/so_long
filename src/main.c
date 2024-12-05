/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-03 12:02:45 by mgarsaul          #+#    #+#             */
/*   Updated: 2024-12-03 12:02:45 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**read_map(const char *file, t_game *game)
{
	FILE	*fp;
	char	buffer[1024];
	int		i;
	int		y;
	int		x;

	i = 0;
	y = 0;
	fp = fopen(file, "r");
	if (!fp)
	{
		fprintf(stderr, "Erreur : ouverture du fichier impossible %s\n", file);
		exit(0);
	}
	game->rows = 0;
	game->cols = 0;
	while (fgets(buffer, sizeof(buffer), fp))
	{
		if (game->cols == 0)
			game->cols = strlen(buffer) - 1;
		game->rows++;
	}
	rewind(fp);
	game->map = malloc(game->rows * sizeof(char *));
	while (i < game->rows)
	{
		game->map[i] = malloc((game->cols + 1) * sizeof(char));
		fgets(game->map[i], game->cols + 2, fp);
		game->map[i][game->cols] = '\0';
		i++;
	}
	fclose(fp);
	game->collectibles = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->cols)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map[y][x] == 'C')
			{
				game->collectibles++;
			}
			x++;
		}
		y++;
	}
	return (game->map);
}

void	init_game(t_game *game, const char *map_file)
{
	game->move_count = 0;
	game->map = read_map(map_file, game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->cols * TILE_SIZE,
			game->rows * TILE_SIZE, "so_long");
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"assets/arbres.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"assets/terre.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game->player_img = mlx_xpm_file_to_image(game->mlx,
			"assets/guts.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"assets/behelit.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game->exit_img = mlx_xpm_file_to_image(game->mlx,
			"assets/skull_knight.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	if (!game->wall_img || !game->floor_img || !game->player_img
		|| !game->collectible_img || !game->exit_img)
	{
		fprintf(stderr, "Erreur de chargement des images\n");
		exit_game(game);
	}
	draw_map(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	init_game(&game, argv[1]);
	mlx_hook(game.win, 2, 1L << 0, on_keypress, &game);
	mlx_hook(game.win, DestroyNotify,
		StructureNotifyMask, &on_destroy_bouton, &game);
	mlx_loop(game.mlx);
	return (0);
}
