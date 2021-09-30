#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

     if (argc < 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    FILE *pic = fopen(argv[1], "r");
    unsigned char *buff = malloc(512);
    if (buff == NULL)
    {
        return 1;
    }
    char *file = malloc(3 * sizeof(int));
    int picnumber = 0;

    while (fread(buff, sizeof(unsigned char), 512, pic) == 512)
    {
        if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] & 0xf0) == 0xe0)
        {
            if (picnumber == 1)
            {
                sprintf(file, "%03i.jpg", picnumber);
                FILE *image = fopen(file, "w");
                fwrite(buff, 1, 512, image);
                fclose(image);
            }
            else
            {
                sprintf(file, "%03i.jpg", picnumber);
                FILE *image = fopen(file, "w");
                fwrite(buff, 1, 512, image);
                fclose(image);
            }
            picnumber++;
        }
        else if (picnumber > 0 || picnumber < 0)
        {
            FILE *image = fopen(file, "a");
            fwrite(buff, 1, 512, image);
            fclose(image);
        }

    }
    free(buff);
    printf("contagem = %i\n", picnumber);
}