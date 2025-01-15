#include "stdio.h"
#define LUNO_IMPL
#include "../luno/Luno.h"

// #define RC_TGA_IMPL
// #include "rc_tga.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Load TGA image
    int tgaW = 0;
    int tgaH = 0;
    unsigned char *pixelsTga = rc_load_tga("assets/moon.tga", &tgaW, &tgaH);
    if (!pixelsTga)
    {
        fprintf(stderr, "Failed to load TGA file.\n");
        return -1;
    }

    LunoImage *image = Luno_LoadImage("assets/moon.tga");

    if (!image)
        printf("No image!\n");

    if (!Luno_Create("Luno Window", 600, 600, 30))
        return 0;

    while (Luno_Update())
    {
        Luno_Clear();

        Luno_DrawImage(image, 20, 20);
    }

    // Clean up
    Luno_DestroyImage(image);
    Luno_Close();

    return 0;
}
