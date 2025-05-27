#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ----- Player Class -----
class Player {
    string name;
    char symbol;

public:
    Player(string name, char symbol) : name(name), symbol(symbol) {}
    string getName() const { return name; }
    char getSymbol() const { return symbol; }
};

// ----- Move Class -----
class Move {
    int row, col;

public:
    Move(int r, int c) : row(r), col(c) {}
    int getRow() const { return row; }
    int getCol() const { return col; }
};

// ----- Board Class -----
class Board {
    vector<vector<char>> grid;

public:
    Board() {
        grid = vector<vector<char>>(3, vector<char>(3, ' '));
    }

    void print() const {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " ";
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    bool isFull() const {
        for (auto& row : grid)
            for (char cell : row)
                if (cell == ' ') return false;
        return true;
    }

    bool placeSymbol(int row, int col, char symbol) {
        if (isValidMove(row, col)) {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    bool isValidMove(int row, int col) const {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ';
    }

    bool checkWin(char symbol) const {
        // Check rows & columns
        for (int i = 0; i < 3; ++i) {
            if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
                (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol))
                return true;
        }
        // Diagonals
        if ((grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
            (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol))
            return true;

        return false;
    }
};

// ----- TicTacToe Class -----
class TicTacToe {
    Player player1;
    Player player2;
    Player* currentPlayer;
    Board board;

public:
    TicTacToe(string name1, string name2)
        : player1(name1, 'X'), player2(name2, 'O'), currentPlayer(&player1) {}

    void switchTurn() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    void playGame() {
        cout << "Tic Tac Toe Game Started!\n";
        board.print();

        while (true) {
            int row, col;
            cout << currentPlayer->getName() << " (" << currentPlayer->getSymbol() << "), enter row and column (0-2): ";
            cin >> row >> col;

            if (!board.placeSymbol(row, col, currentPlayer->getSymbol())) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            board.print();

            if (board.checkWin(currentPlayer->getSymbol())) {
                cout << currentPlayer->getName() << " wins!\n";
                break;
            }

            if (board.isFull()) {
                cout << "It's a draw!\n";
                break;
            }

            switchTurn();
        }
    }
};

// ----- Main -----
int main() {
    string name1, name2;
    cout << "Enter Player 1 name (X): ";
    cin >> name1;
    cout << "Enter Player 2 name (O): ";
    cin >> name2;

    TicTacToe game(name1, name2);
    game.playGame();

    return 0;
}
