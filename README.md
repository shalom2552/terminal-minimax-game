# terminal-minimax-game

A turn-based strategy game written in C, played directly in the terminal. The human player competes against an AI on a 10x10 numeric grid, where every move restricts the opponent's next available options.

## Screenshots

<div align="center">
  <table>
    <tr>
      <td valign="top" width="50%">
        <h3 align="center">Main Menu</h3>
        <img src="https://github.com/user-attachments/assets/d4cc0005-6d1c-4fb8-ae65-ebcc3ffd162f" width="100%" alt="Main Menu" />
      </td>
      <td valign="top" width="50%">
        <h3 align="center">Gameplay</h3>
        <img src="https://github.com/user-attachments/assets/3297b659-5006-4053-8392-9817851b1d9c" width="100%" alt="Gameplay Grid" />
      </td>
    </tr>
  </table>
</div>

## Overview

The game takes place on a grid populated with integers generated using a Gaussian (Normal) distribution. This ensures a challenging board layout with a mix of positive and negative values centered around a mean.

The primary mechanic is constraint propagation:
1. The Human player selects a number from the active Row.
2. The AI player must then select a number from the specific Column chosen by the human.
3. The AI's selection determines the Row for the human's next turn.

The game ends when the board is full or a player is blocked from making a move. The goal is to finish with a higher total score than the AI.

## Technical Highlights

* **Language Standard:** C99
* **System Architecture:** Modular design separating game logic, input handling (raw terminal mode), and display rendering.
* **Procedural Generation:** Board values are initialized using the Box-Muller transform to create a normal distribution of scores.
* **Input Handling:** Implements non-canonical terminal input to capture keystrokes immediately without requiring the Enter key.
* **Graphics:** Custom ASCII rendering using ANSI escape sequences for colors and cursor movement.

## Build and Run

This project uses GNU Make for compilation.

1.  Clone the repository:
    ```
    git clone https://github.com/shalom2552/terminal-minimax-game.git
    cd terminal-minimax-game
3.  Compile the source code:
    ```
    make
4.  Run the executable:
    ```
    ./game
## Controls

* **Arrow Keys:** Move the cursor left or right within the active row/column.
* **Space / Enter:** Confirm selection.
* **Q:** Quit the application.

## Rules

* **Starting:** The human player moves first.
* **Scoring:** When a cell is picked, its value is added to the player's total score.
* **Blocking:** If a player has no valid moves remaining in their active row or column, the game ends immediately, and the blocked player receives a 200-point penalty.
* **Winning:** The player with the highest score at the end of the game wins.

## Author

**shalom2552**

