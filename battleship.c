#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Board dimensions. The game uses a 10x10 board, from A-J and 1-10.
#define BOARD_SIZE 10

// Total number of ships that each player will place.
#define MAX_SHIPS 5

// Maximum length for player names and ship names.
#define NAME_SIZE 40

// General buffer size used to read input from the console.
#define INPUT_SIZE 80

/*
    ============================================================================
    BATTLESHIP FINAL FINAL VERSION XD
    ============================================================================

    General idea:
    This program is a console version of the Battleship game where two players place
    their ships on their own boards and then attack each other by entering
    coordinates, the first player who sinks all enemy ships wins.

    Important technical decisions:
    - The code uses struct to group all data of each player.
    - The code uses enum to give readable names to board states and orientation.
*/

/*
    CellState:
    Represents what each position of the board contains.

    EMPTY: cell without visible information.
    SHIP : cell occupied by a ship.
    MISS : shot that landed in the water.
    HIT  : ship cell that was hit, but the ship is not fully sunk yet.
    SUNK : ship cell that belongs to a completely sunk ship.
*/
typedef enum {
    EMPTY = 0,
    SHIP = 1,
    MISS = 2,
    HIT = 3,
    SUNK = 5
} CellState;

/*
    Orientation:
    Used when placing ships.
    A ship can be placed horizontally or vertically.
*/
typedef enum {
    HORIZONTAL = 0,
    VERTICAL = 1
} Orientation;

/*
    Ship:
    Stores the information of one ship.

    name   : ship name shown to the user.
    symbol : letter used to display the ship on the owner's board.
    size   : number of cells occupied by the ship.
    hits   : number of times this ship has been hit.
    sunk   : 0 if it is still alive, 1 if it has been sunk.
*/
typedef struct {
    char name[NAME_SIZE];
    char symbol;
    int size;
    int hits;
    int sunk;
} Ship;

/*
    Player:
    Groups all the information of one player.

    name        : player name.
    ownBoard    : board where the player's own ships are placed.
    attackBoard : board where the player records attacks made against the enemy.
    shipIndex   : auxiliary matrix that stores which ship occupies each cell.
                  It is used to know exactly which ship was hit.
    ships       : list of ships owned by the player.
*/
typedef struct {
    char name[NAME_SIZE];
    int ownBoard[BOARD_SIZE][BOARD_SIZE];
    int attackBoard[BOARD_SIZE][BOARD_SIZE];
    int shipIndex[BOARD_SIZE][BOARD_SIZE];
    Ship ships[MAX_SHIPS];
} Player;

/*
    clearScreen:
    Clears the terminal using ANSI escape codes.
    If the terminal does not support ANSI codes, the game still works; it will
    simply print the next screen below the previous one.
*/
void clearScreen(void) {
    /* ANSI clear screen. */
    printf("\033[2J\033[H");
}

/*
    exitOnInputClosed:
    Finishes the program safely when the input stream is closed.
*/
void exitOnInputClosed(void) {
    printf("\nInput stream was closed. Program finished safely.\n");
    exit(EXIT_SUCCESS);
}

/*
    removeNewline:
    Removes the final '\n' left by fgets.
    This keeps names and commands clean before processing them.
*/
void removeNewline(char *text) {
    size_t len = strlen(text);

    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }
}

/*
    readLineOrExit:
    Centralized input function.
    It reads a complete line with fgets and exits safely if the input stream is
    closed, this avoids repeating the same fgets validation in every function.
*/
void readLineOrExit(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        exitOnInputClosed();
    }

    removeNewline(buffer);
}

/*
    waitEnter:
    Replacement for system("pause").
    It pauses the game until the user presses ENTER.
*/
void waitEnter(void) {
    char buffer[INPUT_SIZE];
    printf("\nPress ENTER to continue...");
    readLineOrExit(buffer, sizeof(buffer));
}

/*
    readText:
    Reads a non-empty text value.
    Used mainly to read player names.
*/
void readText(const char *message, char *dest, size_t size) {
    do {
        printf("%s", message);
        readLineOrExit(dest, size);

        if (strlen(dest) == 0) {
            printf("This field cannot be empty.\n");
        }
    } while (strlen(dest) == 0);
}

