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

int read_result(char *buffer, struct box *result_box)
{
    if (!(*buffer))
    {
        return 0;
    }
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
            if (quantity > result_box->red)
            {
                result_box->red = quantity;
            }
            next_item(&buffer);
        }

        else if (!fnmatch("blue*", buffer, 0))
        {
            if (quantity > result_box->blue)
            {
            result_box->blue = quantity;
            }
            next_item(&buffer);
        }

        else if (!fnmatch("green*", buffer, 0))
        {
            if (quantity > result_box->green)
            {
                result_box->green = quantity;
            }
            next_item(&buffer);
        }
    }
    return 1;
}

int read_game(char *buffer)
{
    int game_id = 0;
    sscanf(buffer, "Game %d", &game_id);
    while (*buffer != ':')
    {
        buffer++;
    }
    buffer += 2;
    struct box reference = { 0, 0, 0};
    int result = read_result(buffer, &reference);
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
        result = read_result(buffer, &reference);
    }
    return reference.red * reference.blue * reference.green;
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
    while (fgets(buffer, 256, file))
    {
        result += read_game(buffer);
    }
    printf("%d\n", result);
    return 0;
}
