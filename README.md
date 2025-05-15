# Recreated SuperMario 2D

A simple side-scrolling Mario-style platformer written in C using the `ncurses` library. The game runs in the terminal and features gravity, jumping, basic enemy movement, and level completion.

---

## 🕹️ How to Play

- **Move Left:** `←` arrow key or `A`
- **Move Right:** `→` arrow key or `D`
- **Jump:** `↑` arrow key or `Space`
- **Quit Game:** `Q`
- **Restart:** `R`

📌 **Important:**  
**Mouse input is not supported.** All inputs must be done using the keyboard.

---

## 🎯 Objective

Guide Mario to the end of the level.  
The goal is represented by a `*` character at the far-right side of the level. Reach it to complete the level!

Avoid enemies (`E`) — colliding with one will trigger a game over screen.

---

## Core Source Files

- **main.c:** 
	- Loads the level
	- Initializes Mario and enemies
	- Handles keyboard input
	- Updates the game state (movement, gravity, collisions)
	- Renders the viewport, characters, and status

- **map.c / map.h:** 
	- Handles the level/map loading and drawing.
	- Reads the map from a .map file into memory
	- Converts the ASCII map into a playable area
	- Provides helpers for checking tile contents and drawing the map to the screen

- **mario.c / mario.h:**
	- Draws Mario on screen
	- Handles gravity and jumping physics
	- Tracks position and vertical velocity

- **enemy.c / enemy.h:**
	- Manages simple enemy behavior:
	- Enemies walk left and right
	- Enemies turn around when hitting edges or gaps
	- Enemies collide with Mario to trigger game over

- **util.c / util.h:**
	- Provides utility functions like:
	- Millisecond-level sleeping for controlling frame rate

- **assets.h:** Defines symbolic characters used in the map (e.g., # for brick, = for ground, @ for Mario, * for goal).
---

## 🔧 How to Build

Make sure you have the development version of `ncurses` and `SDL2` installed.

### Compile the program:
```bash
make
```

### Run the Program:
```bash
./mario level1.map