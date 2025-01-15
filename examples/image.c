#include "stdio.h"
#define LUNO_IMPL
#include "../luno/Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 800, 600, 30))
    {
        return -1;
    }

    LunoImage *image = Luno_LoadImage("assets/moon.tga");

    Luno_SetClearColor((LunoColor){20, 20, 20, 255});

    LunoRect srcRect = {0, 0, image->width / 2, image->height / 2};

    LunoColor color = Luno_GetPixel(image, 76, 178);
    printf("Pixel color: %d %d %d %d", color.r, color.g, color.b, color.a);

    while (Luno_Update())
    {
        Luno_Clear();
        Luno_DrawImage(image, 5, 5);
        Luno_DrawImageRect(image, 450, 5, srcRect);
    }

    Luno_DestroyImage(image);
    Luno_Close();
    return 0;
}
