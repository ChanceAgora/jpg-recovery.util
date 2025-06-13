#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Ensure only one file was given
    if (argc != 2)
    {
        printf("Recover: Please provide a file\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        printf("Recover: Error file not found: %s\n", argv[1]);
        return 2;
    }

    int fileNum = 0; // Track the number of files created to number them correctly
    char fileName[16];
    uint8_t c[512];
    FILE *writeData = NULL;

    while (!feof(file))
    {
        fread(c, 512, 1, file);

        // Check for jpg file signature
        if (c[0] == 0xff &&
            c[1] == 0xd8 &&
            c[2] == 0xff &&
            (c[3] >= 0xe0 && c[3] <= 0xef))
        {
            // Write to a new file for the new jpg signature
            fclose(writeData);

            sprintf(fileName, "%03d.jpg", ++fileNum);
            writeData = fopen(fileName, "wb");

            if (writeData == NULL)
            {
                printf("File write error\n");
                fclose(file);
                return 3;
            }
            fwrite(c, 512, 1, writeData);
        }
        else if (writeData != NULL)
        {
            // Continue writing to the currently open jpg
            fwrite(c, 512, 1, writeData);
        }
    }

    printf("Copying completed successfully\n");

    // Close files
    fclose(file);
    fclose(writeData);
    return 0;
}
