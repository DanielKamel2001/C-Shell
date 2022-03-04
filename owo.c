#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char ok[] = "child says hi\n";
    FILE *fp;
    fp = fopen("child.txt", "a+");
    for (int i = 0; ok[i] != '\0'; i++)
    {
        // printf("Hello from the childs new program\n");
        // sleep(3);
        /* write to file using fputc() function */
        fputc(ok[i], fp);
    }
    fclose(fp);
    return 0;
}