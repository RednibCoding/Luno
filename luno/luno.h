#ifndef LUNO_H
#define LUNO_H

#include <windows.h>
#include <windowsx.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MSC_VER
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")
#endif

#define LUNO_WHITE (LunoColor){255, 255, 255, 255}
#define LUNO_BLACK (LunoColor){0, 0, 0, 255}
#define LUNO_GRAY (LunoColor){128, 128, 128, 255}
#define LUNO_DARKGRAY (LunoColor){64, 64, 64, 255}
#define LUNO_RED (LunoColor){255, 0, 0, 255}
#define LUNO_GREEN (LunoColor){0, 255, 0, 255}
#define LUNO_BLUE (LunoColor){0, 0, 255, 255}
#define LUNO_YELLOW (LunoColor){255, 255, 0, 255}
#define LUNO_CYAN (LunoColor){0, 255, 255, 255}
#define LUNO_MAGENTA (LunoColor){255, 0, 255, 255}
#define LUNO_LIGHTGRAY (LunoColor){211, 211, 211, 255}
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

    /** Structs **/

    typedef struct
    {
        int x;
        int y;
    } LunoPoint; // Represents a 2D point.

    typedef struct
    {
        int r, g, b, a;
    } LunoColor; // Represents an RGBA color.

    typedef struct
    {
        int x, y, w, h;
    } LunoRect; // Defines a rectangle with position and dimensions.

    typedef struct
    {
        unsigned char r, g, b, a;
    } _LunoPixel; // Internal pixel representation for images.

    typedef struct
    {
        _LunoPixel *pixels;
        int width, height;
    } LunoImage; // Represents an image or a buffer.

    typedef struct
    {
        int interval;    // Interval in milliseconds.
        int lastTrigger; // Last trigger time in milliseconds.
    } LunoTimer;         // Timer for interval-based actions.

    typedef struct
    {
        LunoRect rect; // Portion of the image representing the glyph.
        int xadv;      // Horizontal advance after drawing the glyph.
    } LunoGlyph;       // Represents a single character in a font.

    typedef struct
    {
        LunoImage *image;      // Image containing all glyphs.
        LunoGlyph glyphs[256]; // Glyphs for ASCII characters.
    } LunoFont;                // Represents a bitmap font.

    double lunoDT;  // Delta time in seconds since the last frame.
    double lunoFPS; // Current frames per second.
    int lunoMS;     // Milliseconds since the application started.

    /** Initialization and Cleanup **/

    // Creates a window and initializes Luno.
    bool Luno_Create(const char *title, int width, int height, int targetFPS);

    // Cleans up resources and closes the window.
    void Luno_Close();

    /** Window Management **/

    // Scales the window size based on the given factor.
    void Luno_SetWindowScale(int factor);

    /** Rendering Control **/

    // Sets the clear color for the screen.
    void Luno_SetClearColor(LunoColor color);

    // Clears the screen to the clear color.
    void Luno_Clear();

    /** Drawing Functions **/

    // Draws a single pixel on the screen.
    void Luno_DrawPixel(int x, int y, LunoColor color);

    // Gets the pixel color of the given image at the location x, y.
    LunoColor Luno_GetPixel(LunoImage *image, int x, int y);

    // Creates a blank image with the given dimensions.
    LunoImage *Luno_CreateImage(int width, int height);

    // Loads an image from a file.
    LunoImage *Luno_LoadImage(const char *filePath);

    // Loads an image from memory.
    LunoImage *Luno_LoadImageMem(const char *buffer, int bufferLen);

    // Fills an image with a specified color.
    void Luno_FillImage(LunoImage *image, LunoColor color);

    // Draws an image at the specified position.
    void Luno_DrawImage(LunoImage *image, int x, int y);

    // Draws a portion of an image at the specified position.
    void Luno_DrawImageRect(LunoImage *image, int x, int y, LunoRect srcRect);

    // Frees the memory associated with an image.
    void Luno_DestroyImage(LunoImage *image);

    // Draws a rectangle (filled or outlined).
    void Luno_DrawRect(LunoRect rect, LunoColor color, bool fill);

    // Draws a circle (filled or outlined).
    void Luno_DrawCircle(int x, int y, int radius, LunoColor color, bool fill);

    // Draws a line between two points.
    void Luno_DrawLine(int x1, int y1, int x2, int y2, LunoColor color);

    /** Update Loop **/

    // Processes input and updates the frame.
    bool Luno_Update();

    /** Input Handling **/

    // Checks if a key was pressed this frame.
    bool Luno_IsKeyPressed(int key);

    // Checks if a key is currently held down.
    bool Luno_IsKeyHeld(int key);

    // Checks if a key was released this frame.
    bool Luno_IsKeyReleased(int key);

    // Checks if a mouse button was pressed this frame.
    bool Luno_IsMouseButtonPressed(int button);

    // Checks if a mouse button is currently held down.
    bool Luno_IsMouseButtonHeld(int button);

    // Checks if a mouse button was released this frame.
    bool Luno_IsMouseButtonReleased(int button);

    // Returns the current mouse position.
    LunoPoint Luno_MousePosition();

    // Returns the mouse movement delta since the last frame.
    LunoPoint Luno_MouseDelta();

    // Returns the mouse wheel delta since the last frame.
    int Luno_MouseWheelDelta();

    /** Cursor Control **/

    // Sets the cursor visibility.
    void Luno_SetCursorVisibility(bool visible);

    // Checks if the cursor is visible.
    bool Luno_IsCursorVisible();

    /** Timers **/

    // Creates a timer with a specified interval (in milliseconds).
    LunoTimer Luno_CreateTimer(int interval);

    // Checks if the timer interval has elapsed this frame.
    bool Luno_TimerTicked(LunoTimer *timer);

    // Resets a timer to start counting from now.
    void Luno_ResetTimer(LunoTimer *timer);

    // Returns the elapsed time in milliseconds since the timer was created.
    int Luno_TimerElapsed(LunoTimer *timer);

    /** Font Handling **/

    // Creates a font from an image.
    LunoFont *Luno_FontFromImage(LunoImage *image, int glyphWidth, int glyphHeight);

    // Loads a font from a file.
    LunoFont *Luno_LoadFont(const char *filePath, int glyphWidth, int glyphHeight);

    // Loads a font from memory.
    LunoFont *Luno_LoadFontMem(const char *buffer, int bufferLen, int glyphWidth, int glyphHeight);

    // Resets the font to the default font.
    void Luno_ResetFont();

    // Returns the width of a string in pixels.
    int Luno_TextWidth(const char *text);

    // Returns the height of the current font in pixels.
    int Luno_TextHeight();

    // Frees the memory associated with a font.
    void Luno_DestroyFont(LunoFont *font);

    // Draws a string at the specified position.
    void Luno_DrawText(const char *text, int x, int y, LunoColor color);

    // Draws a formatted string at the specified position.
    void Luno_DrawTextF(const char *format, int x, int y, LunoColor color, ...);

    /** Collision Detection **/

    // Checks if a point overlaps a rectangle.
    bool Luno_PointRecOverlaps(int x, int y, LunoRect rec);

    // Checks if two rectangles overlap.
    bool Luno_RecsOverlap(LunoRect rec1, LunoRect rec2);

    // Checks if a point overlaps a circle.
    bool Luno_PointCircleOverlaps(int x, int y, int cx, int cy, float circleRadius);

    // Checks if a rectangle overlaps a circle.
    bool Luno_RecCircleOverlaps(LunoRect rec, int cx, int cy, float circleRadius);

    // Checks if two circles overlap.
    bool Luno_CirclesOverlaps(int cx1, int cy1, float circle1Radius, int cx2, int cy2, float circle2Radius);

