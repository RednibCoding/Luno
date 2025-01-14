#include <stdio.h>
#include <stdlib.h>

#include "embedded_font.h"

int main()
{
    // Open the file for writing in binary mode
    FILE *file = fopen("output.png", "wb");
    if (!file)
    {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Write the byte array to the file
    size_t written = fwrite(_lunoFontPngData, 1, _lunoFontPngDataSize, file);
    if (written != _lunoFontPngDataSize)
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