/*
    readIntegerInRange:
    Reads an integer and validates that it is inside the requested range.

    This function avoids repeated scanf validations and prevents invalid input
    from breaking the program.
*/
int readIntegerInRange(const char *message, int min, int max) {
    char buffer[INPUT_SIZE];
    char *endPtr;
    long value;

    while (1) {
        printf("%s", message);
        readLineOrExit(buffer, sizeof(buffer));

        // strtol is safer than scanf because it allows us to validate the entire input.
        value = strtol(buffer, &endPtr, 10);

        // Ignore trailing spaces after the number.
        while (*endPtr != '\0' && isspace((unsigned char)*endPtr)) {
            endPtr++;
        }

        if (endPtr == buffer || *endPtr != '\0') {
            printf("Invalid input. Enter a number.\n");
            continue;
        }

        if (value < min || value > max) {
            printf("Invalid range. Enter a value from %d to %d.\n", min, max);
            continue;
        }

        return (int)value;
    }
}

/*
    readColumn:
    Reads a board column from A to J and converts it to an index from 0 to 9.

    Example:
    A -> 0
    B -> 1
    J -> 9
*/
int readColumn(void) {
    char buffer[INPUT_SIZE];
    char c;

    while (1) {
        printf("Column (A-J): ");
        readLineOrExit(buffer, sizeof(buffer));

        if (strlen(buffer) == 0) {
            printf("Invalid column. Use a letter from A to J.\n");
            continue;
        }

        // Convert input to uppercase so A/a, B/b, etc to be accepted.
        c = (char)toupper((unsigned char)buffer[0]);

        if (c >= 'A' && c <= 'J') {
            return c - 'A';
        }

        printf("Invalid column. Use a letter from A to J.\n");
    }
}

/*
    readRow:
    Reads a row from 1 to 10 and converts it to an index from 0 to 9.
*/
int readRow(void) {
    return readIntegerInRange("Row (1-10): ", 1, BOARD_SIZE) - 1;
}

/*
    readOrientation:
    Reads the orientation used to place a ship.
    H means horizontal and V means vertical.
*/
Orientation readOrientation(void) {
    char buffer[INPUT_SIZE];
    char c;

    while (1) {
        printf("Orientation [H = horizontal, V = vertical]: ");
        readLineOrExit(buffer, sizeof(buffer));

        if (strlen(buffer) == 0) {
            printf("Invalid orientation. Use H or V.\n");
            continue;
        }

        c = (char)toupper((unsigned char)buffer[0]);

        if (c == 'H') {
            return HORIZONTAL;
        }

        if (c == 'V') {
            return VERTICAL;
        }

        printf("Invalid orientation. Use H or V.\n");
    }
}

/*
    printTitle:
    Prints a formatted title.
    This avoids repeating separators throughout the program.
*/
void printTitle(const char *title) {
    printf("\n========================================\n");
    printf("%s\n", title);
    printf("========================================\n");
}

/*
    printRules:
    Shows the basic rules and board symbols before the game starts.
*/
void printRules(void) {
    printTitle("BATTLESHIP - RULES");

    printf("1. Each player places 5 ships on a 10x10 board.\n");
    printf("2. Ships can be placed horizontally or vertically.\n");
    printf("3. Players attack by entering a column and a row.\n");
    printf("4. The first player to sink all enemy ships wins.\n\n");

    printf("Board symbols:\n");
    printf("  .  Unknown or empty cell\n");
    printf("  @  Miss / water\n");
    printf("  X  Hit ship\n");
    printf("  H  Sunk ship\n");
    printf("  A/B/S/D/P  Your own ships\n");
}

/*
    printShipLegend:
    Shows the player's ship list, including symbol, name, size and sunk status.
*/
void printShipLegend(const Player *player) {
    int i;

    printf("\nShips:\n");

    for (i = 0; i < MAX_SHIPS; i++) {
        printf(
            "  %c = %-12s Size: %d",
            player->ships[i].symbol,
            player->ships[i].name,
            player->ships[i].size
        );

        if (player->ships[i].sunk) {
            printf("  [SUNK]");
        }

        printf("\n");
    }
}

