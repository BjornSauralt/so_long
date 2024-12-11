#include "../include/so_long.h"

void    validate_walls_and_rectangle(t_game *game)
{
    for (int y = 0; y < game->rows; y++) {
        if ((int)strlen(game->map[y]) != game->cols)
        {
            fprintf(stderr, "Error: Map is not rectangular.\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int x = 0; x < game->cols; x++)
    {
        if (game->map[0][x] != '1' || game->map[game->rows - 1][x] != '1')
        {
            fprintf(stderr, "Error: Map must be surrounded by walls (top/bottom).\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int y = 0; y < game->rows; y++)
    {
        if (game->map[y][0] != '1' || game->map[y][game->cols - 1] != '1')
        {
            fprintf(stderr, "Error: Map must be surrounded by walls (sides).\n");
            exit(EXIT_FAILURE);
        }
    }
}

void    error_message(int player_count, int exit_count, int collectible_count)
{
    if (player_count != 1)
    {
        fprintf(stderr, "Erreur, pas de joueurs.\n");
        exit(EXIT_FAILURE);
    }
    if (exit_count < 1)
    {
        fprintf(stderr, "Erreur, pas de sortie.\n");
        exit(EXIT_FAILURE);
    }
    if (collectible_count < 1)
    {
        fprintf(stderr, "Erreur, pas de collectible.\n");
        exit(EXIT_FAILURE);
    }
}

void validate_map(t_game *game)
{
    int player_count;
    int exit_count;
    int collectible_count;
    int y;
    int x;

    validate_walls_and_rectangle(game);
    player_count = 0;
    exit_count = 0;
    collectible_count = 0;
    y = 0;
    while (y < game->rows)
    {
        x = 0;
        while (x < game->cols)
        {
            char tile = game->map[y][x];
            if (tile == 'P')
                player_count++;
            else if (tile == 'E')
                exit_count++;
            else if (tile == 'C')
                collectible_count++;
            x++;
        }
        y++;
    }
    error_message(player_count, exit_count, collectible_count);
}
