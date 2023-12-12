#include <err.h>
#include <stddef.h>
#include <stdio.h>

struct box
{
    int blue;
    int red;
    int green;
};

void next_item(char **buffer)
{
    while(**buffer != ',' && **buffer != ';' && **buffer)
    {
        (*buffer)++;
    }
    if (**buffer == ',')
    {
        (*buffer)++;
    }
}

int read_result(char *buffer, struct box *reference)
{
    // returns 1 if the game is valid, 0 if the string has ended and -1 if the game is invalid

    if (!(*buffer[0]))
    {
        return 0;
    }
    struct box result_box = { .red = 0, .blue = 0, .green = 0};
    if (sscanf(buffer, "%d red", &(result_box.red)))
    {
        next_item(&buffer);
    }

    if (sscanf(buffer, "%d blue", &(result_box.blue)))
    {
        next_item(&buffer);
    }

    if (sscanf(buffer, "%d green", &(result_box.green)))
    {
        next_item(&buffer);
    }
    if (result_box.red > reference->red)
    {
        return -1;
    }

    if (result_box.blue > reference->blue)
    {
        return -1;
    }

    if (result_box.green > reference->green)
    {
        return -1;
    }
    return 1;
}

int read_game(char *buffer, struct box *reference)
{
    int game_id = 0;
    sscanf(buffer, "Game %d", &game_id);
    while (*buffer != ':')
    {
        buffer++;
    }
    int result = read_result(buffer, reference);
    while (result == 1)
    {
        while (*buffer && *buffer != ';')
        {
            buffer++;
        }
        if (*buffer == ';')
        {
            buffer++;
        }
        result = read_result(buffer, reference);
    }
    if (!result)
    {
        return game_id;
    }
    return 0;
}

int main(void)
{
    FILE * file = fopen("input.txt", "r");
    if (!file)
    {
        errx(1, "file could not be opened");
    }
    char buffer[256];
    int result = 0;
    struct box reference = { .red = 12, .blue = 13, .green = 14 };
    while (fgets(buffer, 256, file))
    {
        result += read_game(buffer, &reference);
    }
    printf("%d\n", result);
    return 0;
}
