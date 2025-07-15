#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check cli argguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open file for reading
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Couldn't open file %s\n", argv[1]);
        return 1;
    }

    // Create buffer
    BYTE buffer[BLOCK_SIZE];

    // Initialize variables
    int files_count = 0;
    bool is_new_jpg = false;
    char *file_name = malloc(8 * sizeof(char));
    FILE *destination = NULL;

    // Read card and write lost files into new files
    while (fread(&buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Check file type jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (is_new_jpg)
            {
                fclose(destination);
            }
            else
            {
                is_new_jpg = true;
            }
            // Name new file and open it
            sprintf(file_name, "%03i.jpg", files_count);
            destination = fopen(file_name, "w");

            // Check if can't create new file
            if (destination == NULL)
            {
                fclose(file);
                printf("Can't open destination %s\n", file_name);
                free(file_name);
                return 1;
            }
            // Increment new file name
            files_count++;
        }
        // Write new files
        if (is_new_jpg)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, destination);
        }
    }

    // Close opened files and free allocated memory
    fclose(file);
    fclose(destination);
    free(file_name);

    return 0;
}