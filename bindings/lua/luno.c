#include "deps/include/lua.h"
#include "deps/include/lauxlib.h"
#define LUNO_IMPL
#include "deps/include/lualib.h"

#include "../../luno/luno.h"

/**********************************************************************************
 *
 *
 * Check/Push Helper Functions
 *
 *
 **********************************************************************************/

LunoColor luaL_checkLunoColor(lua_State *L, int index)
{
    luaL_checktype(L, index, LUA_TTABLE);

    lua_getfield(L, index, "r");
    int r = luaL_checkinteger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "g");
    int g = luaL_checkinteger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "b");
    int b = luaL_checkinteger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "a");
    int a = luaL_optinteger(L, -1, 255);
    lua_pop(L, 1);

    return (LunoColor){r, g, b, a};
}

// Push `LunoColor` to Lua as a table
void lua_pushLunoColor(lua_State *L, LunoColor color)
{
    lua_newtable(L);
    lua_pushinteger(L, color.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, color.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, color.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, color.a);
    lua_setfield(L, -2, "a");
}

/**********************************************************************************
 *
 *
 * Helper Functions
 *
 *
 **********************************************************************************/

// --- Get Executable Directory ---
void get_executable_directory(char *buffer, size_t size)
{
    GetModuleFileName(NULL, buffer, (DWORD)size);
    char *last_slash = strrchr(buffer, '\\');
    if (last_slash)
    {
        *(last_slash + 1) = '\0'; // Keep the path up to the last backslash
    }
}

/******************** LunoPoint ********************/

// Create a LunoPoint from Lua
static int l_LunoPoint(lua_State *L)
{
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);

    LunoPoint *point = (LunoPoint *)lua_newuserdata(L, sizeof(LunoPoint));
    point->x = x;
    point->y = y;

    luaL_getmetatable(L, "LunoPoint");
    lua_setmetatable(L, -2);
    return 1; // Return the userdata
}

// Get the fields of a LunoPoint
static int l_LunoPoint_get(lua_State *L)
{
    LunoPoint *point = (LunoPoint *)luaL_checkudata(L, 1, "LunoPoint");
    lua_pushinteger(L, point->x);
    lua_pushinteger(L, point->y);
    return 2; // Return x and y
}

// Set the fields of a LunoPoint
static int l_LunoPoint_set(lua_State *L)
{
    LunoPoint *point = (LunoPoint *)luaL_checkudata(L, 1, "LunoPoint");
    point->x = luaL_checkinteger(L, 2);
    point->y = luaL_checkinteger(L, 3);
    return 0; // No return value
}

/******************** LunoColor ********************/

// Create a LunoColor from Lua
static int l_LunoColor(lua_State *L)
{
    int r = luaL_checkinteger(L, 1);
    int g = luaL_checkinteger(L, 2);
    int b = luaL_checkinteger(L, 3);
    int a = luaL_optinteger(L, 4, 255);

    LunoColor *color = (LunoColor *)lua_newuserdata(L, sizeof(LunoColor));
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;

    luaL_getmetatable(L, "LunoColor");
    lua_setmetatable(L, -2);
    return 1;
}

// Get the fields of a LunoColor
static int l_LunoColor_get(lua_State *L)
{
    LunoColor *color = (LunoColor *)luaL_checkudata(L, 1, "LunoColor");
    lua_pushinteger(L, color->r);
    lua_pushinteger(L, color->g);
    lua_pushinteger(L, color->b);
    lua_pushinteger(L, color->a);
    return 4; // Return r, g, b, a
}

// Set the fields of a LunoColor
static int l_LunoColor_set(lua_State *L)
{
    LunoColor *color = (LunoColor *)luaL_checkudata(L, 1, "LunoColor");
    color->r = luaL_checkinteger(L, 2);
    color->g = luaL_checkinteger(L, 3);
    color->b = luaL_checkinteger(L, 4);
    color->a = luaL_optinteger(L, 5, 255);
    return 0;
}

/******************** LunoRect ********************/

// Create a LunoRect from Lua
static int l_LunoRect(lua_State *L)
{
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3);
    int h = luaL_checkinteger(L, 4);

    // Allocate userdata
    LunoRect *rect = (LunoRect *)lua_newuserdata(L, sizeof(LunoRect));

    // Initialize fields
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    // Set metatable
    luaL_getmetatable(L, "LunoRect");
    lua_setmetatable(L, -2);

    return 1; // Return the userdata
}