/*
    initializeShips:
    Loads the default ship fleet for a player.

    Each player receives the same ships:
    - Aircraft   : 5 cells
    - Battleship : 4 cells
    - Submarine  : 3 cells
    - Destroyer  : 3 cells
    - Patrol     : 2 cells
*/
void initializeShips(Player *player) {
    Ship baseShips[MAX_SHIPS] = {
        {"Aircraft",   'A', 5, 0, 0},
        {"Battleship", 'B', 4, 0, 0},
        {"Submarine",  'S', 3, 0, 0},
        {"Destroyer",  'D', 3, 0, 0},
        {"Patrol",     'P', 2, 0, 0}
    };

    for (int i = 0; i < MAX_SHIPS; i++) {
        player->ships[i] = baseShips[i];
    }
}

/*
    initializePlayer:
    Reads the player's name, clears all boards and loads the player's fleet.

    ownBoard starts empty.
    attackBoard starts empty.
    shipIndex starts with -1 because no cell has a ship assigned yet.
*/
void initializePlayer(Player *player, const char *message) {
    int i;
    int j;

    readText(message, player->name, sizeof(player->name));

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            player->ownBoard[i][j] = EMPTY;
            player->attackBoard[i][j] = EMPTY;
            player->shipIndex[i][j] = -1;
        }
    }

    initializeShips(player);
}

/*
    boardSymbol:
    Converts the numeric value of a board cell into a printable character.

    showShips controls whether ships are visible.
    - On the player's own board, ships are visible.
    - On the attack board, enemy ships remain hidden until hit.
*/
char boardSymbol(
    const Player *player,
    int board[BOARD_SIZE][BOARD_SIZE],
    int row,
    int col,
    int showShips
) {
    int value = board[row][col];

    if (value == EMPTY) {
        return '.';
    }

    if (value == MISS) {
        return '@';
    }

    if (value == HIT) {
        return 'X';
    }

    if (value == SUNK) {
        return 'H';
    }

    if (value == SHIP) {
        if (showShips) {
            int index = player->shipIndex[row][col];

            if (index >= 0 && index < MAX_SHIPS) {
                return player->ships[index].symbol;
            }

            return '#';
        }

        return '.';
    }

    return '?';
}

/*
    drawBoard:
    Prints a complete board with column letters and row numbers.

    This function works for both ownBoard and attackBoard.
    The showShips parameter decides if ships should be shown or hidden.
*/
void drawBoard(
    const char *title,
    const Player *player,
    int board[BOARD_SIZE][BOARD_SIZE],
    int showShips
) {
    int row;
    int col;

    printf("\n%s\n", title);

    printf("   ");
    for (col = 0; col < BOARD_SIZE; col++) {
        printf(" %c", 'A' + col);
    }

    printf("\n");

    for (row = 0; row < BOARD_SIZE; row++) {
        printf("%2d ", row + 1);

        for (col = 0; col < BOARD_SIZE; col++) {
            printf(" %c", boardSymbol(player, board, row, col, showShips));
        }

        printf("\n");
    }
}

/*
    isInsideBoard:
    Checks whether a row and column are inside the board limits.
*/
int isInsideBoard(int row, int col) {
    return row >= 0 &&
           row < BOARD_SIZE &&
           col >= 0 &&
           col < BOARD_SIZE;
}

/*
    canPlaceShip:
    Checks if a ship can be placed at a selected coordinate.

    It validates two things:
    1. The ship must not go outside the board.
    2. The ship must not overlap another ship.
*/
int canPlaceShip(
    const Player *player,
    int shipIndex,
    int row,
    int col,
    Orientation orientation
) {
    int size = player->ships[shipIndex].size;

    for (int k = 0; k < size; k++) {
        int r = row + (orientation == VERTICAL ? k : 0);
        int c = col + (orientation == HORIZONTAL ? k : 0);

        if (!isInsideBoard(r, c)) {
            return 0;
        }

        if (player->ownBoard[r][c] != EMPTY) {
            return 0;
        }
    }

    return 1;
}

