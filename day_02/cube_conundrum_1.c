#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <fnmatch.h>

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
        *buffer += 2;
    }
}

int read_result(char *buffer, struct box *reference)
{
    // returns 1 if the game is valid, 0 if the string has ended and -1 if the game is invalid

    if (!(*buffer))
    {
        return 0;
    }
    struct box result_box = { .red = 0, .blue = 0, .green = 0};
    for (int index = 0; index < 3; index++)
    {
        int quantity = 0;
        if (sscanf(buffer, "%d", &quantity))
        {
            while (*buffer != ' ')
            {
                buffer++;
            }
            buffer++;
        }
        if (!fnmatch("red*", buffer, 0))
        {
            result_box.red = quantity;
            next_item(&buffer);
        }

        else if (!fnmatch("blue*", buffer, 0))
        {
            result_box.blue = quantity;
            next_item(&buffer);
        }

        else if (!fnmatch("green*", buffer, 0))
        {
            result_box.green = quantity;
            next_item(&buffer);
        }
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
    buffer += 2;
    int result = read_result(buffer, reference);
    while (result == 1)
    {
        while (*buffer && *buffer != ';')
        {
            buffer++;
        }
        if (*buffer == ';')
        {
            buffer += 2;
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
    struct box reference = { .red = 12, .green = 13, .blue = 14 };
    while (fgets(buffer, 256, file))
    {
        result += read_game(buffer, &reference);
    }
    printf("%d\n", result);
    return 0;
}