#ifdef __cplusplus
}
#endif

#endif // LUNO_H

#define LUNO_IMPL
#ifdef LUNO_IMPL

#ifdef __cplusplus
extern "C"
{
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include "include/embedded_font.h"

    // --- Types ---
    typedef struct
    {
        const char *title;
        HWND hwnd;
        HDC hdc;
        LunoImage backbuffer;
        LunoColor clearColor;
        bool keys[256];
        bool keysPrev[256];
        bool mouseButtons[3];
        bool mouseButtonsPrev[3];
        struct
        {
            int x, y;
        } mousePos, mouseDelta;
        int mouseWheelDelta;
        int windowWidth, windowHeight;
        bool isCursorHidden;
        double stepTime;
        double prevTime;
        double startTime;
        LunoFont *currentFont;
        LunoFont *defaultFont;
    } _LunoContext;

    // --- Global Variables ---
    static _LunoContext _lunoContext = {0};

    // --- Private Helpers ---

    static double _Luno_Now(void)
    {
        return clock() / 1000.0;
    }

    static inline _LunoPixel _Luno_BlendPixel(_LunoPixel dst, _LunoPixel src)
    {
        _LunoPixel res;
        res.r = dst.r + (((src.r - dst.r) * src.a) >> 8);
        res.g = dst.g + (((src.g - dst.g) * src.a) >> 8);
        res.b = dst.b + (((src.b - dst.b) * src.a) >> 8);
        res.a = dst.a; // Preserve destination alpha
        return res;
    }

    static LunoRect _Luno_GetAdjustedWindowRect(_LunoContext *ctx)
    {
        // work out maximum size to retain aspect ratio
        float src_ar = (float)ctx->backbuffer.height / ctx->backbuffer.width;
        float dst_ar = (float)ctx->windowHeight / ctx->windowWidth;
        int w, h;
        if (src_ar < dst_ar)
        {
            w = ctx->windowWidth;
            h = ceil(w * src_ar);
        }
        else
        {
            h = ctx->windowHeight;
            w = ceil(h / src_ar);
        }
        // return centered rect
        return (LunoRect){(ctx->windowWidth - w) / 2, (ctx->windowHeight - h) / 2, w, h};
    }

    LRESULT CALLBACK _LunoWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_PAINT:
        {
            BITMAPINFO bmi = {0};
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = _lunoContext.backbuffer.width;
            bmi.bmiHeader.biHeight = -_lunoContext.backbuffer.height; // Negative for top-down orientation
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;

            LunoRect wr = _Luno_GetAdjustedWindowRect(&_lunoContext);

            StretchDIBits(_lunoContext.hdc,
                          wr.x, wr.y, wr.w, wr.h,
                          0, 0, _lunoContext.backbuffer.width, _lunoContext.backbuffer.height,
                          _lunoContext.backbuffer.pixels, &bmi, DIB_RGB_COLORS, SRCCOPY);

            ValidateRect(_lunoContext.hwnd, 0);
            break;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            if (lParam & (1 << 30))
            { // key repeat
                break;
            }
            _lunoContext.keys[wParam] = true;
            break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
            _lunoContext.keys[wParam] = false;
            break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        {
            int button = (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP) ? 0 : (message == WM_RBUTTONDOWN || message == WM_RBUTTONUP) ? 1
                                                                                                                                             : 2;

            if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN)
            {
                SetCapture(hwnd);
                _lunoContext.mouseButtons[button] = true;
            }
            else
            {
                ReleaseCapture();
                _lunoContext.mouseButtons[button] = false;
            }
            break;
        }
        case WM_MOUSEMOVE:
        {
            LunoRect wr = _Luno_GetAdjustedWindowRect(&_lunoContext);
            int prevx = _lunoContext.mousePos.x;
            int prevy = _lunoContext.mousePos.y;

            // Calculate the unclamped mouse position
            int unclampedX = (GET_X_LPARAM(lParam) - wr.x) * _lunoContext.backbuffer.width / wr.w;
            int unclampedY = (GET_Y_LPARAM(lParam) - wr.y) * _lunoContext.backbuffer.height / wr.h;

            // Clamp the mouse position to the backbuffer dimensions
            _lunoContext.mousePos.x = max(0, min(unclampedX, _lunoContext.backbuffer.width - 1));
            _lunoContext.mousePos.y = max(0, min(unclampedY, _lunoContext.backbuffer.height - 1));

            // Calculate the delta
            _lunoContext.mouseDelta.x += _lunoContext.mousePos.x - prevx;
            _lunoContext.mouseDelta.y += _lunoContext.mousePos.y - prevy;

            break;
        }

        case WM_MOUSEWHEEL:
        {
            _lunoContext.mouseWheelDelta += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            break;
        }

        case WM_SETCURSOR:
            if (_lunoContext.isCursorHidden && LOWORD(lParam) == HTCLIENT)
            {
                SetCursor(0);
                break;
            }
            goto unhandled;
        case WM_SIZE:
        {
            if (wParam != SIZE_MINIMIZED)
            {
                // Update window dimensions
                _lunoContext.windowWidth = LOWORD(lParam);
                _lunoContext.windowHeight = HIWORD(lParam);

                // Clear the window
                RECT clientRect;
                GetClientRect(hwnd, &clientRect);
                HBRUSH brush = CreateSolidBrush(RGB(_lunoContext.clearColor.b, _lunoContext.clearColor.g, _lunoContext.clearColor.r));
                FillRect(_lunoContext.hdc, &clientRect, brush);
                DeleteObject(brush);

                // Redraw the window with the updated size
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
            }
            break;
        }

        case WM_CLOSE:
        case WM_QUIT:
            PostQuitMessage(0);
            break;
        default:
        unhandled:
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
        return 0;
    }

    static void _Luno_BlitImage(LunoImage *dst, LunoImage *src, int x, int y)
    {
        for (int j = 0; j < src->height; j++)
        {
            int dstY = y + j;
            if (dstY < 0 || dstY >= dst->height)
                continue; // Skip rows outside the destination bounds

            for (int i = 0; i < src->width; i++)
            {
                int dstX = x + i;
                if (dstX < 0 || dstX >= dst->width)
                    continue; // Skip columns outside the destination bounds

                _LunoPixel *dstPixel = &dst->pixels[dstX + dstY * dst->width];
                _LunoPixel srcPixel = src->pixels[i + j * src->width];
                *dstPixel = _Luno_BlendPixel(*dstPixel, srcPixel);
            }
        }
    }

    // --- Public Interface Implementation ---

    bool Luno_Create(const char *title, int width, int height, int targetFPS)
    {
        if (targetFPS > 0)
        {
            _lunoContext.stepTime = 1.0 / targetFPS;
        }

        _lunoContext.isCursorHidden = false;

        WNDCLASSA wc = {0};
        wc.lpfnWndProc = _LunoWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = title;

        if (!RegisterClassA(&wc))
        {
            return false;
        }

        _lunoContext.title = title;

        _lunoContext.hwnd = CreateWindowA(
            title,
            title,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            NULL, NULL, GetModuleHandle(NULL), NULL);

        if (!_lunoContext.hwnd)
        {
            return false;
        }

        _lunoContext.hdc = GetDC(_lunoContext.hwnd);

        // Initialize back buffer
        _lunoContext.backbuffer.width = width;
        _lunoContext.backbuffer.height = height;
        _lunoContext.backbuffer.pixels = (_LunoPixel *)calloc(width * height, sizeof(_LunoPixel));
        if (!_lunoContext.backbuffer.pixels)
        {
            return false;
        }

        _lunoContext.windowWidth = width;
        _lunoContext.windowHeight = height;
        _lunoContext.clearColor = (LunoColor){0, 0, 0, 0};
        _lunoContext.prevTime = 0;
        _lunoContext.startTime = _Luno_Now();

        lunoFPS = 0;
        lunoDT = 0;
        lunoMS = 0;

        // Load the default font
        _lunoContext.defaultFont = Luno_LoadFontMem(_lunoFontPngData, _lunoFontPngDataSize, _lunoFontWidth, _lunoFontHeight);
        _lunoContext.currentFont = _lunoContext.defaultFont;

        return true;
    }

    void Luno_Close()
    {
        // Clean up custom back buffer
        if (_lunoContext.backbuffer.pixels)
        {
            free(_lunoContext.backbuffer.pixels);
            _lunoContext.backbuffer.pixels = NULL;
        }
        if (_lunoContext.hdc)
        {
            ReleaseDC(_lunoContext.hwnd, _lunoContext.hdc);
            _lunoContext.hdc = NULL;
        }
        if (_lunoContext.hwnd)
        {
            DestroyWindow(_lunoContext.hwnd);
            _lunoContext.hwnd = NULL;
        }
        UnregisterClassA(_lunoContext.title, GetModuleHandle(NULL));
    }

    void Luno_SetWindowScale(int factor)
    {
        if (factor <= 0)
        {
            return; // Invalid factor
        }

        // Calculate the new dimensions
        int newWidth = _lunoContext.backbuffer.width * factor;
        int newHeight = _lunoContext.backbuffer.height * factor;

        // Update the window size
        SetWindowPos(
            _lunoContext.hwnd,
            NULL,
            0, 0,
            newWidth,
            newHeight,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

        // Update _lunoContext values
        _lunoContext.windowWidth = newWidth;
        _lunoContext.windowHeight = newHeight;
    }

    void Luno_Clear()
    {
        Luno_FillImage(&_lunoContext.backbuffer, _lunoContext.clearColor);
    }

    void Luno_SetClearColor(LunoColor color)
    {
        _lunoContext.clearColor = color;
    }

    void Luno_DrawPixel(int x, int y, LunoColor color)
    {
        if (color.a <= 0)
            return; // Skip fully transparent pixels

        if (x < 0 || y < 0 || x >= _lunoContext.backbuffer.width || y >= _lunoContext.backbuffer.height)
        {
            return;
        }

        _LunoPixel *pixel = &_lunoContext.backbuffer.pixels[x + y * _lunoContext.backbuffer.width];
        _LunoPixel src = {color.b, color.g, color.r, color.a}; // Convert LunoColor to LunoPixel
        *pixel = _Luno_BlendPixel(*pixel, src);
    }

    LunoColor Luno_GetPixel(LunoImage *image, int x, int y)
    {
        if (!image || x < 0 || y < 0 || x >= image->width || y >= image->height)
        {
            // Return a fully transparent color for invalid coordinates or null image
            return (LunoColor){0, 0, 0, 0};
        }

        _LunoPixel *pixel = &image->pixels[x + y * image->width];
        return (LunoColor){pixel->r, pixel->g, pixel->b, pixel->a};
    }

    LunoImage *Luno_CreateImage(int width, int height)
    {
        LunoImage *image = (LunoImage *)malloc(sizeof(LunoImage));
        if (!image)
            return NULL;

        image->width = width;
        image->height = height;
        image->pixels = (_LunoPixel *)calloc(width * height, sizeof(_LunoPixel));
        if (!image->pixels)
        {
            image->width = 0;
            image->height = 0;
        }
        return image;
    }

    LunoImage *Luno_LoadImageMem(const char *buffer, int bufferLen)
    {
        if (!buffer || bufferLen <= 0)
        {
            printf("ERROR <Luno_LoadImageMem>: Invalid Image buffer!");
            return NULL;
        }

        LunoImage *image = (LunoImage *)malloc(sizeof(LunoImage));
        if (!image)
            return NULL;

        int channels;
        unsigned char *data = stbi_load_from_memory((const unsigned char *)buffer, bufferLen, &image->width, &image->height, &channels, STBI_rgb_alpha);
        if (!data)
        {
            free(image);
            return NULL;
        }

        image->pixels = (_LunoPixel *)calloc(image->width * image->height, sizeof(_LunoPixel));
        if (!image->pixels)
        {
            stbi_image_free(data);
            free(image);
            return NULL;
        }

        // Convert pixel data to LunoPixel format
        for (int y = 0; y < image->height; y++)
        {
            for (int x = 0; x < image->width; x++)
            {
                int index = (y * image->width + x) * 4;
                _LunoPixel *pixel = &image->pixels[y * image->width + x];
                pixel->r = data[index + 0];
                pixel->g = data[index + 1];
                pixel->b = data[index + 2];
                pixel->a = data[index + 3];
            }
        }

        stbi_image_free(data);
        return image;
    }

    LunoImage *Luno_LoadImage(const char *filePath)
    {
        if (!filePath)
        {
            printf("ERROR <Luno_LoadImage>: No image path provided!");
            return NULL;
        }

        FILE *file = fopen(filePath, "rb");
        if (!file)
        {
            printf("ERROR <Luno_LoadImage>: Unable to open image file: %s\n", filePath);
            return NULL;
        }

        fseek(file, 0, SEEK_END);
        int fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *buffer = (char *)malloc(fileSize);
        if (!buffer)
        {
            fclose(file);
            return NULL;
        }

        fread(buffer, 1, fileSize, file);
        fclose(file);

        LunoImage *image = Luno_LoadImageMem(buffer, fileSize);
        free(buffer);
        return image;
    }

    void Luno_FillImage(LunoImage *image, LunoColor color)
    {
        if (!image || !image->pixels)
        {
            printf("ERROR <Luno_FillImage>: Invalid image!");
            return;
        }

        _LunoPixel pixel = {color.b, color.g, color.r, color.a};
        for (int i = 0; i < image->width * image->height; i++)
        {
            image->pixels[i] = pixel;
        }
    }

    void Luno_DrawImage(LunoImage *image, int x, int y)
    {
        _Luno_BlitImage(&_lunoContext.backbuffer, image, x, y);
    }

    void Luno_DrawImageRect(LunoImage *image, int x, int y, LunoRect srcRect)
    {
        if (!image || !image->pixels)
        {
            printf("ERROR <Luno_DrawImageRect>: Invalid image!");
            return;
        }

        // Clamp the source rectangle to the bounds of the image
        int srcXEnd = min(srcRect.x + srcRect.w, image->width);
        int srcYEnd = min(srcRect.y + srcRect.h, image->height);

        for (int j = srcRect.y; j < srcYEnd; j++)
        {
            int dstY = y + (j - srcRect.y);
            if (dstY < 0 || dstY >= _lunoContext.backbuffer.height)
                continue; // Skip rows outside the backbuffer bounds

            for (int i = srcRect.x; i < srcXEnd; i++)
            {
                int dstX = x + (i - srcRect.x);
                if (dstX < 0 || dstX >= _lunoContext.backbuffer.width)
                    continue; // Skip columns outside the backbuffer bounds

                _LunoPixel *dstPixel = &_lunoContext.backbuffer.pixels[dstX + dstY * _lunoContext.backbuffer.width];
                _LunoPixel srcPixel = image->pixels[i + j * image->width];
                *dstPixel = _Luno_BlendPixel(*dstPixel, srcPixel);
            }
        }
    }

    void Luno_DestroyImage(LunoImage *image)
    {
        if (image && image->pixels)
        {
            free(image->pixels);
            image->pixels = NULL;
            image->width = 0;
            image->height = 0;
        }
    }

    void Luno_DrawLine(int x1, int y1, int x2, int y2, LunoColor color)
    {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            Luno_DrawPixel(x1, y1, color);
            if (x1 == x2 && y1 == y2)
                break;
            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y1 += sy;
            }
        }
    }

    void Luno_DrawRect(LunoRect rect, LunoColor color, bool fill)
    {
        if (fill)
        {
            for (int y = rect.y; y < rect.y + rect.h; y++)
            {
                Luno_DrawLine(rect.x, y, rect.x + rect.w - 1, y, color);
            }
        }
        else
        {
            Luno_DrawLine(rect.x, rect.y, rect.x + rect.w - 1, rect.y, color);                           // Top border
            Luno_DrawLine(rect.x, rect.y + rect.h - 1, rect.x + rect.w - 1, rect.y + rect.h - 1, color); // Bottom border
            Luno_DrawLine(rect.x, rect.y, rect.x, rect.y + rect.h - 1, color);                           // Left border
            Luno_DrawLine(rect.x + rect.w - 1, rect.y, rect.x + rect.w - 1, rect.y + rect.h - 1, color); // Right border
        }
    }

    void Luno_DrawCircle(int x, int y, int radius, LunoColor color, bool fill)
    {
        int px = 0;
        int py = radius;
        int d = 1 - radius;

        while (px <= py)
        {
            // Draw symmetric points for the current pixel
            if (fill)
            {
                for (int i = -py; i <= py; i++)
                {
                    Luno_DrawPixel(x + px, y + i, color);
                    Luno_DrawPixel(x - px, y + i, color);
                }
                for (int i = -px; i <= px; i++)
                {
                    Luno_DrawPixel(x + py, y + i, color);
                    Luno_DrawPixel(x - py, y + i, color);
                }
            }
            else
            {
                // Draw only border pixels
                Luno_DrawPixel(x + px, y + py, color);
                Luno_DrawPixel(x - px, y + py, color);
                Luno_DrawPixel(x + px, y - py, color);
                Luno_DrawPixel(x - px, y - py, color);
                Luno_DrawPixel(x + py, y + px, color);
                Luno_DrawPixel(x - py, y + px, color);
                Luno_DrawPixel(x + py, y - px, color);
                Luno_DrawPixel(x - py, y - px, color);
            }

            // Update the decision parameter and pixel positions
            if (d < 0)
            {
                d += 2 * px + 3;
            }
            else
            {
                d += 2 * (px - py) + 5;
                py--;
            }
            px++;
        }
    }

    bool Luno_Update()
    {
        // present
        // RedrawWindow(_lunoContext.hwnd, 0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
        InvalidateRect(_lunoContext.hwnd, NULL, FALSE);

        double now = GetTickCount64() / 1000.0;
        double wait = (_lunoContext.prevTime + _lunoContext.stepTime) - now;
        double prev = _lunoContext.prevTime;

        if (wait > 0)
        {
            Sleep((DWORD)(wait * 1000));
            _lunoContext.prevTime += _lunoContext.stepTime;
        }
        else
        {
            _lunoContext.prevTime = now;
        }

        lunoDT = _lunoContext.prevTime - prev;
        lunoFPS = (lunoDT > 0) ? (1.0 / lunoDT) : 0;
        lunoMS = (int)((_lunoContext.prevTime - _lunoContext.startTime) * 1000);

        if (lunoDT > _lunoContext.stepTime * 10)
        {
            lunoDT = _lunoContext.stepTime;
        }

        for (int i = 0; i < 256; i++)
        {
            _lunoContext.keysPrev[i] = _lunoContext.keys[i];
        }
        for (int i = 0; i < 3; i++)
        {
            _lunoContext.mouseButtonsPrev[i] = _lunoContext.mouseButtons[i];
        }

        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true;
    }

    bool Luno_IsKeyPressed(int key)
    {
        return _lunoContext.keys[key] && !_lunoContext.keysPrev[key];
    }

    bool Luno_IsKeyHeld(int key)
    {
        return _lunoContext.keys[key];
    }

    bool Luno_IsKeyReleased(int key)
    {
        return !_lunoContext.keys[key] && _lunoContext.keysPrev[key];
    }

    bool Luno_IsMouseButtonPressed(int button)
    {
        return _lunoContext.mouseButtons[button] && !_lunoContext.mouseButtonsPrev[button];
    }

    bool Luno_IsMouseButtonHeld(int button)
    {
        return _lunoContext.mouseButtons[button];
    }

    bool Luno_IsMouseButtonReleased(int button)
    {
        return !_lunoContext.mouseButtons[button] && _lunoContext.mouseButtonsPrev[button];
    }

    LunoPoint Luno_MousePosition()
    {
        LunoPoint pos = {_lunoContext.mousePos.x, _lunoContext.mousePos.y};
        return pos;
    }

    LunoPoint Luno_MouseDelta()
    {
        LunoPoint delta = {_lunoContext.mouseDelta.x, _lunoContext.mouseDelta.y};
        _lunoContext.mouseDelta.x = 0;
        _lunoContext.mouseDelta.y = 0;
        return delta;
    }

    int Luno_MouseWheelDelta()
    {
        int delta = _lunoContext.mouseWheelDelta;
        _lunoContext.mouseWheelDelta = 0;
        return delta;
    }

    void Luno_SetCursorVisibility(bool visible)
    {
        _lunoContext.isCursorHidden = !visible;

        // Update the cursor state
        if (visible)
        {
            SetCursor(LoadCursor(NULL, IDC_ARROW)); // Restore default cursor
        }
        else
        {
            SetCursor(NULL); // Hide the cursor
        }

        // Force cursor re-evaluation for the client area
        if (_lunoContext.hwnd)
        {
            PostMessage(_lunoContext.hwnd, WM_SETCURSOR, 0, HTCLIENT);
        }
    }

    bool Luno_IsCursorVisible()
    {
        return !_lunoContext.isCursorHidden;
    }

    LunoTimer Luno_CreateTimer(int interval)
    {
        LunoTimer timer;
        timer.interval = interval;
        timer.lastTrigger = (int)(_Luno_Now() * 1000);
        return timer;
    }

    bool Luno_TimerTicked(LunoTimer *timer)
    {
        int now = (int)(_Luno_Now() * 1000);
        if ((now - timer->lastTrigger) >= timer->interval)
        {
            timer->lastTrigger = now;
            return true;
        }
        return false;
    }

    void Luno_ResetTimer(LunoTimer *timer)
    {
        timer->lastTrigger = (int)(_Luno_Now() * 1000);
    }

    int Luno_TimerElapsed(LunoTimer *timer)
    {
        int now = (int)(_Luno_Now() * 1000);
        return now - timer->lastTrigger;
    }

    LunoFont *Luno_FontFromImage(LunoImage *image, int glyphWidth, int glyphHeight)
    {
        LunoFont *font = (LunoFont *)malloc(sizeof(LunoFont));
        if (!font)
            return NULL;

        if (glyphWidth <= 0 || glyphHeight <= 0 || image->width % glyphWidth != 0 || image->height % glyphHeight != 0)
        {
            free(font);
            return NULL;
        }

        font->image = image;

        int charWidth = image->width / glyphWidth;
        int charHeight = image->height / glyphHeight;

        for (int i = 0; i < 256; i++)
        {
            LunoGlyph *glyph = &font->glyphs[i];
            glyph->rect.x = (i % glyphWidth) * charWidth;
            glyph->rect.y = (i / glyphHeight) * charHeight;
            glyph->rect.w = charWidth;
            glyph->rect.h = charHeight;
            glyph->xadv = charWidth; // Default advance is the character width
        }

        return font;
    }

    LunoFont *Luno_LoadFont(const char *filePath, int glyphWidth, int glyphHeight)
    {
        LunoImage *fontImage = Luno_LoadImage(filePath);

        if (!fontImage)
            return NULL;

        return Luno_FontFromImage(fontImage, glyphWidth, glyphHeight);
    }

    LunoFont *Luno_LoadFontMem(const char *buffer, int bufferLen, int glyphWidth, int glyphHeight)
    {
        LunoImage *fontImage = Luno_LoadImageMem(buffer, bufferLen);
        if (!fontImage)
            return NULL;

        return Luno_FontFromImage(fontImage, glyphWidth, glyphHeight);
    }

    void Luno_DestroyFont(LunoFont *font)
    {
        if (!font)
            return;
        free(font);
    }

    void Luno_SetFont(LunoFont *font)
    {
        if (!font)
            return;
        _lunoContext.currentFont = font;
    }

    void Luno_ResetFont()
    {
        _lunoContext.currentFont = _lunoContext.defaultFont;
    }

    int Luno_TextWidth(const char *text)
    {
        if (!_lunoContext.currentFont || !text)
            return 0;

        int width = 0;
        for (const char *p = text; *p; p++)
        {
            unsigned char c = *p;
            LunoGlyph *glyph = &_lunoContext.currentFont->glyphs[c];
            width += glyph->xadv; // Add the horizontal advance of each glyph
        }

        return width;
    }

    int Luno_TextHeight()
    {
        if (!_lunoContext.currentFont)
            return 0;

        // The height of the font is determined by the glyph image's height
        return _lunoContext.currentFont->glyphs['A'].rect.h; // Use a representative glyph (e.g., 'A')
    }

    void Luno_DrawTextF(const char *format, int x, int y, LunoColor color, ...)
    {
        va_list args;
        va_start(args, color);

        char buffer[1024] = {0}; // Buffer for formatted text
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        // Call Luno_DrawText with the formatted string
        Luno_DrawText(buffer, x, y, color);
    }

    void Luno_DrawText(const char *text, int x, int y, LunoColor color)
    {
        if (!_lunoContext.currentFont || !text)
        {
            printf("ERROR: <Luno_DrawText>: No font set!\n");
            return;
        }

        for (const char *p = text; *p; p++)
        {
            unsigned char c = *p;
            LunoGlyph *glyph = &_lunoContext.currentFont->glyphs[c];

            for (int j = 0; j < glyph->rect.h; j++)
            {
                for (int i = 0; i < glyph->rect.w; i++)
                {
                    int srcX = glyph->rect.x + i;
                    int srcY = glyph->rect.y + j;
                    int dstX = x + i;
                    int dstY = y + j;

                    if (dstX < 0 || dstY < 0 || dstX >= _lunoContext.backbuffer.width || dstY >= _lunoContext.backbuffer.height)
                        continue;

                    _LunoPixel *srcPixel = &_lunoContext.currentFont->image->pixels[srcX + srcY * _lunoContext.currentFont->image->width];
                    if (srcPixel->a == 0)
                        continue; // Skip fully transparent pixels

                    // Blend the glyph pixel with the provided text color
                    _LunoPixel textColor = {color.b, color.g, color.r, color.a};
                    _LunoPixel blendedPixel = _Luno_BlendPixel(*srcPixel, textColor);

                    // Write the blended pixel to the backbuffer
                    _LunoPixel *dstPixel = &_lunoContext.backbuffer.pixels[dstX + dstY * _lunoContext.backbuffer.width];
                    *dstPixel = _Luno_BlendPixel(*dstPixel, blendedPixel);
                }
            }

            x += glyph->xadv; // Advance the x position
        }
    }

    bool Luno_PointRecOverlaps(int x, int y, LunoRect rec)
    {
        return (x >= rec.x && x <= rec.x + rec.w && y >= rec.y && y <= rec.y + rec.h) ? true : false;
    }

    bool Luno_RecsOverlap(LunoRect rec1, LunoRect rec2)
    {
        return (rec1.x < rec2.x + rec2.w && rec1.x + rec1.w > rec2.x && rec1.y < rec2.y + rec2.h && rec1.y + rec1.h > rec2.y) ? true : false;
    }

    bool Luno_PointCircleOverlaps(int x, int y, int cx, int cy, float circleRadius)
    {
        float dx = x - cx;
        float dy = y - cy;
        return (dx * dx + dy * dy <= circleRadius * circleRadius) ? true : false;
    }

    bool Luno_RecCircleOverlaps(LunoRect rec, int cx, int cy, float circleRadius)
    {
        // Find the closest point on the rectangle to the circle center
        float closestX = (cx < rec.x) ? rec.x : (cx > rec.x + rec.w) ? rec.x + rec.w
                                                                     : cx;
        float closestY = (cy < rec.y) ? rec.y : (cy > rec.y + rec.h) ? rec.y + rec.h
                                                                     : cy;

        // Calculate the distance between the circle center and this closest point
        float dx = cx - closestX;
        float dy = cy - closestY;

        return (dx * dx + dy * dy <= circleRadius * circleRadius) ? true : false;
    }

    bool Luno_CirclesOverlaps(int cx1, int cy1, float circle1Radius, int cx2, int cy2, float circle2Radius)
    {
        float dx = cx1 - cx2;
        float dy = cy1 - cy2;
        float distanceSquared = dx * dx + dy * dy;
        float radiusSum = circle1Radius + circle2Radius;
        return (distanceSquared <= radiusSum * radiusSum) ? true : false;
    }

#ifdef __cplusplus
}
#endif

#endif // LUNO_IMPL