// Set the fields of a LunoRect (metamethod for __newindex)
static int l_LunoRect_set(lua_State *L)
{
    LunoRect *rect = (LunoRect *)luaL_checkudata(L, 1, "LunoRect");
    const char *key = luaL_checkstring(L, 2);

    // Accept a Lua number and cast it to int
    double value = luaL_checknumber(L, 3);
    int intValue = (int)value;

    if (strcmp(key, "x") == 0)
    {
        rect->x = intValue;
    }
    else if (strcmp(key, "y") == 0)
    {
        rect->y = intValue;
    }
    else if (strcmp(key, "w") == 0)
    {
        rect->w = intValue;
    }
    else if (strcmp(key, "h") == 0)
    {
        rect->h = intValue;
    }
    else
    {
        return luaL_error(L, "Invalid field '%s' for LunoRect", key);
    }

    return 0;
}

// Get the fields of a LunoRect (metamethod for __index)
static int l_LunoRect_get(lua_State *L)
{
    LunoRect *rect = (LunoRect *)luaL_checkudata(L, 1, "LunoRect");
    const char *key = luaL_checkstring(L, 2);

    if (strcmp(key, "x") == 0)
    {
        lua_pushinteger(L, rect->x);
    }
    else if (strcmp(key, "y") == 0)
    {
        lua_pushinteger(L, rect->y);
    }
    else if (strcmp(key, "w") == 0)
    {
        lua_pushinteger(L, rect->w);
    }
    else if (strcmp(key, "h") == 0)
    {
        lua_pushinteger(L, rect->h);
    }
    else
    {
        return luaL_error(L, "Invalid field '%s' for LunoRect", key);
    }

    return 1;
}

/******************** lunoDT lunoFPS lunoMS ********************/
// Get lunoDT
static int l_Luno_getDT(lua_State *L)
{
    lua_pushnumber(L, lunoDT); // Push to Lua
    return 1;
}

// Get lunoFPS
static int l_Luno_getFPS(lua_State *L)
{
    lua_pushnumber(L, lunoFPS);
    return 1;
}

// Get lunoMS
static int l_Luno_getMS(lua_State *L)
{
    lua_pushinteger(L, lunoMS);
    return 1;
}

/**********************************************************************************
 *
 *
 * Window Management Functions Bindings
 *
 *
 **********************************************************************************/
static int l_Luno_Create(lua_State *L)
{
    const char *title = luaL_checkstring(L, 1);
    int width = luaL_checkinteger(L, 2);
    int height = luaL_checkinteger(L, 3);
    int targetFPS = luaL_checkinteger(L, 4);

    bool success = Luno_Create(title, width, height, targetFPS);
    lua_pushboolean(L, success);
    return 1;
}

static int l_Luno_Close(lua_State *L)
{
    Luno_Close();
    return 0;
}

static int l_Luno_Update(lua_State *L)
{
    if (!Luno_Update())
    {
        lua_pushboolean(L, 0); // Push `false` if Luno_Update() indicates termination
        return 1;
    }

    lua_pushboolean(L, 1); // Push `true` to indicate the application is still running
    return 1;
}

static int l_Luno_SetClearColor(lua_State *L)
{
    LunoColor color;

    if (lua_type(L, 1) == LUA_TUSERDATA)
    {
        // If it's a LunoColor userdata, extract the value directly
        color = *(LunoColor *)luaL_checkudata(L, 1, "LunoColor");
    }
    else if (lua_type(L, 1) == LUA_TTABLE)
    {
        // If it's a Lua table, parse it into a LunoColor
        color = luaL_checkLunoColor(L, 1);
    }
    else
    {
        return luaL_error(L, "bad argument #1 to 'set_clear_color' (LunoColor or table expected)");
    }

    Luno_SetClearColor(color);
    return 0;
}

static int l_Luno_Clear(lua_State *L)
{
    Luno_Clear();
    return 0;
}

// SetWindowScale
static int l_Luno_SetWindowScale(lua_State *L)
{
    int factor = luaL_checkinteger(L, 1);
    Luno_SetWindowScale(factor);
    return 0;
}

/**********************************************************************************
 *
 * Drawing Functions Bindings
 *
 **********************************************************************************/

// Luno_DrawPixel
static int l_Luno_DrawPixel(lua_State *L)
{
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    LunoColor color;

    if (lua_type(L, 3) == LUA_TUSERDATA)
    {
        // If it's a LunoColor userdata, extract the value directly
        color = *(LunoColor *)luaL_checkudata(L, 3, "LunoColor");
    }
    else if (lua_type(L, 3) == LUA_TTABLE)
    {
        // If it's a Lua table, parse it into a LunoColor
        color = luaL_checkLunoColor(L, 3);
    }
    else
    {
        return luaL_error(L, "bad argument #3 to 'draw_pixel' (LunoColor or table expected)");
    }

    Luno_DrawPixel(x, y, color);
    return 0;
}

