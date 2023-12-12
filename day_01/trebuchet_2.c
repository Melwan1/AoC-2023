#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <fnmatch.h>

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int letters_are_digit(char *string)
{
    if (!fnmatch("one*", string, 0))
    {
        return 1;
    }
    if (!fnmatch("two*", string, 0))
    {
        return 2;
    }
    if (!fnmatch("three*", string, 0))
    {
        return 3;
    }
    if (!fnmatch("four*", string, 0))
    {
        return 4;
    }
    if (!fnmatch("five*", string, 0))
    {
        return 5;
    }
    if (!fnmatch("six*", string, 0))
    {
        return 6;
    }
    if (!fnmatch("seven*", string, 0))
    {
        return 7;
    }
    if (!fnmatch("eight*", string, 0))
    {
        return 8;
    }
    if (!fnmatch("nine*", string, 0))
    {
        return 9;
    }
    return 0;
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
        int letters = letters_are_digit(string + index);
        if (letters)
        {
            result += 10 *letters;
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
        int letters = letters_are_digit(string + index);
        if (letters)
        {
            result += letters;
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
