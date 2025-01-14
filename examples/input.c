#include "stdio.h"
#define LUNO_IMPL
#include "../luno/Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 800, 600, 30))
        return -1;

    Luno_SetClearColor((LunoColor){20, 20, 20, 255});

    while (Luno_Update())
    {
        Luno_Clear();
        Luno_DrawText("Press left/right mouse button or space key", 50, 50, (LunoColor){255, 255, 255, 255});

        // Mouse left
        if (Luno_IsMouseButtonPressed(0))
        {
            printf("Mouse Left Pressed\n");
        }
        if (Luno_IsMouseButtonHeld(0))
        {
            printf("Mouse Left held\n");
        }
        if (Luno_IsMouseButtonReleased(0))
        {
            printf("Mouse Left released\n");
        }

        // Mouse right
        if (Luno_IsMouseButtonPressed(1))
        {
            printf("Mouse Right Pressed\n");
        }
        if (Luno_IsMouseButtonHeld(1))
        {
            printf("Mouse Right held\n");
        }
        if (Luno_IsMouseButtonReleased(1))
        {
            printf("Mouse Right released\n");
        }

        // Space key
        if (Luno_IsKeyPressed(VK_SPACE))
        {
            printf("Space Pressed\n");
        }
        if (Luno_IsKeyHeld(VK_SPACE))
        {
            printf("Space held\n");
        }
        if (Luno_IsKeyReleased(VK_SPACE))
        {
            printf("Space released\n");
        }
    }

    Luno_Close();
    return 0;
}
