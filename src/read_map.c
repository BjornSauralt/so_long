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
		exit(0);
	}
	game->rows = 0;
	game->cols = 0;
	line = get_next_line(fd);
	while ((line))
	{
		line = get_next_line(fd);
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
		fprintf(stderr, "Error\nEchec allocation memoire pour la carte.\n");
		exit(0);
	}
}

void	fill_map_line(char *line, t_game *game, int row)
{
	game->map[row] = malloc((game->cols + 1) * sizeof(char));
	if (!game->map[row])
	{
		fprintf(stderr, "Error\nEchec allocation memoire pour ligne.\n");
		exit(0);
	}
	strncpy(game->map[row], line, game->cols);
	game->map[row][game->cols] = '\0';
}

void	fill_map_from_file(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error\nReouverture du fichier impossible %s\n", file);
		exit(0);
	}
	i = 0;
	while (i < game->rows)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		fill_map_line(line, game, i);
		free(line);
		i++;
	}
	close(fd);
}

void	initialize_game_elements(t_game *game)
{
	int	y;
	int	x;

	y = 0;
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
}
