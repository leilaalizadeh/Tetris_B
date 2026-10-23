# Computer Architectures: Tetris (Second Edition)

## 📌 Project Overview
This repository contains my **extended Tetris** implementation for the **LandTiger (LPC1768)** platform, developed for the course *Architetture dei Sistemi di Elaborazione (Computer Architectures)*.

Compared to the **First Edition**, this version adds:
- **Potentiometer (ADC) speed control**
- **Powerups**
- **Random malus line generation**
- Updated **soft drop** behavior (relative to the current speed)

🔗 **First Edition repository:** [Tetris (First Edition)](https://github.com/leilaalizadeh/Tetris_A)

- **Target platform:** LandTiger Board / LPC1768 (Emulator)
- **Keil target:** `SW_Debug`

---

## 🎮 Gameplay Summary
This is a classic Tetris-style game:

- A random tetromino spawns near the top of the grid.
- You can move and rotate it while it falls.
- When it can’t move down anymore, it **locks** into the grid.
- Completed lines are cleared and everything above shifts down.
- The game ends when new pieces can’t be spawned safely.

---

## 🧩 Playing Field & UI
- **Grid size:** **20 rows × 10 columns**
- **Layout:**
  - **Left:** playing field
  - **Right:** **Score**, **High Score**, **Cleared Lines**
- **Tetrominoes implemented:** **I, O, T, J, L, S, Z**

---

## 🕹️ Controls

| Input | Action |
|---|---|
| **KEY1** | Start (after reset) / Pause / Resume |
| **KEY2** | **Hard Drop** (instant fall + lock) |
| **Joystick Left / Right** | Move horizontally |
| **Joystick Up** | Rotate **90° clockwise** |
| **Joystick Down (hold)** | **Soft Drop** (see speed rules below) |

---

## ⏱️ Speed Control (Potentiometer / ADC)
In this edition, the falling speed is controlled by the **potentiometer (ADC)**:

- The ADC reading (0–4095) is mapped linearly to the falling speed: `speed = 1 + (ADC × 4) / 4095`, rounded down
- Minimum speed: **1 block/second** at low voltage
- Maximum speed: **5 blocks/second** at maximum voltage

### Soft Drop (Updated)
Soft drop **doubles the current falling speed**, whatever it is at that moment.

Example:
- If the potentiometer sets **3 blocks/sec**, soft drop becomes **6 blocks/sec** while held.

---

## ✨ Powerups
Special **powerup blocks** can appear during the game.

### Spawn Rule
- Every **5 cleared lines**, a **random powerup** replaces an **already occupied cell** (never an empty cell).
- A powerup activates **only when the row containing it is cleared**.
- Powerups are color-coded: normal blocks are **white**, *Clear Half* is **green**, and *Slow Down* is **blue**.

### Implemented Powerups

#### 1) Clear Half the Lines 🟩
- Clears the bottom half of the playing field (the bottom **10 rows**).
- Only rows that contained blocks earn points. They are scored in groups of up to 4, **as if cleared normally** (e.g. 6 filled rows = one Tetris + one double).
- If the bottom half is empty, nothing happens and no points are awarded.

#### 2) Slow Down 🟦
- If the current speed is greater than **1 block/sec**, it forces the speed to **1 block/sec** for **15 seconds**.
- After 15 seconds, speed returns to the potentiometer-controlled value.

---

## 😈 Random Malus Line
To increase difficulty, the game introduces a malus mechanic:

- Every **10 cleared lines**, a **new bottom line** is generated.
- The generated line contains **7 random blocks out of 10** (holes allowed).
- All existing lines shift **up by 1**.
- If this shift causes overflow above the top boundary → **game over**.

---

## 📈 Scoring
| Event | Points |
|---|---|
| Piece locks (placement) | `+10` |
| Clear 1–3 lines at once | `+100 × N` |
| Clear 4 lines at once (Tetris) | `+600` (instead of `+400`) |

> Placement points are always added when the piece locks, even if lines are cleared.

---

## 🛑 Game Over + High Score
Game ends if:
- blocks exceed the top boundary, or
- a newly spawned piece overlaps existing blocks, or
- the malus shift pushes blocks above the top boundary.

After game over:
- **High Score** is updated if the final score is higher
- the game returns to the initial paused state
- press **KEY1** to start a new run

---

## 📁 Project Structure

| Path | Purpose |
|---|---|
| `Main.c` | Initialization and main loop (reads the potentiometer, sets the speed) |
| `Game.c` / `Game.h` | Game logic: collisions, line clearing, scoring, powerups, malus line |
| `View.c` / `View.h` | Drawing the grid, blocks and score panel on the LCD |
| `Tetrominoes.s` | Tetromino shape and rotation data (assembly) |
| `Random_LFSR.s` | LFSR random number generator (assembly) |
| `RIT/` | Repetitive Interrupt Timer (10 ms tick): gravity, soft drop, joystick polling |
| `ADC/` | Potentiometer reading |
| `Button/`, `joystick/` | KEY1/KEY2 and joystick input |
| `GLCD/` | LCD driver |
| `Template.uvprojx` | Keil µVision project file |

---

## 🧱 Build & Run (Keil µVision)
**Requirements:** Keil µVision (version: -) with the LPC17xx device pack

1. Open the `.uvprojx` project in **Keil µVision**
2. Select target **`SW_Debug`**
3. Build (**Rebuild All** recommended)
4. Start Debug session
5. Run, then press **KEY1** to start

---

## 👤 Author
Student project by **Leila Alizadeh**, Politecnico di Torino, Computer Architectures, A.Y. 2025–2026
