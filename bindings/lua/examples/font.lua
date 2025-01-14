-- Load the Luno library
local luno = require("luno")

-- Initialize the Luno library
if not luno.create("Luno Test - Font Functions", 800, 600, 60) then
    error("Failed to initialize Luno!")
end

-- Load a font from a file
local font = luno.load_font("assets/font.png", 16, 16)
if not font then
    error("Failed to load font from file")
end

-- Test text width and height
local sample_text = "Hello, Luno!"
local text_width = luno.text_width(sample_text)
local text_height = luno.text_height()
print(string.format("Text width: %d, Text height: %d", text_width, text_height))

-- Draw some text on the screen
local x, y = 100, 100
local color = luno.color(255, 255, 255) -- White
luno.draw_text("Testing draw_text", x, y, color)

-- Reset the font to the default font
luno.reset_font()

-- Draw text with the default font
luno.draw_text("Default Font Example", x, y + 60, color)

-- Main loop
while luno.update() do
    -- Clear the screen
    luno.clear()

    -- Draw static text
    luno.draw_text("Static Text Example", 50, 50, luno.color(255, 0, 0)) -- Red

    -- Draw sample text
    luno.draw_text(sample_text, 50, 110, luno.color(0, 0, 255)) -- Blue
end

-- Cleanup
luno.destroy_font(font)
luno.close()