// Luno_GetPixel
static int l_Luno_GetPixel(lua_State *L)
{
    // Get the LunoImage from the first argument
    LunoImage *image = *(LunoImage **)luaL_checkudata(L, 1, "LunoImage");

    // Get the x and y coordinates
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);

    // Call the Luno_GetPixel function
    LunoColor color = Luno_GetPixel(image, x, y);

    // Push the color as a table or userdata
    lua_pushLunoColor(L, color);

    return 1;
}

// Luno_CreateImage
static int l_Luno_CreateImage(lua_State *L)
{
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    LunoImage *image = Luno_CreateImage(width, height);

    if (!image)
    {
        return luaL_error(L, "Failed to create image");
    }

    *(LunoImage **)lua_newuserdata(L, sizeof(LunoImage *)) = image;
    luaL_getmetatable(L, "LunoImage");
    lua_setmetatable(L, -2);

    return 1;
}

// Luno_LoadImage
static int l_Luno_LoadImage(lua_State *L)
{
    const char *filePath = luaL_checkstring(L, 1);
    LunoImage *image = Luno_LoadImage(filePath);

    if (!image)
    {
        return luaL_error(L, "Failed to load image from file");
    }

    *(LunoImage **)lua_newuserdata(L, sizeof(LunoImage *)) = image;
    luaL_getmetatable(L, "LunoImage");
    lua_setmetatable(L, -2);

    return 1;
}

// Luno_LoadImageMem
static int l_Luno_LoadImageMem(lua_State *L)
{
    size_t len;
    const char *buffer = luaL_checklstring(L, 1, &len);
    LunoImage *image = Luno_LoadImageMem(buffer, (int)len);

    if (!image)
    {
        return luaL_error(L, "Failed to load image from memory");
    }

    *(LunoImage **)lua_newuserdata(L, sizeof(LunoImage *)) = image;
    luaL_getmetatable(L, "LunoImage");
    lua_setmetatable(L, -2);

    return 1;
}

// Luno_FillImage
static int l_Luno_FillImage(lua_State *L)
{
    LunoImage *image = *(LunoImage **)luaL_checkudata(L, 1, "LunoImage");
    LunoColor color;

    if (lua_type(L, 2) == LUA_TUSERDATA)
    {
        // If it's a LunoColor userdata, extract the value directly
        color = *(LunoColor *)luaL_checkudata(L, 2, "LunoColor");
    }
    else if (lua_type(L, 2) == LUA_TTABLE)
    {
        // If it's a Lua table, parse it into a LunoColor
        color = luaL_checkLunoColor(L, 2);
    }
    else
    {
        return luaL_error(L, "bad argument #2 to 'fill_image' (LunoColor or table expected)");
    }

    Luno_FillImage(image, color);
    return 0;
}

// Luno_DrawImage
static int l_Luno_DrawImage(lua_State *L)
{
    LunoImage *image = *(LunoImage **)luaL_checkudata(L, 1, "LunoImage");
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    Luno_DrawImage(image, x, y);
    return 0;
}

// Luno_DrawImageRect
static int l_Luno_DrawImageRect(lua_State *L)
{
    LunoImage *image = *(LunoImage **)luaL_checkudata(L, 1, "LunoImage");
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    LunoRect *srcRect = (LunoRect *)luaL_checkudata(L, 4, "LunoRect");
    Luno_DrawImageRect(image, x, y, *srcRect);
    return 0;
}

// Luno_DestroyImage
static int l_Luno_DestroyImage(lua_State *L)
{
    LunoImage *image = *(LunoImage **)luaL_checkudata(L, 1, "LunoImage");
    Luno_DestroyImage(image);
    return 0;
}

// Luno_DrawCircle
static int l_Luno_DrawCircle(lua_State *L)
{
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int radius = luaL_checkinteger(L, 3);
    LunoColor color;

    if (lua_type(L, 4) == LUA_TUSERDATA)
    {
        // If it's a LunoColor userdata, extract the value directly
        color = *(LunoColor *)luaL_checkudata(L, 4, "LunoColor");
    }
    else if (lua_type(L, 4) == LUA_TTABLE)
    {
        // If it's a Lua table, parse it into a LunoColor
        color = luaL_checkLunoColor(L, 4);
    }
    else
    {
        return luaL_error(L, "bad argument #4 to 'draw_circle' (LunoColor or table expected)");
    }

    bool fill = lua_toboolean(L, 5);
    Luno_DrawCircle(x, y, radius, color, fill);
    return 0;
}

