#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int readline(char *string)
{
    if (!(*string))
    {
        return 0;
    }
    int length = strlen(string);
    int result = 0;
    for (int index = 0; index < length; index++)
    {
        if (is_digit(string[index]))
        {
            result += 10 * (string[index] - '0');
            break;
        }
    }
    for (int index = length - 1; index >= 0; index--)
    {
        if (is_digit(string[index]))
        {
            result += string[index] - '0';
            break;
        }
    }
    return result;
}

int main(void)
{
    FILE * file = fopen("input.txt", "r");
    if (!file)
    {
        errx(1, "file could not be opened");
    }
    int result = 0;
    int line = 0;
    char buffer[256] = { 0 };
    while (fgets(buffer, 256, file))
    {
        line++;
        result += readline(buffer);
    }
    printf("%d\n", result);
    return 0;
}
