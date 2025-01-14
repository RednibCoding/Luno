# Luno

## Introduction

Luno is a lightweight 2D graphics library designed for creating games or graphical applications in C.
It provides a simple interface for window management, drawing primitives, image handling, text rendering, and input handling.

---

## Features

- **Window Management**: Create and scale windows.
- **Rendering**: Draw pixels, lines, rectangles, circles, and images.
- **Font Rendering**: Render bitmap fonts with ease.
- **Input Handling**: Detect keyboard, mouse buttons, and mouse wheel inputs.
- **Timers**: Create timers for interval-based actions.
- **Collision Detection**: Perform basic 2D overlap checks.

---

## Overview

- Small header-only library: ~1.2k lines of C
- Software rendered images and bitmap fonts
- Keyboard and mouse input
- Image Loading (via stb_image)
- No dependencies
- Windows only

## Installation

1. **Clone the repository**:

   ```sh
   git clone git@github.com:RednibCoding/luno.git
   ```

2. **Copy the 'luno' folder into your project**.

3. **Include the Luno header**:

   ```c
   #define LUNO_IMPL
   #include "luno/luno.h"
   ```

   Do `#define LUNO_IMPL` before you include `luno.h` in _one_ C file to create the implementation.
   In all other files just include `luno.h` without creating the implementations.

   ```c
   #include "luno/luno.h"
   ```

4. **Compile your project**:

   ```sh
   gcc -o game.exe main.c -lgdi32 -luser32 -lwinmm
   ```

## Example

```c
#define LUNO_IMPL
#include "luno/Luno.h"

int main()
{
    if (!Luno_Create("Luno Window", 800, 600, 30))
        return -1;

    Luno_SetClearColor(LUNO_DARKGRAY);

    while (Luno_Update())
    {
        Luno_Clear();
        Luno_DrawText("Hello Luno", 50, 50, LUNO_WHITE);
    }

    Luno_Close();
    return 0;
}
```

## Functions

### Initialization and Cleanup

#### `bool Luno_Create(const char *title, int width, int height, int targetFPS)`

Creates a window with the specified title, dimensions, and target frame rate.

- **Parameters**:
  - `title`: The title of the window.
  - `width`, `height`: Dimensions of the window.
  - `targetFPS`: The desired frames per second.
- **Returns**: `true` on success, `false` on failure.

#### `void Luno_Close()`

Closes the window and releases resources.

### Window Management

#### `void SetWindowScale(int factor)`

Scales the window dimensions by a given factor.

- **Parameter**:
  - `factor`: The scaling factor (e.g., `2` doubles the size).

### Rendering Control

#### `void Luno_SetClearColor(LunoColor color)`

Sets the background color used when clearing the screen.

#### `void Luno_Clear()`

Clears the screen to the current clear color.

### Drawing Functions

#### `void Luno_DrawPixel(int x, int y, LunoColor color)`

Draws a single pixel at the specified coordinates.

#### `LunoColor Luno_GetPixel(LunoImage *image, int x, int y)`

Gets the pixel color of the given image at the location x, y.

#### `void Luno_DrawRect(LunoRect rect, LunoColor color, bool fill)`

Draws a rectangle.

- **Parameters**:
  - `rect`: The rectangle to draw.
  - `color`: The color of the rectangle.
  - `fill`: `true` to fill the rectangle, `false` for an outline.

#### `void Luno_DrawCircle(int x, int y, int radius, LunoColor color, bool fill)`

Draws a circle.

- **Parameters**:
  - `x`, `y`: The center of the circle.
  - `radius`: The radius of the circle.
  - `color`: The color of the circle.
  - `fill`: `true` to fill the circle, `false` for an outline.

#### `void Luno_DrawLine(int x1, int y1, int x2, int y2, LunoColor color)`

Draws a line between two points.

### Image Handling

#### `LunoImage *Luno_CreateImage(int width, int height)`

Creates a blank image.

- **Returns**: A pointer to the created image.

#### `LunoImage *Luno_LoadImage(const char *filePath)`

Loads an image from a file.

- **Returns**: A pointer to the loaded image, or `NULL` on failure.

