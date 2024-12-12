#include "../include/so_long.h"

char	**clone_map(t_game *game)
{
	char **clone;
	int i;

	clone = malloc(game->rows * sizeof(char *));
	if (!clone)
	{
		fprintf(stderr, "Error\nMemory allocation failed for map clone.\n");
		exit(0);
	}
	i = 0;
	while (i < game->rows)
	{
		clone[i] = ft_strdup(game->map[i]);
		if (!clone[i])
		{
			fprintf(stderr, "Error\nMemory allocation failed for map clone row.\n");
			while (--i >= 0)
				free(clone[i]);
			free(clone);
			exit(0);
		}
		i++;
	}
	return (clone);
}

void	free_clone(char **clone, int rows)
{
	int i;

	i = 0;
	while (i < rows)
	{
		free(clone[i]);
		i++;
	}
	free(clone);
}

void	flood_fill(char **map, int x, int y, int rows, int cols)
{
	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, rows, cols);
	flood_fill(map, x - 1, y, rows, cols);
	flood_fill(map, x, y + 1, rows, cols);
	flood_fill(map, x, y - 1, rows, cols);
}

void	check_unreachable_collectibles(char **map, char **map_clone, int rows, int cols)
{
	int y;
	int x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map[y][x] == 'C' && map_clone[y][x] != 'V')
			{
				fprintf(stderr, "Error\nCollectible non atteignable(%d, %d).\n", x, y);
				free_clone(map_clone, rows);
				exit(0);
			}
			x++;
		}
		y++;
	}
}

void	check_unreachable_exit(char **map, char **map_clone, int rows, int cols)
{
	int y;
	int x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map[y][x] == 'E' && map_clone[y][x] != 'V')
			{
				fprintf(stderr, "Error\nSortie non atteignable.\n");
				free_clone(map_clone, rows);
				exit(0);
			}
			x++;
		}
		y++;
	}
}