/*
    placeShip:
    Places a ship on the player's board after validation.

    ownBoard stores that there is a ship in the selected cells.
    shipIndex stores which exact ship occupies those cells.
*/
void placeShip(
    Player *player,
    int shipIndex,
    int row,
    int col,
    Orientation orientation
) {
    int size = player->ships[shipIndex].size;

    for (int k = 0; k < size; k++) {
        int r = row + (orientation == VERTICAL ? k : 0);
        int c = col + (orientation == HORIZONTAL ? k : 0);

        player->ownBoard[r][c] = SHIP;
        player->shipIndex[r][c] = shipIndex;
    }
}

/*
    placeShipsManually:
    Allows the user to manually place every ship.

    The function repeats the input while the selected position is invalid.
*/
void placeShipsManually(Player *player) {
    int row;
    int col;
    Orientation orientation;

    for (int i = 0; i < MAX_SHIPS; i++) {
        while (1) {
            clearScreen();
            printTitle("SHIP PLACEMENT");

            printf("Player: %s\n", player->name);

            printShipLegend(player);
            drawBoard("Your board:", player, player->ownBoard, 1);

            printf(
                "\nPlace ship: %s (%c), size %d\n",
                player->ships[i].name,
                player->ships[i].symbol,
                player->ships[i].size
            );

            col = readColumn();
            row = readRow();
            orientation = readOrientation();

            if (canPlaceShip(player, i, row, col, orientation)) {
                placeShip(player, i, row, col, orientation);
                break;
            }

            printf(
                "\nInvalid position. The ship overlaps another ship "
                "or goes outside the board.\n"
            );

            waitEnter();
        }
    }
}

/*
    autoPlaceShips:
    Places all ships randomly.
*/
void autoPlaceShips(Player *player) {
    int row;
    int col;
    Orientation orientation;

    for (int i = 0; i < MAX_SHIPS; i++) {
        do {
            // Random row, random column and random orientation.
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
            orientation = (rand() % 2 == 0) ? HORIZONTAL : VERTICAL;
        } while (!canPlaceShip(player, i, row, col, orientation));

        placeShip(player, i, row, col, orientation);
    }
}

/*
    askYesNo:
    Reads a yes/no answer.
    Returns 1 for yes and 0 for no.
*/
int askYesNo(const char *message) {
    char buffer[INPUT_SIZE];
    char c;

    while (1) {
        printf("%s [Y/N]: ", message);
        readLineOrExit(buffer, sizeof(buffer));

        if (strlen(buffer) == 0) {
            printf("Invalid option. Use Y or N.\n");
            continue;
        }

        c = (char)toupper((unsigned char)buffer[0]);

        if (c == 'Y') {
            return 1;
        }

        if (c == 'N') {
            return 0;
        }

        printf("Invalid option. Use Y or N.\n");
    }
}

/*
    setupPlayerShips:
    Handles the complete ship setup process for one player.

    The player can choose between automatic placement and manual placement.
*/
void setupPlayerShips(Player *player) {
    clearScreen();
    printTitle("PLAYER SETUP");

    printf("Player: %s\n\n", player->name);

    if (askYesNo("Do you want to place ships automatically?")) {
        autoPlaceShips(player);
    } else {
        placeShipsManually(player);
    }

    clearScreen();

    printf("Ships placed for %s.\n", player->name);
    drawBoard("Final board:", player, player->ownBoard, 1);

    waitEnter();
    clearScreen();
}

/*
    markSunkShip:
    When a ship is completely destroyed, this function marks every cell of that
    ship as SUNK on both boards:

    - defender->ownBoard shows the ship as sunk.
    - attacker->attackBoard shows the result of the attack as sunk.
*/
void markSunkShip(Player *defender, Player *attacker, int shipIndex) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (defender->shipIndex[row][col] == shipIndex) {
                defender->ownBoard[row][col] = SUNK;
                attacker->attackBoard[row][col] = SUNK;
            }
        }
    }
}

