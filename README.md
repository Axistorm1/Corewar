# 🔥 Corewar: The Battle of Code

**Corewar** is a programming game where players write programs, called **warriors**, that battle for control of a simulated computer memory called the **core**. The game is a test of logic, strategy, and low-level programming skill.

---

## 🧠 How It Works

- **Language**: Warriors are written in an assembly-like language called **Redcode** (this version uses a pseudo-redcode language).
- **Simulator**: The game runs in a virtual machine that follows the rules of the **MARS** (Memory Array Redcode Simulator).
- **Goal**: Each warrior tries to:
  - Survive longest in the memory.
  - Crash or disable the opponent's code.
  - Take over the memory by replicating or overwriting other programs.

---

## 💻 Game Mechanics

- The core memory is a circular array where each cell can contain a Redcode instruction.
- Multiple warriors are loaded into different parts of the core.
- Warriors execute instructions based on their 'cooldown'.
- If a warrior runs out of processes, it dies.
- The last warrior running wins.

---

![Corewar](assets/screenshot_corewar.png)

---

## **Table of Contents**
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Acknowledgements](#acknowledgements)

---

## **Features**
✨ Key features: <br>
✔️ Efficient virtual machine <br>
✔️ Beautiful graphic version <br>

---

## **Installation**
**Prerequisites:** <br>
All available in the install script <br>
Default:
- Git
- Make + Cmake
- GCC + Clang

Graphic version:
- Raylib
- Ncurses
- SDL

**Steps:**
1. Clone the repository:
   ```sh
   git clone https://github.com/Axistorm1/Corewar.git --depth=1
   ```
2. Navigate to the project directory:
   ```sh
   cd B-CPE-200-TLS-2-1-corewar-valentin.bort-esgueva
   ```
3. Install dependencies:
   ```sh
   ./installer.sh
   ```
4. Compile project:
   ```sh
   make
   ```
4. For the graphic version:
   ```sh
   make bonus
   ```
---

## **Usage**
**Basic Commands:**
  ```sh
  ./corewar -h
  ./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...
  ```
**Examples**
```sh
./corewar -dump 1000 -n 5 abel.cor -a 2000 bill.cor
```

---

## **Acknowledgements**
- Thanks to Epitech for this wonderful project

---

**⭐ Star this repo if you liked it! ⭐**

---
