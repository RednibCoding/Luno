#include "stdio.h"
#define LUNO_IMPL
#include "../Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 800, 600, 30))
    {
        return -1;
    }

    Luno_SetClearColor((LunoColor){30, 30, 30, 255});

    while (Luno_Update())
    {
        Luno_Clear();
        Luno_DrawText("Hello Luno!", 50, 50, (LunoColor){255, 255, 255, 255});
    }

    Luno_Close();
    return 0;
}
