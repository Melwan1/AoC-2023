#include "game.h"

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