#### `LunoImage *Luno_LoadImageMem(const char *buffer, int bufferLen)`

Loads an image from memory.

- **Returns**: A pointer to the loaded image, or `NULL` on failure.

#### `void Luno_FillImage(LunoImage *image, LunoColor color)`

Fills an image with a specified color.

#### `void Luno_DrawImage(LunoImage *image, int x, int y)`

Draws an image at the specified position.

#### `void Luno_DrawImageRect(LunoImage *image, int x, int y, LunoRect srcRect)`

Draws a portion of an image.

#### `void Luno_DestroyImage(LunoImage *image)`

Releases resources associated with an image.

### Font Handling

#### `LunoFont *Luno_FontFromImage(LunoImage *image, int glyphWidth, int glyphHeight)`

Creates a font from an image.

#### `LunoFont *Luno_LoadFont(const char *filePath, int glyphWidth, int glyphHeight)`

Loads a font from a file.

#### `LunoFont *Luno_LoadFontMem(const char *buffer, int bufferLen, int glyphWidth, int glyphHeight)`

Loads a font from memory.

#### `void Luno_DrawText(const char *text, int x, int y, LunoColor color)`

Draws a string of text.

#### `void Luno_DrawTextF(const char *format, int x, int y, LunoColor color, ...)`

Draws formatted text.

#### `void Luno_DestroyFont(LunoFont *font)`

Releases resources associated with a font.

### Input Handling

#### `bool Luno_IsKeyPressed(int key)`

Checks if a key was pressed this frame.

#### `bool Luno_IsKeyHeld(int key)`

Checks if a key is currently held down.

#### `bool Luno_IsKeyReleased(int key)`

Checks if a key was released this frame.

#### `bool Luno_IsMouseButtonPressed(int button)`

Checks if a mouse button was pressed this frame.

#### `bool Luno_IsMouseButtonHeld(int button)`

Checks if a mouse button is currently held down.

#### `bool Luno_IsMouseButtonReleased(int button)`

Checks if a mouse button was released this frame.

#### `LunoPoint Luno_MousePosition()`

Returns the current mouse position.

#### `LunoPoint Luno_MouseDelta()`

Returns the change in mouse position since the last frame.

#### `int Luno_MouseWheelDelta()`

Returns the change in the mouse wheel since the last frame.

### Cursor Control

#### `void Luno_SetCursorVisibility(bool visible)`

Sets the cursor visibility.

#### `bool Luno_IsCursorVisible()`

Checks if the cursor is visible.

### Timers

#### `LunoTimer Luno_CreateTimer(int interval)`

Creates a timer with the specified interval (in milliseconds).

#### `bool Luno_TimerTicked(LunoTimer *timer)`

Checks if the timer has reached its interval this frame.

#### `void Luno_ResetTimer(LunoTimer *timer)`

Resets a timer to start counting from now.

#### `int Luno_TimerElapsed(LunoTimer *timer)`

Returns the elapsed time in milliseconds since the timer started.

### Collision Detection

#### `bool Luno_PointRecOverlaps(int x, int y, LunoRect rec)`

Checks if a point is inside a rectangle.

#### `bool Luno_RecsOverlap(LunoRect rec1, LunoRect rec2)`

Checks if two rectangles overlap.

#### `bool Luno_PointCircleOverlaps(int x, int y, int cx, int cy, float circleRadius)`

Checks if a point is inside a circle.

#### `bool Luno_RecCircleOverlaps(LunoRect rec, int cx, int cy, float circleRadius)`

Checks if a rectangle and circle overlap.

#### `bool Luno_CirclesOverlaps(int cx1, int cy1, float circle1Radius, int cx2, int cy2, float circle2Radius)`

Checks if two circles overlap.

---

## Predefined Colors

The Luno library provides a variety of predefined colors for ease of use:

