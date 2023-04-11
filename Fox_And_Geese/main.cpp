#include <iostream>

using namespace std;

class Goose{
public:
    int row, column;
    string type = "geese";
    char sign;
    Goose(int r, int c, char s){
        row = r;
        column = c;
        sign = s;
    }
};

class Fox{
public:
    int row, column;
    string type = "fox";
    char sign = 70;
};

void board_set(char b[8][8], Goose g[4], Fox f){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ((j+i)%2 == 0) {
                b[i][j] = 35;
            }
            else{
                b[i][j] = 32;
            }
        }
    }

    for (int h = 0; h < 4; h++){
        b[g[h].row][g[h].column] = g[h].sign;
    }

    b[f.row][f.column] = f.sign;

    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << "[" << b[i][j] << "] ";
        }
        cout << endl;
    }
}

//determines how goose pieces move
void goose_move(char b[8][8], Goose g[4]){
    cout << "It is the geese's turn." << endl;
    char choice;
    Goose chosen_goose(NULL, NULL, NULL);
    bool valid_choice = false;
    //Choose piece. Will reject and force to choose other piece if it cannot move
    START:while (!valid_choice) {
        cout << "Choose which piece to move (A, B, C, D): ";
        cin >> choice;
        switch (choice) {
            case 65:
                chosen_goose.row = g[0].row;
                chosen_goose.column = g[0].column;
                chosen_goose.sign = g[0].sign;
                break;
            case 66:
                chosen_goose.row = g[1].row;
                chosen_goose.column = g[1].column;
                chosen_goose.sign = g[1].sign;
                break;
            case 67:
                chosen_goose.row = g[2].row;
                chosen_goose.column = g[2].column;
                chosen_goose.sign = g[2].sign;
                break;
            case 68:
                chosen_goose.row = g[3].row;
                chosen_goose.column = g[3].column;
                chosen_goose.sign = g[3].sign;
                break;
        }
        if (chosen_goose.row == 7) {
            cout << "You cannot move that piece." << endl;
        }
        else if(chosen_goose.column == 0 && b[chosen_goose.row + 1][chosen_goose.column + 1] != 32){
            cout << "You cannot move that piece." << endl;
        }
        else if(chosen_goose.column == 7 && b[chosen_goose.row + 1][chosen_goose.column - 1] != 32){
            cout << "You cannot move that piece." << endl;
        }
        else if(b[chosen_goose.row + 1][chosen_goose.column + 1] != 32 && b[chosen_goose.row + 1]
        [chosen_goose.column - 1] != 32){
            cout << "You cannot move that piece." << endl;
        }
        else{ valid_choice = true;}
    }
    //Moves piece that is on left edge
    if(chosen_goose.column == 0){
        char confirm;
        cout << "You can only move downward right. Continue? (Y/n): ";
        cin >> confirm;
        if (confirm == 110){
            valid_choice = false;
            goto START;
        }
        else if(confirm == 89){
            b[chosen_goose.row + 1][chosen_goose.column + 1] = chosen_goose.sign;
            b[chosen_goose.row][chosen_goose.column] = 32;
            chosen_goose.row += 1;
            chosen_goose.column += 1;
        }
    }
    //Moves piece that is on right edge
    else if(chosen_goose.column == 7){
        char confirm;
        cout << "You can only move downward left. Continue? (Y/n): ";
        cin >> confirm;
        if (confirm == 110){
            valid_choice = false;
            goto START;
        }
        else if(confirm == 89){
            b[chosen_goose.row + 1][chosen_goose.column - 1] = chosen_goose.sign;
            b[chosen_goose.row][chosen_goose.column] = 32;
            chosen_goose.row += 1;
            chosen_goose.column -= 1;
        }
    }
    //Moves piece not on left or right edge
    else{
        char confirm, direction;
        bool can_move = false;
        cout << "You can choose to move downward left or right. Continue? (Y/n): ";
        cin >> confirm;
        if (confirm == 110){
            valid_choice = false;
            goto START;
        }
        else if(confirm == 89){
            while(!can_move) {
                cout << "Would you like to go (L)eft or (r)ight? ";
                cin >> direction;
                if (direction == 76 && b[chosen_goose.row + 1][chosen_goose.column - 1] == 32) {
                    b[chosen_goose.row + 1][chosen_goose.column - 1] = chosen_goose.sign;
                    b[chosen_goose.row][chosen_goose.column] = 32;
                    chosen_goose.row += 1;
                    chosen_goose.column -= 1;
                    can_move = true;
                } else if (direction == 114 && b[chosen_goose.row + 1][chosen_goose.column + 1]) {
                    b[chosen_goose.row + 1][chosen_goose.column + 1] = chosen_goose.sign;
                    b[chosen_goose.row][chosen_goose.column] = 32;
                    chosen_goose.row += 1;
                    chosen_goose.column += 1;
                    can_move = true;
                }
                else{cout << "You are unable to make that move." << endl;}
            }
        }

    }
    //makes necessary changes to pieces to save for future moves
    switch(choice){
        case 65:
            g[0].row = chosen_goose.row;
            g[0].column = chosen_goose.column;
            break;
        case 66:
            g[1].row = chosen_goose.row;
            g[1].column = chosen_goose.column;
            break;
        case 67:
            g[2].row = chosen_goose.row;
            g[2].column = chosen_goose.column;
            break;
        case 68:
            g[3].row = chosen_goose.row;
            g[3].column = chosen_goose.column;
            break;
    }
}

void fox_move(char b[8][8], Fox f){
    cout << "It is the fox's turn." << endl;
    char lateral, longitude;
    if (f.row == 0){
        if (f.column == 0){
            cout << "You can only move upward right." << endl;
            b[f.row + 1][f.column + 1] = f.sign;
            b[f.row][f.column] = 32;
            f.row += 1;
            f.column += 1;
        }
        else if (f.column == 7){
            cout << "You can only move upward left." << endl;
            b[f.row + 1][f.column - 1] = f.sign;
            b[f.row][f.column] = 32;
            f.row += 1;
            f.column -= 1;
        }
        else{
            cout << "Would you like to move upward (L)eft or (r)ight? ";
            cin >> lateral;

        }
    }
}

int main() {
    char board[8][8];

    Fox fox;
    fox.row = 7;
    fox.column = 4;

    Goose goose1(0, 1, 65), goose2(0, 3, 66), goose3(0, 5, 67), goose4(0, 7, 68);

    Goose geese[4] = {goose1, goose2, goose3, goose4};

    board_set(board, geese, fox);

    bool game_over = false;

    while(not game_over){
        goose_move(board, geese);
        board_set(board, geese, fox);
//        game_over = check_game_over();
//        fox_move(board, fox);
//        board_set(board, geese, fox);
//        game_over = check_game_over();
    }

    return 0;
}
