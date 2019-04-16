# Pocket DDR

This project is meant to be a game, to carry on the go. It is reminiscent of the classic videogame, Dance Dance Revolution, in that a 2x2 grid of lights corresponds to a 2x2 grid of buttons, and you have to hit the buttons corresponding to the turned-on LEDs before the time runs out.

The gameplay is straightforward: when two LEDs are lit on the screen, you must hit the corresponding two butons before they disappear. There are 8 levels, each of which is slightly faster than the previous. These 8 levels are encoded in binary in the top left corner. A red LED blinks in the top right corner if you lose, at which point you are reset to level 0. There will only ever be two LEDs lit at a time, and the only indicator that the next level has begun is the changing level in the top left.

On the software side, the game runs a simple program that randomly selects two of the four gameplay LEDs to be lit, and then sets a timeout for the corresponding buttons to be hit. Once the timeout expires, the state of the game is compared with the most recent state of button presses. If they are the same, the player may progress to the next level. Otherwise, the program resets the player's level to 0, and resets the timeout accordingly.

For the project's "enclosure," I chose to only create a top pane, because I was fascinated by how the user-facing side of the game was so elegant and clean but the developer-facing side was a scramble of wires and electrical tape and resistors and solder burns. It is reflective of my typical experience with software development.

The codebase for this project can be found [on GitHub](https://github.com/khayyamsaleem/arduino-pocket-ddr).