```c
#define LUNO_WHITE (LunoColor){255, 255, 255, 255}
#define LUNO_BLACK (LunoColor){0, 0, 0, 255}
#define LUNO_RED (LunoColor){255, 0, 0, 255}
#define LUNO_GREEN (LunoColor){0, 255, 0, 255}
#define LUNO_BLUE (LunoColor){0, 0, 255, 255}
#define LUNO_YELLOW (LunoColor){255, 255, 0, 255}
#define LUNO_CYAN (LunoColor){0, 255, 255, 255}
#define LUNO_MAGENTA (LunoColor){255, 0, 255, 255}
#define LUNO_LIGHTGRAY (LunoColor){211, 211, 211, 255}
#define LUNO_GRAY (LunoColor){128, 128, 128, 255}
#define LUNO_DARKGRAY (LunoColor){64, 64, 64, 255}
#define LUNO_ORANGE (LunoColor){255, 165, 0, 255}
#define LUNO_PURPLE (LunoColor){128, 0, 128, 255}
#define LUNO_BROWN (LunoColor){165, 42, 42, 255}
#define LUNO_PINK (LunoColor){255, 192, 203, 255}
#define LUNO_LIME (LunoColor){50, 205, 50, 255}
#define LUNO_TEAL (LunoColor){0, 128, 128, 255}
#define LUNO_GOLD (LunoColor){255, 215, 0, 255}
#define LUNO_SILVER (LunoColor){192, 192, 192, 255}
#define LUNO_BEIGE (LunoColor){245, 245, 220, 255}
#define LUNO_IVORY (LunoColor){255, 255, 240, 255}
#define LUNO_KHAKI (LunoColor){240, 230, 140, 255}
#define LUNO_NAVY (LunoColor){0, 0, 128, 255}
#define LUNO_MAROON (LunoColor){128, 0, 0, 255}
#define LUNO_OLIVE (LunoColor){128, 128, 0, 255}
#define LUNO_AQUA (LunoColor){0, 255, 255, 255}
#define LUNO_CORAL (LunoColor){255, 127, 80, 255}
#define LUNO_TAN (LunoColor){210, 180, 140, 255}
#define LUNO_SKYBLUE (LunoColor){135, 206, 235, 255}
#define LUNO_MINT (LunoColor){189, 252, 201, 255}
#define LUNO_PEACH (LunoColor){255, 218, 185, 255}
#define LUNO_CHOCOLATE (LunoColor){210, 105, 30, 255}
#define LUNO_VIOLET (LunoColor){238, 130, 238, 255}
#define LUNO_INDIGO (LunoColor){75, 0, 130, 255}
#define LUNO_TURQUOISE (LunoColor){64, 224, 208, 255}
#define LUNO_SALMON (LunoColor){250, 128, 114, 255}
#define LUNO_WHEAT (LunoColor){245, 222, 179, 255}
```

---

## Data Structures

### LunoPoint

```c
typedef struct {
    int x;
    int y;
} LunoPoint;
```

Represents a 2D point.

---

### LunoColor

```c
typedef struct {
    int r, g, b, a;
} LunoColor;
```

Represents a color with red, green, blue, and alpha components.

---

### LunoRect

```c
typedef struct {
    int x, y, w, h;
} LunoRect;
```

Represents a rectangle.

---

### LunoImage

```c
typedef struct {
    _LunoPixel *pixels;
    int width, height;
} LunoImage;
```

Represents an image, including pixel data and dimensions.

---

### LunoGlyph

```c
typedef struct {
    LunoRect rect;
    int xadv;
} LunoGlyph;
```

Represents a font glyph, including its rectangle and horizontal advance.

---

### LunoFont

```c
typedef struct
{
    int interval;    // Interval in milliseconds.
    int lastTrigger; // Last trigger time in milliseconds.
} LunoTimer;
```

Represents a Timer for interval-based actions.

### LunoTimer

```c
typedef struct {
    LunoImage *image;
    LunoGlyph glyphs[256];
} LunoFont;
```

Represents a font, including its image and glyphs.

---

## Global Variables

### lunoDT

Type: `double`  
Description: Delta time in seconds since the last frame.

---

### lunoFPS

Type: `double`  
Description: The current frames per second.

---

### lunoMS

Type: `int`  
Description: Milliseconds since the application started.

---

## Bindings

- Lua bindings: [Readme](bindings/lua/README.md)

## License

Luno is open-source and available under the [MIT](LICENSE) License.