// Luno_DrawLine
static int l_Luno_DrawLine(lua_State *L)
{
    int x1 = luaL_checkinteger(L, 1);
    int y1 = luaL_checkinteger(L, 2);
    int x2 = luaL_checkinteger(L, 3);
    int y2 = luaL_checkinteger(L, 4);
    LunoColor color;

    if (lua_type(L, 5) == LUA_TUSERDATA)
    {
        // If it's a LunoColor userdata, extract the value directly
        color = *(LunoColor *)luaL_checkudata(L, 5, "LunoColor");
    }
    else if (lua_type(L, 5) == LUA_TTABLE)
    {
        // If it's a Lua table, parse it into a LunoColor
        color = luaL_checkLunoColor(L, 5);
    }
    else
    {
        return luaL_error(L, "bad argument #5 to 'draw_line' (LunoColor or table expected)");
    }

    Luno_DrawLine(x1, y1, x2, y2, color);
    return 0;
}

static int l_Luno_DrawRect(lua_State *L)
{
    // Check and print the first argument (rect)
    LunoRect *rect = (LunoRect *)luaL_checkudata(L, 1, "LunoRect");

    // Check and interpret the second argument (color)
    LunoColor color;
    if (lua_type(L, 2) == LUA_TUSERDATA)
    {
        color = *(LunoColor *)luaL_checkudata(L, 2, "LunoColor");
    }
    else if (lua_type(L, 2) == LUA_TTABLE)
    {
        color = luaL_checkLunoColor(L, 2);
    }
    else
    {
        return luaL_error(L, "bad argument #2 to 'draw_rect' (LunoColor or table expected)");
    }

    // Get the `fill` argument
    bool fill = lua_toboolean(L, 3);

    // Call the C function
    Luno_DrawRect(*rect, color, fill);
    return 0;
}

/**********************************************************************************
 *
 * Input Handling Functions Bindings
 *
 **********************************************************************************/

// Luno_IsKeyPressed
static int l_Luno_IsKeyPressed(lua_State *L)
{
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, Luno_IsKeyPressed(key));
    return 1;
}

// Luno_IsKeyHeld
static int l_Luno_IsKeyHeld(lua_State *L)
{
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, Luno_IsKeyHeld(key));
    return 1;
}

// Luno_IsKeyReleased
static int l_Luno_IsKeyReleased(lua_State *L)
{
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, Luno_IsKeyReleased(key));
    return 1;
}

// Luno_IsMouseButtonPressed
static int l_Luno_IsMouseButtonPressed(lua_State *L)
{
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, Luno_IsMouseButtonPressed(button));
    return 1;
}

// Luno_IsMouseButtonHeld
static int l_Luno_IsMouseButtonHeld(lua_State *L)
{
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, Luno_IsMouseButtonHeld(button));
    return 1;
}

// Luno_IsMouseButtonReleased
static int l_Luno_IsMouseButtonReleased(lua_State *L)
{
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, Luno_IsMouseButtonReleased(button));
    return 1;
}

