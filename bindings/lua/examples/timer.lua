-- Load the Luno library
local luno = require("luno")

-- Initialize the Luno library
if not luno.create("Luno Test - Cursor & Timer", 800, 600, 60) then
    error("Failed to initialize Luno!")
end

-- Test cursor visibility
print("Testing Cursor Visibility...")
luno.set_cursor_visibility(false)
print("Cursor should be hidden:", luno.is_cursor_visible() == false)

luno.set_cursor_visibility(true)
print("Cursor should be visible:", luno.is_cursor_visible() == true)

-- Create a timer
local timer = luno.create_timer(1000) -- Timer interval: 1000ms (1 second)

while luno.update() do
    -- Clear the screen
    luno.clear()

    -- Update elapsed time
    local elapsed_time = timer:elapsed()

    -- Check if the timer has ticked
    if timer:ticked() then
        print("elapsed: " .. elapsed_time)
        timer:reset() -- Reset the timer
    end

    -- Display elapsed time
    luno.draw_text("elapsed: " .. elapsed_time, 10, 10, luno.color(255, 255, 255)) -- White text

    -- Break the loop after 5 seconds
    if elapsed_time > 5000 then
        print("Test complete. Exiting...")
        break
    end
end

-- Cleanup
luno.close()
