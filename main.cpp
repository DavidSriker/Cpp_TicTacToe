#include <iostream>
#include <string>

using namespace std;

char gameBoard[3][3] = {'1','2','3',
                        '4','5','6',
                        '7','8','9'};

// Function decelerations
void printIntro(string &first_player, string &second_player);
void printBoard();
void printStatus(string first_player, string second_player, int turn);
bool checkWinTie(int turn, int num_moves, int &winner, int &tie);
bool checkRow(char player_char);
bool checkCol(char player_char);
bool checkDiag(char player_char);
void transformLocation(char location, int &row_out, int &col_out);
void getPlayerMove(string first_player, string second_player, int turn, int &row, int &col);
bool checkValidLocation(int row, int col, char location);
void setPlayerMove(int row, int col, int turn);
void printEnding(string first_player, string second_player, int winner, int tie);

int main() {
    int turn {0}, moves {0}, row {0}, col {0}, winner {-1}, tie {-1};
    string first_player_name {}, second_player_name {};
    bool game_finished {false};

    printIntro(first_player_name, second_player_name);

    while(!game_finished){
        printStatus(first_player_name, second_player_name, turn);
        getPlayerMove(first_player_name, second_player_name, turn, row, col);
        setPlayerMove(row, col, turn);
        game_finished = checkWinTie(turn, moves, winner, tie);
        moves++;
        turn = (turn + 1) % 2;
    }

    printEnding(first_player_name, second_player_name, winner, tie);
    return 0;
}


void printIntro(string &first_player, string &second_player){
    cout << "Hello Welcome to the TicTacToe game" << endl;
    cout << "Please enter first player name: ";
    getline(cin, first_player);
    cout << "Hello " << first_player << " you are o" << endl;

    cout << "Please enter second player name: ";
    getline(cin, second_player);
    cout << "Hello " << second_player << " you are x" << endl;
    return;
}

void printBoard(){
    int row {0}, col{0};

    cout << "Board Status:" << endl;
    for (row = 0; row < 3; row++){
        cout << "    ";
        for (col = 0; col < 3; col++) {
            if (row != 0 && col == 0){
                cout << "|____|____|____|" << endl;
                cout << "    ";
            }
            cout << "|  "<< gameBoard[row][col] << " ";
        }
        cout << "|" << endl;
    }
}

void printStatus(string first_player, string second_player, int turn){

    if (turn == 0) {
        // player 1 turn -> o
        cout << first_player << " turn <o>" << endl;
    } else {
        // player 2 turn -> x
        cout << second_player << " turn <x>" << endl;
    }
    cout << "<=================================>" << endl;
    printBoard();
    return;
}

bool checkWinTie(int turn, int num_moves, int &winner, int &tie){
    bool win_tie {false};
    char turn_symbol;

    if (turn == 0) {
        turn_symbol = 'o';
    } else {
        turn_symbol = 'x';
    }
    win_tie = checkRow(turn_symbol);
    win_tie = win_tie || checkCol(turn_symbol);
    win_tie = win_tie || checkDiag(turn_symbol);
    if (win_tie){ // someone won!
        winner = turn;
    }
    win_tie = win_tie || (num_moves == 8);
    if (win_tie){ // its a tie!
        tie = turn;
    }

    return win_tie;

}

bool checkRow(char player_char){
    bool res {false};

    for (int i = 0; i < 3; i++){
        res = res || ((gameBoard[i][0] == player_char) && (gameBoard[i][1] == player_char) &&
                      (gameBoard[i][2] == player_char));
    }
    return res;
}

bool checkCol(char player_char){
    bool res {false};

    for (int i = 0; i < 3; i++){
        res = res || ((gameBoard[0][i] == player_char) && (gameBoard[1][i] == player_char) &&
                      (gameBoard[2][i] == player_char));
    }
    return res;
}

bool checkDiag(char player_char){
    bool res {false};

    res = (gameBoard[0][0] == player_char) && (gameBoard[1][1] == player_char) &&
            (gameBoard[2][2] == player_char);
    res = res || ((gameBoard[0][2] == player_char) && (gameBoard[1][1] == player_char) &&
                  (gameBoard[2][0] == player_char));

    return res;
}

void transformLocation(char location, int &row_out, int &col_out){
    for (int row {0}; row < 3; row ++){
        for (int col {0}; col < 3; col++){
            if (gameBoard[row][col] == location) {
                row_out = row;
                col_out = col;
                break;
            }
        }
    }
}

void getPlayerMove(string first_player, string second_player, int turn, int &row, int &col){
    char loc {'Z'};
    int row_in {}, col_in {};
    while (loc == 'Z'){
        if (turn == 0) {
            cout << first_player << " please enter where you want to place the <o>: ";
            cin >> loc;
        } else {
            cout << second_player << " please enter where you want to place the <x>: ";
            cin >> loc;
        }

        transformLocation(loc, row, col);
        if (checkValidLocation(row, col, loc)) {
            loc = 'Z';
            cout << "Invalid location!!" << endl;
        }
    }
    return;
}

bool checkValidLocation(int row, int col, char location){
    int loc {};
    bool res {false};
    char loc_value {};
    // check that the location is between 1-9
    loc = location - '0';
    cout << loc << endl;
    res = (loc < 1 || loc > 9);
    // check that the board at position is available
    loc_value = gameBoard[row][col];
    loc = loc_value - '0';
    res = res || (loc < 1 || loc > 9);
    return res;
}

void setPlayerMove(int row, int col, int turn){

    if (turn == 0){
        gameBoard[row][col] = 'o';
    } else {
        gameBoard[row][col] = 'x';
    }
    return;
}

void printEnding(string first_player, string second_player, int winner, int tie){

    cout << "Good match " << first_player << " and " << second_player << endl;
    if (tie != -1) {
        cout << "The game ended with a tie" << endl;
        cout << "<=================================>" << endl;
        printBoard();
    } else if (winner != -1) {
        if (winner == 0) {
            cout << "The Winner is: " << first_player << " with <o>" << endl;
            cout << "Better luck next time " << second_player << endl;
            cout << "<=================================>" << endl;
            printBoard();
        } else {
            cout << "The Winner is: " << second_player << " with <x>" << endl;
            cout << "Better luck next time " << first_player << endl;
            cout << "<=================================>" << endl;
            printBoard();
        }
    }
}