# Computer Architectures: Tetris (Second Edition)

## 📌 Project Overview
This repository contains my **extended Tetris** implementation for the **LandTiger (LPC1768)** platform, developed for the course *Architetture dei Sistemi di Elaborazione (Computer Architectures)*.

Compared to the **First Edition**, this version adds:
- **Potentiometer (ADC) speed control**
- **Powerups**
- **Random malus line generation**
- Updated **soft drop** behavior (relative to the current speed)

🔗 **First Edition repository:** [link here](https://github.com/leilaalizadeh/Tetris_A)

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
- Powerups are visually distinguishable from normal blocks and from each other.

### Implemented Powerups

#### 1) Clear Half the Lines
- Clears the **bottom half** of the playing field.
- Points are awarded **as if those lines were cleared normally**.
- If no lines can be cleared, nothing happens and no points are awarded.

#### 2) Slow Down
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
- **Piece locks (placement):** `+10`
- **Clear N lines at once:** `+100 × N`
- **Clear 4 lines at once (Tetris):** `+600`

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

## 🧱 Build & Run (Keil µVision)
1. Open the `.uvprojx` project in **Keil µVision**
2. Select target **`SW_Debug`**
3. Build (**Rebuild All** recommended)
4. Start Debug session
5. Run, then press **KEY1** to start

---

## 👤 Author
Student project by **[Leila Alizadeh]**