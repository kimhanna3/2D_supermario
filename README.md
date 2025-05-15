# Terminal Mario Platformer

A simple side-scrolling Mario-style platformer written in C using the `ncurses` library. The game runs in the terminal and features gravity, jumping, basic enemy movement, and level completion.

---

## 🕹️ How to Play

- **Move Left:** `←` arrow key or `A`
- **Move Right:** `→` arrow key or `D`
- **Jump:** `↑` arrow key or `Space`
- **Quit Game:** `Q`
- **Restart:** `R`

📌 **Important:**  
**Mouse input is not supported.** All interactions must be done using the keyboard.

---

## 🎯 Objective

Guide Mario to the end of the level.  
The goal is represented by a `*` character at the far-right side of the level. Reach it to complete the level!

Avoid enemies (`E`) — colliding with one will trigger a game over screen.

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