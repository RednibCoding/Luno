#include "stdio.h"

#define LUNO_IMPL
#include "../Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 800, 600, 30))
        return -1;

    Luno_SetClearColor((LunoColor){20, 20, 20, 255});

    while (Luno_Update())
    {
        Luno_Clear();
    }

    Luno_Close();
    return 0;
}
