#include "stdio.h"

#define LUNO_IMPL
#include "../Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 800, 600, 30))
        return -1;

    Luno_SetClearColor((LunoColor){20, 20, 20, 255});

    LunoPoint mpos = {0};

    LunoRect rect = (LunoRect){100, 100, 200, 200};
    bool collidingRect = false;
    bool collidingCircle = false;

    while (Luno_Update())
    {
        Luno_Clear();

        mpos = Luno_MousePosition();
        collidingRect = Luno_PointRecOverlaps(mpos.x, mpos.y, rect);
        collidingCircle = Luno_PointCircleOverlaps(mpos.x, mpos.y, 400, 400, 100);

        if (collidingRect)
            Luno_DrawRect(rect, LUNO_CYAN, true);

        else
            Luno_DrawRect(rect, LUNO_CYAN, false);

        if (collidingCircle)
            Luno_DrawCircle(400, 400, 100, LUNO_LIME, true);
        else
            Luno_DrawCircle(400, 400, 100, LUNO_LIME, false);
    }

    Luno_Close();
    return 0;
}