#include <stdio.h>
#include<ctype.h>

int main()
{
    int c, nc = 0, nl = 0, nw = 0;
    while ( (c = getchar()) != EOF )
    {
        nc++;
        if (isspace(c) || c=='\t') nw++;
        if (c == '\n') {
            nw++;
            nl++;
        }
    }
    printf("Number of characters = %d\nnumber of words = %d\nnumber of lines = %d\n", nc, nw, nl);
    return 0;
}