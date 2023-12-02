#include "game.h"

#include <stddef.h>
#include <stdio.h>

int compare_box(struct box_restriction *box, struct box_output *output)
{
    if (box->max_red < output->red_cubes)
    {
        return 0;
    }
    if (box->max_blue < output->blue_cubes)
    {
        return 0;
    }
    if (box->max_green < output->green_cubes)
    {
        return 0;
    }
    return 1;
}

void parse_output(FILE *file, struct game *game)
{
    game->outputs = realloc(game->outputs, (1 + game->output_number) * sizeof(*(game->outputs)));
    int left_tokens = 1;
    while (left_tokens)
    {
        for (int index = 0; index < 3; index++)
        {
            int number_cubes;
            char color[6] = { 0 };
            if (!fscanf(file, "%d %s", &number_cubes, color))
            {
                left_tokens = 0;
                game->output_number++;
                break;
            }
            if (!strcmp(color, "red"))
            {
                game->outputs[game->output_number]->red_cubes = number_cubes;
            }
            else if (!strcmp(color, "blue"))
            {
                game->outputs[game->output_number]->blue_cubes = number_cubes;
            }
            else
            {
                game->outputs[game->output_number]->green_cubes = number_cubes;
            }
        }
        char c = fgetc(file);
        if (c == ';')
        {
            parse_output(file, game, id);
        }
        if (c == '\n')
        {
            return;
        }
    }
}

struct game *parse_game(FILE *file)
{
    struct game *game = malloc(sizeof(struct game));
    if (!fscanf(file, "Game %d: ", &game->id)) // file is at the end
    {
        return NULL;
    }
    game->output_number = 0;
    game->outputs = NULL;
    parse_output(file, game, game->id);
    return game;
}

int main(void)
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        return 1;
    }
    struct box_restriction box = { .max_red = 12; .max_blue = 14; .max_green = 13 };
    fclose(file);
}
