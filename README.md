# Baccarat Game (C Project)

## Table of Contents
- [Key Features](#key-features)
- [Technical Highlights](#technical-highlights)
- [How to Build and Run](#how-to-build-and-run)
- [Project Purpose](#project-purpose)
- [Project presentation](#project_presentation)

This is a console-based Baccarat game implemented in C. The project focuses on simulating the basic rules of Baccarat, including card dealing, score calculation, and third-card rules. It also includes a simple text-based interface using console functions such as gotoxy, getch, and SetColor.

## Key Features

- Implementation of Player vs Banker Baccarat rules

- Deck generation using a base-13 encoding method (0–51 mapping)

- Third card rule logic and split-stage game flow

- Console interface with keyboard navigation and visual effects

## Technical Highlights

- Dynamic memory allocation with malloc

- Use of structures and function-based card decoding

- 2D arrays and pointer logic for deck and hand management

- Basic GUI-like interaction using console cursor control and color output

## How to Build and Run
```bash
gcc baccarat.c -o baccarat
./baccarat
```
## Project Purpose

- Practice with data structures and memory management in C

- Understand game logic implementation and state-based flow

- Explore basic user interaction without external graphics libraries

## project_presentation
[baccarat_presentation.pdf](https://github.com/user-attachments/files/22860939/baccarat_presentation.pdf)
