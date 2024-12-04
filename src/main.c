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

/*int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}*/

char	**read_map(const char *file, int *rows, int *cols)
{
	FILE	*fp;

	fp = fopen(file, "r");
	if (!fp)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	char **map = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	*rows = 0;

	while ((nread = getline(&line, &len, fp)) != -1)
	{
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (*rows == 0)
			*cols = nread - 1;

		map = realloc(map, (*rows + 1) * sizeof(char *));
		if (!map)
		{
			perror("Error reallocating memory");
			exit(EXIT_FAILURE);
		}

		map[*rows] = strdup(line);
		if (!map[*rows])
		{
			perror("Error duplicating line");
			exit(EXIT_FAILURE);
		}

		(*rows)++;
	}

	free(line);
	fclose(fp);
	return (map);
}

void	draw_tile(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
}

/*int	on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_d)
		dep_droite(data);
	if (keysym == XK_s)
		dep_bas(data);
	if (keysym == XK_a)
		dep_gauche(data);
	if (keysym == XK_w)
		dep_haut(data);
	return (0);
}*/

void draw_map(t_game *game) {
	for (int y = 0; y < game->rows; y++) {
		for (int x = 0; x < game->cols; x++) {
			char tile = game->map[y][x];
			printf("Tile at (%d, %d): %c\n", x, y, tile);

			if (tile == '1')
				draw_tile(game, x, y, game->wall_img);
			else if (tile == '0')
				draw_tile(game, x, y, game->floor_img);
			else if (tile == 'P')
				draw_tile(game, x, y, game->player_img);
			else if (tile == 'C')
				draw_tile(game, x, y, game->collectible_img);
			else if (tile == 'E')
				draw_tile(game, x, y, game->exit_img);
		}
	}
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	game.map = read_map(argv[1], &game.rows, &game.cols);
	if (!game.map || game.rows == 0 || game.cols == 0)
	{
		fprintf(stderr, "Invalid map\n");
		return (EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		fprintf(stderr, "Error initializing MLX\n");
		return (EXIT_FAILURE);
	}
	game.win = mlx_new_window(game.mlx, game.cols * TILE_SIZE, game.rows * TILE_SIZE, "so_long");
	if (!game.win)
	{
		fprintf(stderr, "Error creating window\n");
		return (EXIT_FAILURE);
	}

	game.wall_img = mlx_xpm_file_to_image(game.mlx, "assets/arbres.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game.floor_img = mlx_xpm_file_to_image(game.mlx, "assets/terre.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game.player_img = mlx_xpm_file_to_image(game.mlx, "assets/guts.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game.collectible_img = mlx_xpm_file_to_image(game.mlx, "assets/behelit.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	game.exit_img = mlx_xpm_file_to_image(game.mlx, "assets/skull_knight.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	if (!game.wall_img || !game.floor_img || !game.player_img || !game.collectible_img || !game.exit_img)
	{
		fprintf(stderr, "Error loading images\n");
		return (EXIT_FAILURE);
	}
	draw_map(&game);
	mlx_loop(game.mlx);

	return (0);
}
