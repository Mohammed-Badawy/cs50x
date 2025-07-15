// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Name new types
typedef uint8_t BYTE;
typedef int16_t BUFFER;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    BYTE header[HEADER_SIZE];

    // Read header from source file
    fread(header, HEADER_SIZE, 1, input);

    // Write headr to destination file
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    BUFFER buffer;

    // Read samples from source
    while (fread(&buffer, sizeof(BUFFER), 1, input))
    {
        // Update volume
        buffer *= factor;

        // Write updated samples to destination file
        fwrite(&buffer, sizeof(BUFFER), 1, output);
    }
    
    // Close files
    fclose(input);
    fclose(output);
}
