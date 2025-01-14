#include "stdio.h"
#define LUNO_IMPL
#include "../luno/Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 300, 100, 30))
    {
        return -1;
    }

    LunoTimer timer = Luno_CreateTimer(1000);

    while (Luno_Update())
    {
        Luno_Clear();

        if (Luno_TimerTicked(&timer))
        {
            printf("Tick...");
        }
        printf("timer %d\n", Luno_TimerElapsed(&timer));
    }

    Luno_Close();
    return 0;
}