// Luno_MousePosition
static int l_Luno_MousePosition(lua_State *L)
{
    LunoPoint position = Luno_MousePosition();
    lua_newtable(L);
    lua_pushinteger(L, position.x);
    lua_setfield(L, -2, "x");
    lua_pushinteger(L, position.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Luno_MouseDelta
static int l_Luno_MouseDelta(lua_State *L)
{
    LunoPoint delta = Luno_MouseDelta();
    lua_newtable(L);
    lua_pushinteger(L, delta.x);
    lua_setfield(L, -2, "x");
    lua_pushinteger(L, delta.y);
    lua_setfield(L, -2, "y");
    return 1;
}

// Luno_MouseWheelDelta
static int l_Luno_MouseWheelDelta(lua_State *L)
{
    lua_pushinteger(L, Luno_MouseWheelDelta());
    return 1;
}

/**********************************************************************************
 *
 * Cursor Control Functions Bindings
 *
 **********************************************************************************/

// Luno_SetCursorVisibility
static int l_Luno_SetCursorVisibility(lua_State *L)
{
    bool visible = lua_toboolean(L, 1);
    Luno_SetCursorVisibility(visible);
    return 0;
}

// Luno_IsCursorVisible
static int l_Luno_IsCursorVisible(lua_State *L)
{
    lua_pushboolean(L, Luno_IsCursorVisible());
    return 1;
}

/**********************************************************************************
 *
 * Timer Functions Bindings
 *
 **********************************************************************************/

// Luno_CreateTimer
static int l_Luno_CreateTimer(lua_State *L)
{
    int interval = luaL_checkinteger(L, 1);
    LunoTimer *timer = (LunoTimer *)lua_newuserdata(L, sizeof(LunoTimer));
    *timer = Luno_CreateTimer(interval);

    // Set the metatable for the userdata
    luaL_getmetatable(L, "LunoTimer");
    lua_setmetatable(L, -2);

    return 1; // Return the timer userdata
}

// Luno_TimerTicked
static int l_Luno_TimerTicked(lua_State *L)
{
    LunoTimer *timer = (LunoTimer *)luaL_checkudata(L, 1, "LunoTimer");
    lua_pushboolean(L, Luno_TimerTicked(timer));
    return 1;
}

// Luno_ResetTimer
static int l_Luno_ResetTimer(lua_State *L)
{
    LunoTimer *timer = (LunoTimer *)luaL_checkudata(L, 1, "LunoTimer");
    Luno_ResetTimer(timer);
    return 0;
}

// Luno_TimerElapsed
static int l_Luno_TimerElapsed(lua_State *L)
{
    LunoTimer *timer = (LunoTimer *)luaL_checkudata(L, 1, "LunoTimer");
    lua_pushinteger(L, Luno_TimerElapsed(timer));
    return 1;
}

/**********************************************************************************
 *
 * Font Handling Bindings
 *
 **********************************************************************************/

// Luno_FontFromImage
static int l_Luno_FontFromImage(lua_State *L)
{
    LunoImage *image = *(LunoImage **)luaL_checkudata(L, 1, "LunoImage");
    int glyphWidth = luaL_checkinteger(L, 2);
    int glyphHeight = luaL_checkinteger(L, 3);

    LunoFont *font = Luno_FontFromImage(image, glyphWidth, glyphHeight);
    if (!font)
    {
        return luaL_error(L, "Failed to create font from image");
    }

    *(LunoFont **)lua_newuserdata(L, sizeof(LunoFont *)) = font;
    luaL_getmetatable(L, "LunoFont");
    lua_setmetatable(L, -2);

    return 1;
}

// Luno_LoadFont
static int l_Luno_LoadFont(lua_State *L)
{
    const char *filePath = luaL_checkstring(L, 1);
    int glyphWidth = luaL_checkinteger(L, 2);
    int glyphHeight = luaL_checkinteger(L, 3);

    LunoFont *font = Luno_LoadFont(filePath, glyphWidth, glyphHeight);
    if (!font)
    {
        return luaL_error(L, "Failed to load font from file");
    }

    *(LunoFont **)lua_newuserdata(L, sizeof(LunoFont *)) = font;
    luaL_getmetatable(L, "LunoFont");
    lua_setmetatable(L, -2);

    return 1;
}

// Luno_LoadFontMem
static int l_Luno_LoadFontMem(lua_State *L)
{
    size_t len;
    const char *buffer = luaL_checklstring(L, 1, &len);
    int glyphWidth = luaL_checkinteger(L, 2);
    int glyphHeight = luaL_checkinteger(L, 3);

    LunoFont *font = Luno_LoadFontMem(buffer, (int)len, glyphWidth, glyphHeight);
    if (!font)
    {
        return luaL_error(L, "Failed to load font from memory");
    }

    *(LunoFont **)lua_newuserdata(L, sizeof(LunoFont *)) = font;
    luaL_getmetatable(L, "LunoFont");
    lua_setmetatable(L, -2);

    return 1;
}

// Luno_ResetFont
static int l_Luno_ResetFont(lua_State *L)
{
    Luno_ResetFont();
    return 0;
}

// Luno_TextWidth
static int l_Luno_TextWidth(lua_State *L)
{
    const char *text = luaL_checkstring(L, 1);
    int width = Luno_TextWidth(text);
    lua_pushinteger(L, width);
    return 1;
}

// Luno_TextHeight
static int l_Luno_TextHeight(lua_State *L)
{
    int height = Luno_TextHeight();
    lua_pushinteger(L, height);
    return 1;
}

// Luno_DestroyFont
static int l_Luno_DestroyFont(lua_State *L)
{
    LunoFont **font = (LunoFont **)luaL_checkudata(L, 1, "LunoFont");
    if (*font)
    {
        Luno_DestroyFont(*font);
        *font = NULL;
    }
    return 0;
}

// Luno_DrawText
static int l_Luno_DrawText(lua_State *L)
{
    const char *text = luaL_checkstring(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    LunoColor color;

    if (lua_type(L, 4) == LUA_TUSERDATA)
    {
        // If it's a LunoColor userdata, extract the value directly
        color = *(LunoColor *)luaL_checkudata(L, 4, "LunoColor");
    }
    else if (lua_type(L, 4) == LUA_TTABLE)
    {
        // If it's a Lua table, parse it into a LunoColor
        color = luaL_checkLunoColor(L, 4);
    }
    else
    {
        return luaL_error(L, "bad argument #4 to 'draw_text' (LunoColor or table expected)");
    }

    Luno_DrawText(text, x, y, color);
    return 0;
}

/**********************************************************************************
 *
 * Collision Detection Bindings
 *
 **********************************************************************************/

// Luno_PointRecOverlaps
static int l_Luno_PointRecOverlaps(lua_State *L)
{
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    LunoRect *rect = (LunoRect *)luaL_checkudata(L, 3, "LunoRect");

    lua_pushboolean(L, Luno_PointRecOverlaps(x, y, *rect));
    return 1;
}

// Luno_RecsOverlap
static int l_Luno_RecsOverlap(lua_State *L)
{
    LunoRect *rect1 = (LunoRect *)luaL_checkudata(L, 1, "LunoRect");
    LunoRect *rect2 = (LunoRect *)luaL_checkudata(L, 2, "LunoRect");

    lua_pushboolean(L, Luno_RecsOverlap(*rect1, *rect2));
    return 1;
}

// Luno_PointCircleOverlaps
static int l_Luno_PointCircleOverlaps(lua_State *L)
{
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int cx = luaL_checkinteger(L, 3);
    int cy = luaL_checkinteger(L, 4);
    float radius = luaL_checknumber(L, 5);

    lua_pushboolean(L, Luno_PointCircleOverlaps(x, y, cx, cy, radius));
    return 1;
}

// Luno_RecCircleOverlaps
static int l_Luno_RecCircleOverlaps(lua_State *L)
{
    LunoRect *rect = (LunoRect *)luaL_checkudata(L, 1, "LunoRect");
    int cx = luaL_checkinteger(L, 2);
    int cy = luaL_checkinteger(L, 3);
    float radius = luaL_checknumber(L, 4);

    lua_pushboolean(L, Luno_RecCircleOverlaps(*rect, cx, cy, radius));
    return 1;
}

// Luno_CirclesOverlaps
static int l_Luno_CirclesOverlaps(lua_State *L)
{
    int cx1 = luaL_checkinteger(L, 1);
    int cy1 = luaL_checkinteger(L, 2);
    float radius1 = luaL_checknumber(L, 3);
    int cx2 = luaL_checkinteger(L, 4);
    int cy2 = luaL_checkinteger(L, 5);
    float radius2 = luaL_checknumber(L, 6);

    lua_pushboolean(L, Luno_CirclesOverlaps(cx1, cy1, radius1, cx2, cy2, radius2));
    return 1;
}

/**********************************************************************************
 *
 *
 * Register library
 *
 *
 **********************************************************************************/

void register_luno_structs(lua_State *L)
{
    // Register LunoPoint
    luaL_newmetatable(L, "LunoPoint");
    lua_pushcfunction(L, l_LunoPoint_get);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, l_LunoPoint_set);
    lua_setfield(L, -2, "__newindex");
    lua_pop(L, 1);

    // Register LunoColor
    luaL_newmetatable(L, "LunoColor");
    lua_pushcfunction(L, l_LunoColor_get);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, l_LunoColor_set);
    lua_setfield(L, -2, "__newindex");
    lua_pop(L, 1);

    // Register LunoRect
    luaL_newmetatable(L, "LunoRect");
    lua_pushcfunction(L, l_LunoRect_get);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, l_LunoRect_set);
    lua_setfield(L, -2, "__newindex");
    lua_pop(L, 1);
}

