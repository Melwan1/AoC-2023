#include <err.h>
#include <stddef.h>
#include <stdio.h>

int main(void)
{
    FILE * file = fopen("input.txt", "r");
    if (!file)
    {
        errx(1, "file could not be opened");
    }
    return 0;
}
