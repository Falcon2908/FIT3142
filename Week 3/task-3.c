#include <stdio.h>
#define MIN 0
#define MAX 10
int main()
{
    int i =MIN;
    while(i < MAX)
    {
        printf("In While loop: %d\n", i);
        if(i % 2 == 0)
        {
            printf("%d is an even number\n", i);
        }
        if(i % 3 == 0)
        {
            printf("%d is divisible by 3\n", i);
        }
        i++;
    }
    int j;
    printf("\n");
    for(j = MIN + 1; j <= MAX; j++)
    {
        printf("In For loop: %d\n", j);
        switch(j)
        {
            case 1:
            {
                printf("ONE\n");
                break;
            }
            case 2:
            {
                printf("TWO\n");
                break;
            }
            default:
            {
                printf("NEITHER ONE OR TWO\n");
            }
        }
    }
    return 0;
}