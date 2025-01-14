-- Load the Luno library
local luno = require("luno")

-- Initialize the Luno library
if not luno.create("Luno Test", 800, 600, 60) then
    error("Failed to initialize Luno!")
end

-- Test drawing functions
local rect = luno.rect(100, 100, 200, 150)
local rect_color = luno.color(255, 0, 0) -- Red
local circle_color = luno.color(0, 255, 0) -- Green
local line_color = luno.color(0, 0, 255) -- Blue

local image = luno.create_image(100, 100)
luno.fill_image(image, luno.color(128, 128, 128, 255)) -- Fill image with gray

-- Movement variables for rectangle
local speed = 200 -- Pixels per second
local direction = 1 -- 1 for right, -1 for left

-- Main loop
while luno.update() do
    -- Clear the screen
    luno.clear()

    -- Draw a pixel at the center
    luno.draw_pixel(400, 300, luno.YELLOW)

    -- Move the rectangle
    rect.x = rect.x + direction * speed * luno.get_dt()
    if rect.x + rect.w > 800 or rect.x < 0 then
        direction = -direction -- Reverse direction
    end

    -- Draw the rectangle
    luno.draw_rect(rect, rect_color, true)

    -- Draw a circle at the center
    luno.draw_circle(400, 300, 50, circle_color, false)

    -- Draw a line across the screen
    luno.draw_line(0, 0, 800, 600, line_color)

    -- Draw the image
    luno.draw_image(image, 50, 50)

    -- Display FPS
    local fps_text = string.format("FPS: %.1f", luno.get_fps())
    luno.draw_text(fps_text, 10, 10, luno.WHITE)

    -- Display mouse information
    local mouse_pos = luno.mouse_position()
    local mouse_delta = luno.mouse_delta()
    local mouse_info = string.format(
        "Mouse: (%d, %d), Delta: (%d, %d), Wheel: %d",
        mouse_pos.x, mouse_pos.y,
        mouse_delta.x, mouse_delta.y,
        luno.mouse_wheel_delta()
    )
    luno.draw_text(mouse_info, 10, 30, luno.WHITE)

    -- Display keyboard input state
    for key = 0, 255 do
        if luno.is_key_pressed(key) then
            print("Key pressed:", key)
        end
        if luno.is_key_held(key) then
            print("Key held:", key)
        end
        if luno.is_key_released(key) then
            print("Key released:", key)
        end
    end

    -- Check mouse buttons
    for button = 0, 2 do
        if luno.is_mouse_button_pressed(button) then
            print("Mouse button pressed:", button)
        end
        if luno.is_mouse_button_held(button) then
            print("Mouse button held:", button)
        end
        if luno.is_mouse_button_released(button) then
            print("Mouse button released:", button)
        end
    end
end

-- Cleanup
luno.destroy_image(image)
luno.close()
