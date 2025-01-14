#include "stdio.h"

#define LUNO_IMPL
#include "../luno/Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 400, 300, 30))
        return -1;

    Luno_SetClearColor((LunoColor){20, 20, 20, 255});

    while (Luno_Update())
    {
        Luno_Clear();

        LunoPoint pos = Luno_MousePosition();
        LunoPoint delta = Luno_MouseDelta();
        int wheeldelta = Luno_MouseWheelDelta();

        Luno_DrawTextF("Mouse Pos: %d, %d", 10, 10, LUNO_WHITE, pos.x, pos.y);
        Luno_DrawTextF("Mouse Motion: %d, %d", 10, 30, LUNO_WHITE, delta.x, delta.y);
        Luno_DrawTextF("Mouse Wheel: %d", 10, 50, LUNO_WHITE, wheeldelta);
    }

    Luno_Close();
    return 0;
}
