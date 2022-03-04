#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Hello from the childs new program\n");
    char ok[] = "child says hi\n";
    FILE *fp;
    fp = fopen("child.txt", "a+");
    for (int i = 0; ok[i] != '\n'; i++)
    {
        /* write to file using fputc() function */
        fputc(ok[i], fp);
    }
    fclose(fp);
    return 0;
}