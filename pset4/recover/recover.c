#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ........\n");

        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "........\n");

        return 1;
    }

    int count = 0;

    FILE *output_file = NULL;

    BYTE buffer[512];

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // buffer[3]から上位４ビットを飲みを取り出すためにビットマスク(0xf0)を使用する
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output_file != NULL)
            {
                fclose(output_file);
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", count++);
            output_file = fopen(filename, "w");
            if (output_file == NULL)
            {
                fprintf(stderr, "......");
                fclose(file);
                return 1;
            }
        }

        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, output_file);
        }
    }
    if (output_file != NULL)
    {
        fclose(output_file);

        fclose(file);

        return 0;
    }
}