void register_luno_colors(lua_State *L)
{
    // Add color constants to the Lua table
    lua_pushLunoColor(L, LUNO_WHITE);
    lua_setfield(L, -2, "WHITE");

    lua_pushLunoColor(L, LUNO_BLACK);
    lua_setfield(L, -2, "BLACK");

    lua_pushLunoColor(L, LUNO_GRAY);
    lua_setfield(L, -2, "GRAY");

    lua_pushLunoColor(L, LUNO_DARKGRAY);
    lua_setfield(L, -2, "DARKGRAY");

    lua_pushLunoColor(L, LUNO_RED);
    lua_setfield(L, -2, "RED");

    lua_pushLunoColor(L, LUNO_GREEN);
    lua_setfield(L, -2, "GREEN");

    lua_pushLunoColor(L, LUNO_BLUE);
    lua_setfield(L, -2, "BLUE");

    lua_pushLunoColor(L, LUNO_YELLOW);
    lua_setfield(L, -2, "YELLOW");

    lua_pushLunoColor(L, LUNO_CYAN);
    lua_setfield(L, -2, "CYAN");

    lua_pushLunoColor(L, LUNO_MAGENTA);
    lua_setfield(L, -2, "MAGENTA");

    lua_pushLunoColor(L, LUNO_LIGHTGRAY);
    lua_setfield(L, -2, "LIGHTGRAY");

    lua_pushLunoColor(L, LUNO_ORANGE);
    lua_setfield(L, -2, "ORANGE");

    lua_pushLunoColor(L, LUNO_PURPLE);
    lua_setfield(L, -2, "PURPLE");

    lua_pushLunoColor(L, LUNO_BROWN);
    lua_setfield(L, -2, "BROWN");

    lua_pushLunoColor(L, LUNO_PINK);
    lua_setfield(L, -2, "PINK");

    lua_pushLunoColor(L, LUNO_LIME);
    lua_setfield(L, -2, "LIME");

    lua_pushLunoColor(L, LUNO_TEAL);
    lua_setfield(L, -2, "TEAL");

    lua_pushLunoColor(L, LUNO_GOLD);
    lua_setfield(L, -2, "GOLD");

    lua_pushLunoColor(L, LUNO_SILVER);
    lua_setfield(L, -2, "SILVER");

    lua_pushLunoColor(L, LUNO_BEIGE);
    lua_setfield(L, -2, "BEIGE");

    lua_pushLunoColor(L, LUNO_IVORY);
    lua_setfield(L, -2, "IVORY");

    lua_pushLunoColor(L, LUNO_KHAKI);
    lua_setfield(L, -2, "KHAKI");

    lua_pushLunoColor(L, LUNO_NAVY);
    lua_setfield(L, -2, "NAVY");

    lua_pushLunoColor(L, LUNO_MAROON);
    lua_setfield(L, -2, "MAROON");

    lua_pushLunoColor(L, LUNO_OLIVE);
    lua_setfield(L, -2, "OLIVE");

    lua_pushLunoColor(L, LUNO_AQUA);
    lua_setfield(L, -2, "AQUA");

    lua_pushLunoColor(L, LUNO_CORAL);
    lua_setfield(L, -2, "CORAL");

    lua_pushLunoColor(L, LUNO_TAN);
    lua_setfield(L, -2, "TAN");

    lua_pushLunoColor(L, LUNO_SKYBLUE);
    lua_setfield(L, -2, "SKYBLUE");

    lua_pushLunoColor(L, LUNO_MINT);
    lua_setfield(L, -2, "MINT");

    lua_pushLunoColor(L, LUNO_PEACH);
    lua_setfield(L, -2, "PEACH");

    lua_pushLunoColor(L, LUNO_CHOCOLATE);
    lua_setfield(L, -2, "CHOCOLATE");

    lua_pushLunoColor(L, LUNO_VIOLET);
    lua_setfield(L, -2, "VIOLET");

    lua_pushLunoColor(L, LUNO_INDIGO);
    lua_setfield(L, -2, "INDIGO");

    lua_pushLunoColor(L, LUNO_TURQUOISE);
    lua_setfield(L, -2, "TURQUOISE");

    lua_pushLunoColor(L, LUNO_SALMON);
    lua_setfield(L, -2, "SALMON");

    lua_pushLunoColor(L, LUNO_WHEAT);
    lua_setfield(L, -2, "WHEAT");
}

