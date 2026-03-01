# 🎲 Introduction
This project is a C++ command-line lottery simulation program that models real-world lotto systems using probability, combinatorics, and randomized dice rolls.

It simulates lottery drawings, calculates true odds mathematically, and repeatedly “plays” until a winning combination is achieved — tracking total rolls, cost, and statistical averages.



## 📚 Index

- [About](#-about)
- [Usage](#-usage)
- [Development](#-development)
- [Acknowledgements](#-acknowledgements)



## 🎯 About

This project is a console-based C++ lottery simulator designed to demonstrate:

- Combinatorics-based odds calculation (n choose k)
- Random number generation using `std::mt19937_64`
- Simulation of lottery roll repetition until win
- Duplicate prevention logic
- Sorting algorithms (insertion sort)
- Performance throttling based on CPU workload selection
- Statistical averaging across multiple lottery simulations
- File parsing using `fstream` and `stringstream`

The program allows users to:

- Choose predefined lottery systems (via `lottoInfo.txt`)
- Create a fully custom lottery configuration
- Simulate one or many lottery runs
- Calculate average rolls across multiple simulations
- Track total cost vs jackpot winnings



## 🏗 Usage

Write about how to use this project.

### 💻 Requirements

- C++17 compatible compiler
- g++ (Mac/Linux) or MinGW-w64 (Windows)
- VS Code (optional but recommended)



### 🖥 macOS Compilation (g++)

From the project directory:

```bash
g++ -std=c++17 main.cpp dice.cpp -o lotto
```

Run:

```bash
./lotto
```

If `dice.cpp` is not separate and is header-only, compile:

```bash
g++ -std=c++17 main.cpp -o lotto
```



### 🪟 Windows Compilation (VS Code + MinGW)

1. Install MinGW-w64
2. Ensure `g++` is in your system PATH
3. Open VS Code in the project folder
4. Open terminal inside VS Code
5. Compile:

```bash
g++ -std=c++17 main.cpp dice.cpp -o lotto.exe
```

Run:

```bash
lotto.exe
```



### ▶ Running the Program

When launched:

1. Choose CPU workload mode
2. Select an existing lottery or create custom
3. Program simulates rolls until jackpot win
4. Displays:
   - Number of rolls required
   - Closest roll sets
   - Total ticket cost
   - Time elapsed
   - Average across repeated runs (if selected)

You may enter:
- `y`, `yes`, etc. to replay
- A number to simulate multiple runs for averaging



## 🛠 Development

If you want to modify or extend this program, follow the structure below.

### 📋 Pre-Requisites

- C++17 knowledge
- Understanding of:
  - Random number generation
  - Combinations (nCk)
  - Sorting algorithms
  - File I/O
  - Vectors and dynamic arrays



### 🧠 Core Program Features

- `Lottery` struct for configuration storage
- `calculateOdds()` for mathematical odds
- `playLottery()` for simulation engine
- `doubles()` legacy simulation mode
- Insertion sort for roll normalization
- Thread-local Mersenne Twister RNG
- CPU workload throttling using `sleep_for`
- Rolling statistics & averaging system



### 📂 Program Structure

Only the primary structure is shown below.

```
.
├── main.cpp
├── dice.h
├── dice.cpp
└── lottoInfo.txt
```

| No | File | Details |
|----|------|---------|
| 1  | main.cpp | Core lottery logic and simulation engine |
| 2  | dice.h | Dice class declaration |
| 3  | dice.cpp | Dice class implementation |
| 4  | lottoInfo.txt | Predefined lottery configurations |



### ▶️ Build Notes

- Ensure `lottoInfo.txt` is in the same directory as the executable
- Must compile with `-std=c++17` or newer
- Program uses `<thread>` and `<chrono>` for timing



## 🙏 Acknowledgements

Original Author from the 1980's (doubles function): **Alen Bell**  
Updated & Documented by: **Kenton Bell**

Built using:
- C++17
- Standard Template Library (STL)
- Mersenne Twister RNG (`std::mt19937_64`)
- VS Code