/*
    allShipsSunk:
    Checks if all ships from a player have been sunk.
    If all ships are sunk, the enemy wins.
*/
int allShipsSunk(const Player *player) {
    for (int i = 0; i < MAX_SHIPS; i++) {
        if (!player->ships[i].sunk) {
            return 0;
        }
    }

    return 1;
}

/*
    printShotResult:
    Prints the result of a shot using a single reusable function.
    its to avoid the repeating messages such as HIT, MISS or SUNK in many places.
*/
void printShotResult(
    const char *attackerName,
    const char *message,
    const char *shipName
) {
    printf("\n%s: %s", attackerName, message);

    if (shipName != NULL) {
        printf(" %s", shipName);
    }

    printf("!\n");
}

/*
    playTurn:
    Executes one complete turn.

    Steps:
    1. Show the attacker's own board.
    2. Show the attacker's attack board.
    3. Ask for target coordinates.
    4. Validate that the cell was not attacked before.
    5. Check if the shot was a hit or miss.
    6. Update both boards.
    7. If a ship is fully hit, mark it as sunk.
*/
void playTurn(Player *attacker, Player *defender) {
    int row;
    int col;
    int shipIndex;

    while (1) {
        clearScreen();
        printTitle("PLAYER TURN");

        printf("Current player: %s\n", attacker->name);

        drawBoard("Your board:", attacker, attacker->ownBoard, 1);
        drawBoard("Your attacks:", attacker, attacker->attackBoard, 0);

        printf("\nChoose target coordinates.\n");

        col = readColumn();
        row = readRow();

        // A player cannot shoot twice at the same coordinate.
        if (attacker->attackBoard[row][col] != EMPTY) {
            printf("\nYou already attacked that position. Choose another one.\n");
            waitEnter();
            continue;
        }

        break;
    }

    // If the enemy board has a ship in the selected cell, it is a hit.
    if (defender->ownBoard[row][col] == SHIP) {
        shipIndex = defender->shipIndex[row][col];

        defender->ownBoard[row][col] = HIT;
        attacker->attackBoard[row][col] = HIT;

        // Increase the hit counter of the specific ship that was attacked.
        defender->ships[shipIndex].hits++;

        if (defender->ships[shipIndex].hits >= defender->ships[shipIndex].size) {
            defender->ships[shipIndex].sunk = 1;
            markSunkShip(defender, attacker, shipIndex);

            printShotResult(
                attacker->name,
                "SUNK",
                defender->ships[shipIndex].name
            );
        } else {
            printShotResult(
                attacker->name,
                "HIT",
                defender->ships[shipIndex].name
            );
        }
    } else {
        defender->ownBoard[row][col] = MISS;
        attacker->attackBoard[row][col] = MISS;

        printShotResult(attacker->name, "MISS", NULL);
    }

    drawBoard("Updated attacks:", attacker, attacker->attackBoard, 0);

    waitEnter();
}

/*
    printWinner:
    Shows the final message when the game ends.
*/
void printWinner(const Player *winner) {
    clearScreen();

    printTitle("GAME OVER");

    printf("Winner: %s\n", winner->name);
    printf("Congratulations! You sank all enemy ships.\n");
}

/*
    main:
    Program entry point.

    General flow:
    1. Print rules.
    2. Create both players.
    3. Place ships for each player.
    4. Alternate turns until one player sinks all enemy ships.
    5. Show the winner.
*/
int main(void) {
    Player player1;
    Player player2;

    Player *current;
    Player *enemy;

    // Seed for random automatic ship placement.
    srand((unsigned int)time(NULL));

    clearScreen();
    printTitle("BATTLESHIP GAME IN C");
    printRules();
    waitEnter();

    clearScreen();

    initializePlayer(&player1, "Enter Player 1 name: ");
    initializePlayer(&player2, "Enter Player 2 name: ");

    setupPlayerShips(&player1);
    setupPlayerShips(&player2);

    current = &player1;
    enemy = &player2;

    while (1) {
        playTurn(current, enemy);

        if (allShipsSunk(enemy)) {
            printWinner(current);
            break;
        }

        if (current == &player1) {
            current = &player2;
            enemy = &player1;
        } else {
            current = &player1;
            enemy = &player2;
        }
    }

    return 0;
}