static void register_luno_timers(lua_State *L)
{
    luaL_newmetatable(L, "LunoTimer");

    // Set up the __index table
    lua_newtable(L);
    lua_pushcfunction(L, l_Luno_TimerTicked);
    lua_setfield(L, -2, "ticked");
    lua_pushcfunction(L, l_Luno_ResetTimer);
    lua_setfield(L, -2, "reset");
    lua_pushcfunction(L, l_Luno_TimerElapsed);
    lua_setfield(L, -2, "elapsed");
    lua_setfield(L, -2, "__index"); // Assign the __index table to the metatable

    lua_pop(L, 1); // Pop the metatable off the stack
}

static const luaL_Reg lunolib[] = {
    // Structs and variables
    {"get_dt", l_Luno_getDT},
    {"get_fps", l_Luno_getFPS},
    {"get_ms", l_Luno_getMS},
    {"point", l_LunoPoint},
    {"color", l_LunoColor},
    {"rect", l_LunoRect},
    // Window management
    {"create", l_Luno_Create},
    {"close", l_Luno_Close},
    {"update", l_Luno_Update},
    {"set_window_scale", l_Luno_SetWindowScale},
    // Drawing functions
    {"create_image", l_Luno_CreateImage},
    {"load_image", l_Luno_LoadImage},
    {"load_image_mem", l_Luno_LoadImageMem},
    {"draw_pixel", l_Luno_DrawPixel},
    {"get_pixel", l_Luno_GetPixel},
    {"draw_line", l_Luno_DrawLine},
    {"draw_rect", l_Luno_DrawRect},
    {"draw_circle", l_Luno_DrawCircle},
    {"fill_image", l_Luno_FillImage},
    {"draw_image", l_Luno_DrawImage},
    {"draw_image_rect", l_Luno_DrawImageRect},
    {"destroy_image", l_Luno_DestroyImage},
    {"set_clear_color", l_Luno_SetClearColor},
    {"clear", l_Luno_Clear},
    // Keyboard and mouse input functions
    {"is_key_pressed", l_Luno_IsKeyPressed},
    {"is_key_held", l_Luno_IsKeyHeld},
    {"is_key_released", l_Luno_IsKeyReleased},
    {"is_mouse_button_pressed", l_Luno_IsMouseButtonPressed},
    {"is_mouse_button_held", l_Luno_IsMouseButtonHeld},
    {"is_mouse_button_released", l_Luno_IsMouseButtonReleased},
    {"mouse_position", l_Luno_MousePosition},
    {"mouse_delta", l_Luno_MouseDelta},
    {"mouse_wheel_delta", l_Luno_MouseWheelDelta},
    {"create_timer", l_Luno_CreateTimer},
    {"timer_ticked", l_Luno_TimerTicked},
    {"reset_timer", l_Luno_ResetTimer},
    {"timer_elapsed", l_Luno_TimerElapsed},
    {"set_cursor_visibility", l_Luno_SetCursorVisibility},
    {"is_cursor_visible", l_Luno_IsCursorVisible},
    // Font functions
    {"font_from_image", l_Luno_FontFromImage},
    {"load_font", l_Luno_LoadFont},
    {"load_font_mem", l_Luno_LoadFontMem},
    {"draw_text", l_Luno_DrawText},
    {"reset_font", l_Luno_ResetFont},
    {"text_width", l_Luno_TextWidth},
    {"text_height", l_Luno_TextHeight},
    {"destroy_font", l_Luno_DestroyFont},
    // Collision Detection Functions
    {"point_rec_overlaps", l_Luno_PointRecOverlaps},
    {"recs_overlap", l_Luno_RecsOverlap},
    {"point_circle_overlaps", l_Luno_PointCircleOverlaps},
    {"rec_circle_overlaps", l_Luno_RecCircleOverlaps},
    {"circles_overlap", l_Luno_CirclesOverlaps},
    {NULL, NULL}};

