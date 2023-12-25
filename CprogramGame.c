#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// Global variable
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';
typedef struct {
    char username[100];
    int score;
} PlayerScore;

// Function declaration
PlayerScore currentUser;
void initializeBoard();
void printBoard();
int checkWin();
int checkDraw();
void playerMove();
void computerMove();
int ticTacToe();
void guessTheNumber();
int rockPaperScissors();
void readScores(PlayerScore scores[], int *size);
void writeScores(PlayerScore scores[], int size);
void searchUser(PlayerScore scores[], int size);
void sortScores(PlayerScore scores[], int size);
void displayScores(PlayerScore scores[], int size);
void loginUser();
void showMainMenu();
void updateUserScore(PlayerScore scores[], int *size, int addedScore);

void initializeBoard() {
    // Set boardnya jadi kosong
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if (j < 2) printf(" | ");
        }
        if (i < 2) printf("\n---------\n");
    }
    printf("\n\n");
}

int checkWin() {
    // Cek kondisi kalo ada yg diagonal, horizontal, sama vertikal
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return 1;
    return 0;
}

int checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void playerMove() {
    int x, y;
    do {
        printf("Enter row and column (1-3 each, separated by space): ");
        scanf("%d %d", &x, &y);
        x--; y--;
    } while (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ');

    board[x][y] = PLAYER;
}

void computerMove() {
    srand(time(NULL));
    int x, y;
    if (checkDraw()) return;
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');
    board[x][y] = COMPUTER;
    printf("Computer placed an O in position %d, %d\n", x + 1, y + 1);
}

int ticTacToe() {
    // Function tictactoe
    initializeBoard();
    while (1) {
        printBoard();
        playerMove();
        if (checkWin()) {
            printf("Player wins!\n");
            printBoard();
            return 1;
        }
        if (checkDraw()) {
            printf("It's a draw!\n");
            printBoard();
            return 0;
        }
        computerMove();
        if (checkWin()) {
            printf("Computer wins!\n");
            printBoard();
            return 0;
        }
        if (checkDraw()) {
            printf("It's a draw!\n");
            printBoard();
            return 0;
        }
    }
}

void guessTheNumber() {
    // function guess my number
    int number, guess, attempts = 0;
    srand(time(NULL));
    number = rand() % 100 + 1;

    printf("Guess the number (1 to 100):\n");
    do {
        scanf("%d", &guess);
        attempts++;
        if (guess > number) {
            printf("Lower!\n");
        } else if (guess < number) {
            printf("Higher!\n");
        }
    } while (guess != number);

    printf("You guessed it in %d attempts!\n", attempts);
}

int rockPaperScissors() {
    int playerChoice, computerChoice;
    srand(time(NULL));
    printf("Rock (1), Paper (2), Scissors (3): ");
    scanf("%d", &playerChoice);
    computerChoice = rand() % 3 + 1;

    if (playerChoice == computerChoice) {
        printf("It's a draw!\n");
        return 0;
    } else if ((playerChoice == 1 && computerChoice == 3) ||
               (playerChoice == 2 && computerChoice == 1) ||
               (playerChoice == 3 && computerChoice == 2)) {
        printf("Player wins!\n");
        return 1;
    } else {
        printf("Computer wins!\n");
        return 0;
    }
}

void readScores(PlayerScore scores[], int *size) {
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL) {
        // Kalo file scores.txt belom ada, dia write yg baru
        file = fopen("scores.txt", "w");
        if (file == NULL) {
            printf("Unable to create scores.txt file.\n");
            *size = 0;
            return;
        }
        fclose(file);
        *size = 0;
        return;
    }
    // Print username sama scorenya
    PlayerScore ps;
    while (fscanf(file, "%s %d", ps.username, &ps.score) != EOF) {
        scores[*size] = ps;
        (*size)++;
    }
    fclose(file);
}

void writeScores(PlayerScore scores[], int size) {
    FILE *file = fopen("scores.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %d\n", scores[i].username, scores[i].score);
    }
    fclose(file);
}

void searchUser(PlayerScore scores[], int size) {
    char searchName[100];
    printf("Enter username to search: ");
    scanf("%s", searchName);
    for (int i = 0; i < size; i++) {
        if (strcmp(scores[i].username, searchName) == 0) {
            printf("Username: %s, Score: %d\n", scores[i].username, scores[i].score);
            return;
        }
    }
    printf("User not found.\n");
}

void sortScores(PlayerScore scores[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (scores[i].score < scores[j].score) {
                PlayerScore temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
}

void displayScores(PlayerScore scores[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", scores[i].username, scores[i].score);
    }
}

void showMainMenu() {
    printf("\nMain Menu\n");
    printf("1. Play Tic Tac Toe\n");
    printf("2. Play Guess the Number\n");
    printf("3. Play Rock Paper Scissors\n");
    printf("4. Search User Score\n");
    printf("5. Display High Scores\n");
    printf("6. Exit\n");
}

void loginUser() {
    printf("Enter your username: ");
    scanf("%s", currentUser.username);
    currentUser.score = 0;
}

void updateUserScore(PlayerScore scores[], int *size, int addedScore) {
    int userFound = 0;
    for (int i = 0; i < *size; i++) {
        if (strcmp(scores[i].username, currentUser.username) == 0) {
            scores[i].score += addedScore;
            userFound = 1;
            break;
        }
    }
    if (!userFound) {
        strcpy(scores[*size].username, currentUser.username);
        scores[*size].score = addedScore;
        (*size)++;
    }
    writeScores(scores, *size);
}

int main() {
    PlayerScore scores[100];
    int size = 0;
    readScores(scores, &size);

    loginUser();

    int choice, gameresult;
    do {
        showMainMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                gameresult = ticTacToe();
                if(gameresult == 1)
                {
                    updateUserScore(scores, &size, 10);
                    // kalo menang dapet 10 point ke user
                }
                break;
            case 2:
                guessTheNumber();
                updateUserScore(scores, &size, 5);
                // kalo beres gamenya dapet 5 point
                break;
            case 3:
                gameresult = rockPaperScissors();
                if(gameresult == 1)
                {
                    updateUserScore(scores, &size, 7);
                    // kalo menang dapet 7 point ke user
                }
                break;
            case 4:
            // searching user sama scorenya
                searchUser(scores, size);
                break;
            case 5:
            // sorting user dari urutan point tertinggi ke rendah
                sortScores(scores, size);
                //print user sama scorenya
                displayScores(scores, size);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}