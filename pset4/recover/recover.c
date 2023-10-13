#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);

        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open input file.\n");

        return 1;
    }

    int count = 0;

    FILE *outputFile = NULL;

    BYTE buffer[512];

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // buffer[3]から上位４ビットを飲みを取り出すためにビットマスク(0xf0)を使用する
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (outputFile != NULL)
            {
                fclose(outputFile);
            }

            char filename[8];

            // file名を000.jpg - 999.jpgになるようにする
            sprintf(filename, "%03d.jpg", count++);
            outputFile = fopen(filename, "w");
            if (outputFile == NULL)
            {
                fprintf(stderr, "Could not open output file.\n");
                fclose(file);
                return 1;
            }
        }

        if (outputFile != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, outputFile);
        }
    }

    if (outputFile != NULL)
    {
        fclose(outputFile);

        fclose(file);

        return 0;
    }
}