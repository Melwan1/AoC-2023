#ifndef GAME_H
#define GAME_H

struct box_restriction
{
    unsigned int max_red;
    unsigned int max_blue;
    unsigned int max_green;
};

struct box_output
{
    unsigned int red_cubes;
    unsigned int blue_cubes;
    unsigned int green_cubes;
};

struct game
{
    unsigned int id;
    unsigned int output_number;
    struct box_output *outputs;
};

#endif /* !GAME_H */
