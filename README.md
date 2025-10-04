# Text Adventure

A compact, terminal-based **horror text adventure** written in C. You’ll step into an eerily silent house, and try to make it back out in one piece—by exploring rooms, inspecting objects, and using your wits (and items). Built as a single-file C program with a simple CMake setup.

---

## ⚠️ Before You Begin
This README contains **general gameplay explanations** — sections like [💬 Commands](#-commands), [⚙️ Core Loop & Game Logic](#️-core-loop--game-logic), and [🔦 Items, Light, and Hazards](#-items-light-and-hazards) give insight into how the game works.  
While they **don’t spoil story events**, they may **offer small hints or strategic advantages** (like what certain mechanics do).

If you want the **purest, most immersive experience**, skip directly to:
- [🧰 Build & Run](#-build--run) – to set up the game  
- Then **play blind**. Discover the rest through exploration. 🔥

---

## 🌒 Theme (No Spoilers)
This is a **moody, flashlight and floorboards** kind of story: creaking doors, strange drafts, and the ambient dread of a place that *doesn’t want you there*.  
Your goal is simple: **go in, survive, and get out**. The “how” is up to you.

---

## ⚙️ Core Loop & Game Logic
- **Explore → Inspect → Use → Decide:** Navigate between rooms, look closely at what you find, use (or drop) items, and manage risk.  
- **Stateful Rooms & Events:** Certain rooms can trigger consequences depending on your current light and items.  
- **Inventory & Health:** Each character starts with different gear and a number of inventory slots. Taking damage leaves you *injured*, and a second hit ends the run.  
- **Win State:** Find a way to unlock the way out and **leave the house alive**.

---

## 💬 Commands
All commands are **case-insensitive**. Use natural words; no punctuation needed.

- `go <direction>` – Move between rooms using `north`, `east`, `south`, or `west`. Some paths are blocked until you solve something nearby.  
- `inspect <thing>` – Look at an object or the room itself. Inspecting reveals clues or hazards, and sometimes lets you **pick up** items.  
- `use <item>` – Try to use an item you’re carrying. Some are **contextual** or **consumable**.  
- `drop <item>` – Leave an item in the current room to free space. Be careful—dropping your light source can leave you in darkness.  
- `help please` – Shows this list again.  
- `quit game` – Confirms exit from the current run.

> 💡 After each action, the game prints a mini “GUI” showing **Location**, **Light**, **Status**, **Inventory**, and **Room Objects**.

---

## 🔦 Items, Light, and Hazards
- **Items**: Common household objects, a few tools, and some consumables. Some are crucial for progression; others offer one-time help.  
- **Light**: Darkness is dangerous. You can maintain light using specific items or combinations. Without it, some rooms become **much riskier**.  
- **Hazards**: Certain traps or dangers may trigger the first time you enter a room—especially in darkness.

---

## 🧭 Rooms & Navigation (Overview)
The house includes a **living room hub** connecting other spaces (kitchen, bedroom, bathroom, basement). Some exits are locked or blocked until you find clues or use the right items.  
Pay close attention to descriptive text—it often **hints at what matters**.

---

## 🧠 Playing Tips
- 🕯️ **Read the room text** — it often hints at what to inspect or where to use an item.  
- ⚡ **Mind the light** — some areas are lethal in darkness.  
- 🎒 **Travel light** — inventory space is tight; drop what you don’t need.  
- 👁️ **Inspect first, then act** — many dangers are telegraphed if you pay attention.

---

## 🧰 Build & Run

### Requirements
- **CMake ≥ 3.10**
- **C compiler** (e.g., `gcc` or `clang`)

### Build with CMake (recommended)
```bash
cmake -B build
cmake --build build
./build/game
```

### Build with gcc (Alternative)
```bash
gcc -std=c11 -O2 -o game TextAdventure.c
./game
```

> 🖥️ Works cleanly on Linux/macOS/WSL. On Windows, use MinGW or a Unix-like environment.

---

## 📁 Project Structure
```
.
├── TextAdventure.c    # Game source (logic, I/O, story text, commands)
└── CMakeLists.txt     # Minimal build script for CMake
```

---

## 🙏 Acknowledgments
Thanks for playing and reading the room text closely. Good luck getting out.
