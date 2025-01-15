#include "stdio.h"

#define LUNO_IMPL
#include "../luno/Luno.h"

int main()
{
    rc_write_tga_as_c_array("assets/font.tga", "embedded_font.h", "_lunoFontImageData");
    return 0;
}