int luaopen_luno(lua_State *L)
{
    luaL_newlib(L, lunolib);

    // Register color constants
    register_luno_colors(L);

    // Register structs
    register_luno_structs(L);

    // Register LunoImage metatable
    luaL_newmetatable(L, "LunoImage");
    lua_pushcfunction(L, l_Luno_DestroyImage);
    lua_setfield(L, -2, "__gc");
    lua_pop(L, 1);

    // Register LunoFont metatable
    luaL_newmetatable(L, "LunoFont");
    lua_pushcfunction(L, l_Luno_DestroyFont);
    lua_setfield(L, -2, "__gc");
    lua_pop(L, 1);

    register_luno_timers(L);

    return 1;
}

/**********************************************************************************
 *
 *
 * Main Function
 *
 *
 **********************************************************************************/
int main()
{
    char exe_dir[1024];
    char script_path[1024];

    // Get the executable directory
    get_executable_directory(exe_dir, sizeof(exe_dir));

    // Construct the full path to `main.lua`
    snprintf(script_path, sizeof(script_path), "%smain.lua", exe_dir);

    // Check if `main.lua` exists
    FILE *file = fopen(script_path, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Could not find 'main.lua' in %s\n", exe_dir);
        return 1;
    }
    fclose(file);

    // Initialize Lua
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Register Luno library
    luaL_requiref(L, "luno", luaopen_luno, 1);
    lua_pop(L, 1);

    // Run the Lua script
    if (luaL_dofile(L, script_path) != LUA_OK)
    {
        fprintf(stderr, "Lua Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        lua_close(L);
        return 1;
    }

    // Clean up Lua
    lua_close(L);
    Luno_Close();
    return 0;
}
