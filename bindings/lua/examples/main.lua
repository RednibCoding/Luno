-- Load the Luno library
local luno = require("luno")

-- Initialize the Luno library
if not luno.create("Luno Collision Test", 800, 600, 60) then
    error("Failed to initialize Luno!")
end

-- Define test shapes
local rect1 = luno.rect(100, 100, 200, 150)
local rect2 = luno.rect(150, 120, 50, 50)
local point = luno.point(160, 130)
local circle_center = luno.point(400, 300)
local circle_radius = 50

-- Test collision detection functions
print("Collision Detection Tests")

-- Point and rectangle overlap
print("Point-Rectangle Overlap:", luno.point_rec_overlaps(point.x, point.y, rect1))

-- Rectangle and rectangle overlap
print("Rectangle-Rectangle Overlap:", luno.recs_overlap(rect1, rect2))

-- Point and circle overlap
print("Point-Circle Overlap:", luno.point_circle_overlaps(point.x, point.y, circle_center.x, circle_center.y, circle_radius))

-- Rectangle and circle overlap
print("Rectangle-Circle Overlap:", luno.rec_circle_overlaps(rect1, circle_center.x, circle_center.y, circle_radius))

-- Circle and circle overlap
local circle2_center = luno.point(420, 310)
local circle2_radius = 30
print("Circle-Circle Overlap:", luno.circles_overlap(circle_center.x, circle_center.y, circle_radius, circle2_center.x, circle2_center.y, circle2_radius))

-- Main loop to visualize the shapes
while luno.update() do
    -- Clear the screen
    luno.clear()

    -- Draw the first rectangle
    luno.draw_rect(rect1, luno.color(255, 0, 0), false) -- Red outline

    -- Draw the second rectangle
    luno.draw_rect(rect2, luno.color(0, 255, 0), false) -- Green outline

    -- Draw the point
    luno.draw_text("P", point.x - 5, point.y - 5, luno.color(0, 0, 255)) -- Blue

    -- Draw the first circle
    luno.draw_circle(circle_center.x, circle_center.y, circle_radius, luno.color(255, 255, 0), false) -- Yellow outline

    -- Draw the second circle
    luno.draw_circle(circle2_center.x, circle2_center.y, circle2_radius, luno.color(255, 0, 255), false) -- Magenta outline
end

-- Cleanup
luno.close()
