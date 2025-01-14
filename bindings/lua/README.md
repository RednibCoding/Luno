# Luno Lua Bindings Documentation

Welcome to the documentation for the Luno Lua bindings. This library provides an interface to integrate Lua scripting with the Luno graphics and utility library, enabling flexible and powerful game scripting.

## Compiliation

You can compile a dedicated `luno.exe` which will have lua bindings build-in.

In the folder `bindings/lua/` you can compile **Luno** with Lua bindings.

- Simply run the `build.bat`. This will create a `luno.exe` in the `./examples` folder.
- Copy this `luno.exe` into a folder of your choice.
- Create a `main.lua` next to it and start coding in lua.
  > Note: `luno.exe` will automatically look for a `main.lua` in the same folder and if found, will run it.

## Binaries

You can find a prebuild `luno.exe` in `bindings/lua/build/` folder.

## Getting Started

### Initialization

Before using Luno functions, the library must be initialized with:

```lua
local luno = require("luno")

if not luno.create("Luno Window", 800, 600, 60) then
    error("Failed to initialize Luno!")
end
```

- **Parameters:**
  - `title` (string): The title of the window.
  - `width` (int): The width of the window in pixels.
  - `height` (int): The height of the window in pixels.
  - `targetFPS` (int): The target frames per second.

### Main Loop

The main game loop must call `luno.update()` to process input and update the screen:

```lua
while luno.update() do
    luno.clear() -- Clears the screen to the background color
    -- Game logic and rendering here
end
```

### Cleanup

Call `luno.close()` to release resources when the program ends:

```lua
luno.close()
```

---

## Functions

### Core Functions

#### `luno.create(title, width, height, targetFPS)`

Initializes the Luno library.

#### `luno.update()`

Processes input and updates the frame.

- **Returns:** `true` if the program should continue, `false` if it should exit.

#### `luno.clear()`

Clears the screen to the background color.

#### `luno.set_window_scale(factor)`

Scales the window size based on the given factor..

#### `luno.set_clear_color(color)`

Sets the background color.

- **Parameters:**
  - `color` (LunoColor or table): The background color.

#### `luno.close()`

Cleans up resources and closes the window.

---

### Drawing Functions

#### `luno.draw_pixel(x, y, color)`

Draws a pixel on the screen.

#### `luno.get_pixel(x, y, color)`

Gets the pixel color of the given image at the location x, y.

#### `luno.draw_rect(rect, color, fill)`

Draws a rectangle.

- **Parameters:**
  - `rect` (LunoRect): The rectangle.
  - `color` (LunoColor or table): The rectangle color.
  - `fill` (bool): Whether the rectangle should be filled.

#### `luno.draw_circle(x, y, radius, color, fill)`

Draws a circle.

#### `luno.draw_line(x1, y1, x2, y2, color)`

Draws a line between two points.

---

### Font Functions

#### `luno.load_font(filePath, glyphWidth, glyphHeight)`

Loads a font from a file.

- **Returns:** A `LunoFont` object.

#### `luno.text_width(text)`

Gets the width of a string in pixels using the current font.

#### `luno.text_height()`

Gets the height of the current font in pixels.

#### `luno.reset_font()`

Resets to the default font.

#### `luno.draw_text(text, x, y, color)`

Draws text on the screen.

---

### Input Functions

#### `luno.is_key_pressed(key)`

Checks if a key was pressed this frame.

#### `luno.is_key_held(key)`

Checks if a key is currently held down.

#### `luno.is_key_released(key)`

Checks if a key was released this frame.

#### `luno.is_mouse_button_pressed(button)`

Checks if a mouse button was pressed this frame.

#### `luno.is_mouse_button_held(button)`

Checks if a mouse button is currently held down.

#### `luno.is_mouse_button_released(button)`

Checks if a mouse button was released this frame.

#### `luno.mouse_position()`

Gets the current mouse position.

- **Returns:** A `LunoPoint`.

#### `luno.mouse_delta()`

Gets the mouse movement delta since the last frame.

#### `luno.mouse_wheel_delta()`

Gets the mouse wheel delta since the last frame.

---

### Collision Detection Functions

#### `luno.point_rec_overlaps(x, y, rect)`

Checks if a point overlaps a rectangle.

#### `luno.recs_overlap(rect1, rect2)`

Checks if two rectangles overlap.

#### `luno.point_circle_overlaps(x, y, cx, cy, radius)`

Checks if a point overlaps a circle.

#### `luno.rec_circle_overlaps(rect, cx, cy, radius)`

Checks if a rectangle overlaps a circle.

#### `luno.circles_overlap(cx1, cy1, radius1, cx2, cy2, radius2)`

Checks if two circles overlap.

---

### Timer Functions

#### `luno.create_timer(interval)`

Creates a timer with the specified interval (in milliseconds).

- **Returns:** A `LunoTimer` object.

#### `timer:ticked()`

Checks if the timer interval has elapsed this frame.

#### `timer:elapsed()`

Gets the elapsed time in milliseconds since the timer was created or reset.

#### `timer:reset()`

Resets the timer to start counting from now.

---

### Cursor Functions

#### `luno.set_cursor_visibility(visible)`

Sets the cursor visibility.

#### `luno.is_cursor_visible()`

Checks if the cursor is visible.

---

## Data Structures

### `LunoPoint`

Represents a 2D point.

- **Fields:**
  - `x` (int): X-coordinate.
  - `y` (int): Y-coordinate.

### `LunoRect`

Defines a rectangle with position and dimensions.

- **Fields:**
  - `x` (int): X-coordinate.
  - `y` (int): Y-coordinate.
  - `w` (int): Width.
  - `h` (int): Height.

### `LunoColor`

Represents an RGBA color.

- **Fields:**
  - `r` (int): Red.
  - `g` (int): Green.
  - `b` (int): Blue.
  - `a` (int): Alpha (optional, defaults to 255).

### `LunoTimer`

Represents a timer.

- **Methods:**
  - `ticked()`
  - `elapsed()`
  - `reset()`

---

## Examples

### Drawing a Moving Rectangle

```lua
local luno = require("luno")

if not luno.create("Moving Rectangle", 800, 600, 60) then
    error("Failed to initialize Luno!")
end

local rect = luno.rect(100, 100, 200, 150)
local speed = 100

while luno.update() do
    luno.clear()
    rect.x = rect.x + speed * luno.get_dt()
    if rect.x + rect.w > 800 or rect.x < 0 then
        speed = -speed
    end
    luno.draw_rect(rect, luno.RED, true)
end

luno.close()
```
