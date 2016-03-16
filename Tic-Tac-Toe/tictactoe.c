/* Eeshan Londhe
 *
 * Tic-Tac-Toe game in C. Allows user to play against a computer or another human turn by turn.
 */

#include <stdio.h> // for printf() and getchar()
#include <stdlib.h> // for rand()
#include <time.h> // for srand()

void initializeBoard();
void printBoard();
void startGame();
void playGame(char input);
void getHumanMove(char player);
void getComputerMove();
char checkWinner();
int winPossible();
void clearInputBuffer();

char board[3][3]; // Tic-Tac-Toe game board 3 x 3

// main method that runs Tic-Tac-Toe
int main() {
  initializeBoard();
  startGame();
  return 0;
}

// Loads the start up message for when the game is run. Asks the user to input
// a 1 or 0 for whether they would like to play against a computer or a human.
void startGame() {
  printf("Welecome to the Tic-Tac-Toe Game!\n");
  char input = ' ';
  while (input != '1' && input != '0') {
    printf("Would you like to play against a Computer or a Human? (Input 1 for Computer or 0 for Human): ");
    input = getchar();
    clearInputBuffer();
  }
  playGame(input);
}

// Takes in an input to determine whether the game is played against a computer (1) or another human (0).
// Prompts the user to input the coordinate for where they would like to play there move.
// Displays the game board after every move. Once someone wins, a message is displayed indicating
// who won. After someone wins, the user is prompted to see if they would like to play again.
void playGame(char input) {
  int repeat = 1;
  char win = ' ';
  int moves = 0;
  printBoard();
  // main game loop
  while (repeat) {
    // player 1's move
    if (win == ' ') {
      getHumanMove('X');
      if (input == '0') {
        printBoard();
      }
      moves++;
      win = checkWinner();
    }

    // player 2's/computer's move
    if (win == ' ' && moves != 9) {
      if (input == '1') {
        getComputerMove();
      } else {
        getHumanMove('O');
      }
      moves++;
      printBoard();
      win = checkWinner();
    }

    // if someone wins or game ends in a draw
    if (win != ' ' || (moves == 9 && win == ' ')) {
      if (win == 'X') {
        if (input == '1') {
          printf("You win!\n");
        } else {
          printf("Player 1 wins!\n");
        }
      } else if (win == 'O') {
        if (input == '1') {
          printf("The computer wins!\n");
        } else {
          printf("Player 2 wins!\n");
        }
      } else {
        printf("The game ended in a draw!\n");
      }
      if (input == '1' && win != 'O') {
        printBoard();
      }
      char response = ' ';
      while (response != '1' && response != '0') {
        printf("Would you like to play again? Input 1 for yes, 0 for no: ");
        response = getchar();
        clearInputBuffer();
      }
      if (response == '0') {
        repeat = 0;
      }
      // re-initializes all variable for a new game.
      win = ' ';
      moves = 0;
      initializeBoard();
      if (repeat) {
        printBoard();
      }
    }
  }
}

// Takes in a char as an input to indicate which player is making their move.
// 'X' for player 1. 'O' for player 2.
// Asks the user the coordinate that they would like to place their move. Afterwards,
// updates the Tic-Tac-Toe board accordingly. If the user inputs a move that already has been played,
// then there is a message shown to notify the user that the spot has already been filled.
// The user is prompted again to input a coordinate.
void getHumanMove(char player) {
  char x = ' ';
  char y = ' ';
  int gamePlayer = 1;
  if (player != 'X') {
    gamePlayer = 2;
  }
  printf("%s%d%s%c%s", "You are player ", gamePlayer, ". Please input the row and column you would like to place your ", player, " at.\n");
  printf("Input the row. Input a number between 1 - 3: ");
  x = getchar();
  clearInputBuffer();
  printf("Input the the column. (Input a number between 1 - 3: ");
  y = getchar();
  clearInputBuffer();
  if (x < '1' || y < '1' || x > '3' || y > '3') {
    printf("Invalid move. Number must be between 1 and 3.\n");
    getHumanMove(player);
  } else if(board[x - '0' - 1][y - '0' - 1] != ' ') {
    printf("Invalid move. That spot has already been taken.\n");
    getHumanMove(player);
  } else {
    board[x - '0' - 1][y - '0' - 1] = player;
  }
}

// When playing against a computer, the computer tries to make a move to win, or stop
// the human from winning. If no winning moves or win stopping moves are possible, the
// computer randomly chooses a spot to make its move.
void getComputerMove() {
  int location = winPossible();
  // If the computer can win, then the winning move is placed.
  // If the computer can stop the human from winning, that move is placed.
  if (location != -1) {
    board[location / 3][location % 3] = 'O';
  } else { // if no winning moves or win stopping moves are available, randomly a chooses move
    srand(time(NULL));
    int x = rand() % 3;
    int y = rand() % 3;
    while (board[x][y] != ' ') {
      x = rand() % 3;
      y = rand() % 3;
    }
    board[x][y] = 'O';
  }
}

// Checks to see if a win or win stopping move is possible at all locations on the board.
// If a win or win stopping move is possible, then returns a number corresponding to the spot on the board.
// If no possible win locations or win stopping locations are found, returns -1.
int winPossible() {
  int i;
  // loops through all locations on the board and checks if computer can win
  for (i = 0; i < 9; i++) {
    int x = i / 3;
    int y = i % 3;
    if (board[x][y] == ' ') {
      board[x][y] = 'O';
      if (checkWinner() != ' ') {
        board[x][y] = ' ';
        return i;
      }
      board[x][y] = ' ';
    }
  }

  // loops through all locations on the board and checks if computer can stop the human from winning
  for (i = 0; i < 9; i++) {
    int x = i / 3;
    int y = i % 3;
    if (board[x][y] == ' ') {
      board[x][y] = 'X';
      if (checkWinner() != ' ') {
        board[x][y] = ' ';
        return i;
      }
      board[x][y] = ' ';
    }
  }
  return -1;
}

// Checks if someone has won the game or not.
// Returns 'X' if the Player 1 wins, 'O' if either Player 2 or the computer wins, and
// returns ' ' if there is no winner.
char checkWinner() {
  int i;
  // checks all rows to see if there are 3 in a row.
  for (i = 0; i < 3; i++) {
    if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
      return board[i][0];
    }
  }

  // checks all columsn to see if there are 3 in a column
  for (i = 0; i < 3; i++) {
    if(board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
      return board[0][i];
    }
  }

  // checks a diagnal to see if there are 3 diagonally
  if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
    return board[0][0];
  }

  // checks other diagonally to see if there are 3 diagonally
  if (board[2][0] != ' ' && board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
    return board[2][0];
  }
  return ' ';
}

// initializes the game board with empty characters.
void initializeBoard() {
  int i;
  int j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      board[i][j] = ' ';
    }
  }
}

// prints the the contents of the game board to the console.
void printBoard() {
  int i;
  for (i = 0; i < 3; i++) {
    printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
    if (i != 2) {
      printf("\n---|---|---\n");
    }
  }
  printf("\n");
}

// helper method to clear the input buffer
void clearInputBuffer() {
  while (getchar() != '\n');
}
