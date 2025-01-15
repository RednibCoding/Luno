#include <stdio.h>
#include <stdlib.h>

#include "embedded_font.h"

int main()
{
    // Open the file for writing in binary mode
    FILE *file = fopen("output.tga", "wb");
    if (!file)
    {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Write the byte array to the file
    size_t written = fwrite(_lunoFontImageData, 1, _lunoFontImageDataSize, file);
    if (written != _lunoFontImageDataSize)
    {
        perror("Failed to write all data to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("File successfully written with %zu bytes.\n", written);

    // Close the file
    fclose(file);
    return EXIT_SUCCESS;
}
