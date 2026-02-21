# Computer Architectures — Tetris (Extrapoint 2) | LandTiger (LPC1768)

## 📌 Project Overview
This repository contains my **extended Tetris** project for the **LandTiger (LPC1768)** platform, developed for the course *Architetture dei Sistemi di Elaborazione (Computer Architectures)*.

This version corresponds to **Extrapoint 2**, meaning it includes **all features from Extrapoint 1** plus additional mechanics (speed control via potentiometer, powerups, malus lines, and audio). :contentReference[oaicite:1]{index=1}

- **Target platform:** LandTiger Board / LPC1768
- **Keil target:** `SW_Debug` (emulator)
- **Note:** The **Music/Speaker** part cannot be fully tested on the emulator (requires real board). :contentReference[oaicite:2]{index=2}

---

## 🎮 What the Game Does
A classic Tetris-style game:

- A random tetromino spawns near the top-center.
- You can move/rotate it while it falls.
- When it can’t move down anymore, it **locks** into the grid.
- Full lines are removed, blocks above shift down, and the score increases.
- The game ends when pieces **cannot enter** the field (overflow / spawn collision).

---

## 🧩 Playing Field & UI
- **Grid size:** **20 rows × 10 columns**
- **Screen layout:**
  - **Left:** playing field
  - **Right:** **Score**, **High Score**, **Cleared Lines**
- **Tetrominoes:** I, O, T, J, L, S, Z

---

## 🕹️ Controls

| Input | Action |
|---|---|
| **KEY1** | Start (after reset) / Pause / Resume |
| **KEY2** | **Hard Drop** (instant drop to lowest valid position + lock) |
| **Joystick Left / Right** | Move piece horizontally |
| **Joystick Up** | Rotate **90° clockwise** |
| **Joystick Down (hold)** | **Soft Drop** (see speed rules below) |

---

## ⏱️ Speed Control (New in Extrapoint 2)
Game speed is controlled by the **potentiometer (ADC)**:

- Minimum speed: **1 block/second** when ADC ≈ **0V**
- Maximum speed: **5 blocks/second** when ADC is at **maximum voltage** :contentReference[oaicite:3]{index=3}

### Soft Drop Rule (Updated)
In Extrapoint 1, soft drop always set the speed to **2 blocks/sec**.
In Extrapoint 2, soft drop **doubles the current speed** (whatever the potentiometer setting is). :contentReference[oaicite:4]{index=4}

Example:
- If potentiometer speed = 3 blocks/sec → soft drop becomes 6 blocks/sec (while held).

---

## ✨ Powerups (New in Extrapoint 2)
During gameplay, special **powerup blocks** can appear on the playing field.

### Spawn Rule
- Every **5 cleared lines**, a **random powerup** replaces an **existing occupied block** (it must NOT appear in an empty cell).
- Powerups are drawn with a distinct appearance (different from normal blocks and from other powerups). :contentReference[oaicite:5]{index=5}
- A powerup activates **only when the line containing it is cleared**. :contentReference[oaicite:6]{index=6}

### Implemented Powerups

#### 1) Clear Half the Lines
- Instantly clears the **bottom half** of the current field.
- The player receives points **as if those lines were cleared normally**. :contentReference[oaicite:7]{index=7}

Scoring details for this powerup:
- If it clears up to **4 lines**, score as usual.
- If it clears **more than 4**, score in **groups of 4 lines** (Tetris groups), and handle the remainder properly (last group may be < 4). :contentReference[oaicite:8]{index=8}
- If there are **no remaining lines** to clear, nothing happens and **no points** are awarded. :contentReference[oaicite:9]{index=9}

#### 2) Slow Down
- If current speed is > **1 block/sec**, it forces speed to **1 block/sec** for **15 seconds**.
- After 15 seconds, speed returns to the potentiometer-controlled value. :contentReference[oaicite:10]{index=10}

---

## 😈 Random Malus (New in Extrapoint 2)
To increase difficulty:

- Every **10 cleared lines**, a new **malus line** appears at the **bottom**.
- That line contains **7 random blocks out of 10** (not necessarily consecutive; holes are allowed).
- All existing lines are shifted **up by 1**.
- If this causes blocks to overflow above the top boundary → **game over**. :contentReference[oaicite:11]{index=11}

---

## 📈 Scoring System
- **Piece locks (placement):** `+10`
- **Clear N lines at once:** `+100 × N`
- **Clear 4 lines at once (Tetris):** `+600`

> Placement points (`+10`) are added when the piece locks, even if lines are cleared.

---

## 🛑 Game Over + High Score
Game ends if:
- locked blocks exceed the top boundary, or
- a new tetromino overlaps existing blocks at spawn, or
- the malus line shift causes overflow. :contentReference[oaicite:12]{index=12}

After game over:
- High score updates if the score is higher
- Game returns to the initial **paused** state
- New game starts again with **KEY1**

---

## 🔊 Music / Sound (New in Extrapoint 2)
The speaker is configured to play:
- sound effects
- background music

⚠️ This part **cannot be implemented/tested on the emulator** and requires a physical LandTiger board. :contentReference[oaicite:13]{index=13}

---

## 🧱 Build & Run (Keil µVision)
1. Open the `.uvprojx` project in **Keil µVision**
2. Select target **`SW_Debug`**
3. Build (**Rebuild All** recommended)
4. Start Debug session
5. Run, then press **KEY1** to start

---

## 📦 Submission Note (Course Requirement)
For the course delivery, the expected package name is **`extrapoint2.zip`** containing the full Keil project folder with all required source files. :contentReference[oaicite:14]{index=14}

---

## 👤 Author
Student project by **[Leila Alizadeh]**