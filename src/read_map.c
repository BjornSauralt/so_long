/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-11 12:20:43 by mgarsaul          #+#    #+#             */
/*   Updated: 2024-12-11 12:20:43 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	calculate_map_dimensions(const char *file, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error\nOuverture du fichier impossible %s\n", file);
		exit(EXIT_FAILURE);
	}

	game->rows = 0;
	game->cols = 0;
	while ((line = get_next_line(fd)))
	{
		if (game->cols == 0)
			game->cols = strlen(line) - (line[strlen(line) - 1] == '\n');
		game->rows++;
		free(line);
	}
	close(fd);
}

void	allocate_map_memory(t_game *game)
{
	game->map = malloc(game->rows * sizeof(char *));
	if (!game->map)
	{
		fprintf(stderr, "Error\nÉchec allocation mémoire pour la carte.\n");
		exit(EXIT_FAILURE);
	}
}

void	fill_map_from_file(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		i = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error\nRéouverture du fichier impossible %s\n", file);
		exit(EXIT_FAILURE);
	}

	while ((line = get_next_line(fd)) && i < game->rows)
	{
		game->map[i] = malloc((game->cols + 1) * sizeof(char));
		if (!game->map[i])
		{
			fprintf(stderr, "Error\nÉchec allocation mémoire pour ligne.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(game->map[i], line, game->cols);
		game->map[i][game->cols] = '\0';
		free(line);
		i++;
	}
	close(fd);
}

void	initialize_game_elements(t_game *game)
{
	game->collectibles = 0;
	for (int y = 0; y < game->rows; y++)
	{
		for (int x = 0; x < game->cols; x++)
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
		}
	}
}