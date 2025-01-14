#include "stdio.h"
#define LUNO_IMPL
#include "../luno/Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 800, 600, 30))
    {
        return -1;
    }

    LunoImage *image = Luno_LoadImage("assets/moon.png");

    Luno_SetClearColor((LunoColor){100, 100, 100, 255});

    LunoRect srcRect = {0, 0, image->width / 2, image->height / 2};

    LunoTimer myTimer = Luno_CreateTimer(1000);

    while (Luno_Update())
    {
        Luno_Clear();
        Luno_DrawText("Blended Text!", 50, 50, (LunoColor){255, 255, 255, 255});
        // Luno_DrawImage(image, 10, 10);
        Luno_DrawImageRect(image, 100, 100, srcRect);

        if (Luno_TimerTicked(&myTimer))
        {
            printf("Timer ticked!\n");
            printf("Milliseconds since start: %d\n", lunoMS);
        }

        if (Luno_IsMouseButtonPressed(0))
        {
            if (Luno_IsCursorVisible())
            {

                Luno_SetCursorVisibility(false);
            }
            else
            {
                Luno_SetCursorVisibility(true);
            }
            printf("Pressed");
        }
    }

    Luno_DestroyImage(image);
    Luno_Close();
    return 0;
}
