#include <iostream>

using namespace std;

//Class for Goose Piece Object
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

//Class for Fox Piece Object
class Fox{
public:
    int row, column;
    string type = "fox";
    char sign = 70;
    Fox(int r, int c){
        row = r;
        column = c;
    }
};

//prints fun fox if fox wins :3
void print_fox(){
    cout << R"( /\   /\)" << endl;
    cout << R"(//\\_//\\     ____)" << endl;
    cout << R"(\_     _/    /   /)" << endl;
    cout << R"( / ^ ^ \    /^^^])" << endl;
    cout << R"( \_\O/_/    [   ])" << endl;
    cout << R"(  /   \_    [   /)" << endl;
    cout << R"(  \     \_  /  /)" << endl;
    cout << R"(   [ [ /  \/ _/)" << endl;
    cout << R"(  _[ [ \  /_/)" << endl;
}

//prints fun goose if geese win :3
void print_goose(){
    cout << R"(                                   ___)" << endl;
    cout << R"(                               ,-""   `.)" << endl;
    cout << R"(                             ,'  _   ^ )`-._)" << endl;
    cout << R"(                            /  ,' `-._<.===-')" << endl;
    cout << R"(                           /  /)" << endl;
    cout << R"(                          /  ;)" << endl;
    cout << R"(   _          _          /   ;)" << endl;
    cout << R"( (`._    _.-"" ""--..__,'    |)" << endl;
    cout << R"( <_  `-""                     \)" << endl;
    cout << R"(  <`-                          :)" << endl;
    cout << R"(   (__   <__.                  ;)" << endl;
    cout << R"(     `-.   '-.__.      _.'    /)" << endl;
    cout << R"(        \      `-.__,-'    _,')" << endl;
    cout << R"(         `._    ,    /__,-')" << endl;
    cout << R"(            ""._\__,'< <____)" << endl;
    cout << R"(                 | |  `----.`.)" << endl;
    cout << R"(                 | |        \ `.)" << endl;
    cout << R"(                 ; |___      \-``)" << endl;
    cout << R"(                 \   --<)" << endl;
    cout << R"(                  `.`.<)" << endl;
    cout << R"(                    `-')" << endl;

}

//Function to print out board with pieces
void board_set(char b[8][8], Goose g[4], Fox f[1]){
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

    b[f[0].row][f[0].column] = f[0].sign;

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
            default:
                cout << "That is not a valid choice." << endl;
                goto START;
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
        else{valid_choice = true;}
    }
    //Moves piece that is on left edge
    if(chosen_goose.column == 0){
        char confirm;
        bool confirmation = false;
        while (!confirmation) {
            cout << "You can only move downward right. Continue? (Y/n): ";
            cin >> confirm;
            if (confirm == 110) {
                valid_choice = false;
                goto START;
            } else if (confirm == 89) {
                confirmation = true;
                chosen_goose.row += 1;
                chosen_goose.column += 1;
            }
            else{cout << "That is not a valid option." << endl;}
        }
    }
    //Moves piece that is on right edge
    else if(chosen_goose.column == 7){
        char confirm;
        bool confirmation = false;
        while (!confirmation) {
            cout << "You can only move downward left. Continue? (Y/n): ";
            cin >> confirm;
            if (confirm == 110) {
                valid_choice = false;
                goto START;
            } else if (confirm == 89) {
                confirmation = true;
                chosen_goose.row += 1;
                chosen_goose.column -= 1;
            }
            else{cout << "That is not a valid option." << endl;}
        }
    }
    //Moves piece not on left or right edge
    else{
        char confirm, direction;
        bool can_move = false, confirmation = false;
        while (!confirmation) {
            cout << "You can choose to move downward left or right. Continue? (Y/n): ";
            cin >> confirm;
            if (confirm == 110) {
                valid_choice = false;
                goto START;
            } else if (confirm == 89) {
                confirmation = true;
                while (!can_move) {
                    cout << "Would you like to go (L)eft or (r)ight? ";
                    cin >> direction;
                    if (direction == 76 && b[chosen_goose.row + 1][chosen_goose.column - 1] == 32) {
                        chosen_goose.row += 1;
                        chosen_goose.column -= 1;
                        can_move = true;
                    } else if (direction == 114 && b[chosen_goose.row + 1][chosen_goose.column + 1] == 32) {
                        chosen_goose.row += 1;
                        chosen_goose.column += 1;
                        can_move = true;
                    } else { cout << "You are unable to make that move." << endl; }
                }
            }
            else{cout << "That is not a valid option." << endl;}
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
//determines how fox piece moves
void fox_move(char b[8][8], Fox f[1]){
    cout << "It is the fox's turn." << endl;
    Fox chosen(NULL, NULL);
    chosen.row = f[0].row;
    chosen.column = f[0].column;
    char lateral, longitude;
    bool valid_choice = false;
    //movement for when it is in the bottom row
    if (chosen.row == 7){
        //left bottom corner
        if (chosen.column == 0){
            cout << "You can only move upward right." << endl;
            chosen.row -= 1;
            chosen.column += 1;
        }
        //right bottom corner
        else if (chosen.column == 7){
            cout << "You can only move upward left." << endl;
            chosen.row -= 1;
            chosen.column -= 1;
        }
        //not in either corner
        else {
            while (!valid_choice) {
                cout << "Would you like to move upward (L)eft or (r)ight? ";
                cin >> lateral;
                if (lateral == 76 && b[chosen.row - 1][chosen.column - 1] == 32) {
                    chosen.row = chosen.row - 1;
                    chosen.column = chosen.column - 1;
                    valid_choice = true;
                } else if (lateral == 114 && b[chosen.row - 1][chosen.column + 1] == 32) {
                    chosen.row -= 1;
                    chosen.column += 1;
                    valid_choice = true;
                }
                else {cout << "You cannot move your piece there." << endl;}
            }

        }
    }
    //movement for while on the left side of the board
    else if(chosen.column == 0){
        while (!valid_choice){
            cout << "Would you like to move right (U)pwards or (d)ownwards? ";
            cin >> longitude;
            if(longitude == 85 && b[chosen.row - 1][chosen.column + 1] == 32){
                chosen.row -= 1;
                chosen.column += 1;
                valid_choice = true;
            }
            else if(longitude == 100 && b[chosen.row + 1][chosen.column + 1] == 32){
                chosen.row += 1;
                chosen.column += 1;
                valid_choice = true;
            }
            else{cout << "You cannot move your piece there." << endl;}
        }
    }
    //movement for while on the right side of the board
    else if(chosen.column == 7){
        while (!valid_choice){
            cout << "Would you like to move left (U)pwards or (d)ownwards? ";
            cin >> longitude;
            if(longitude == 85 && b[chosen.row - 1][chosen.column - 1] == 32){
                chosen.row -= 1;
                chosen.column -= 1;
                valid_choice = true;
            }
            else if(longitude == 100 && b[chosen.row + 1][chosen.column - 1] == 32){
                chosen.row += 1;
                chosen.column -= 1;
                valid_choice = true;
            }
            else{cout << "You cannot move your piece there." << endl;}
        }
    }

    //movement for in the middle of the board
    else{
        while(!valid_choice) {
            cout << "Would you like to move (U)p or (d)own? ";
            cin >> longitude;
            cout << "Would you like to move (L)eft or (r)ight? ";
            cin >> lateral;
            if(longitude == 85){
                if (lateral == 76 && b[chosen.row - 1][chosen.column - 1] == 32) {
                    chosen.row -= 1;
                    chosen.column -= 1;
                    valid_choice = true;
                }
                else if (lateral == 114 && b[chosen.row - 1][chosen.column + 1] == 32) {
                    chosen.row -= 1;
                    chosen.column += 1;
                    valid_choice = true;
                }
                else {cout << "You cannot move your piece there." << endl;}
            }
            else if(longitude == 100){
                if (lateral == 76 && b[chosen.row + 1][chosen.column - 1] == 32) {
                    chosen.row += 1;
                    chosen.column -= 1;
                    valid_choice = true;
                }
                else if (lateral == 114 && b[chosen.row + 1][chosen.column + 1] == 32) {
                    chosen.row += 1;
                    chosen.column += 1;
                    valid_choice = true;
                }
                else {cout << "You cannot move your piece there." << endl;}
            }
        }
    }
    f[0].row = chosen.row;
    f[0].column = chosen.column;
}

//checks if win conditions for game have been met
bool check_game_over(char b[8][8], Fox f) {
    //checks if fox wins by reaching top row
    if (f.row == 0) {
        cout << "The fox wins!!" << endl;
        print_fox();
        return true;
    }
    //checks if geese win by trapping the fox, so it can't move
    else {
        if (f.row == 7) {
            //left bottom corner
            if (f.column == 0 && b[f.row + 1][f.column - 1] != 32) {
                cout << "The geese win!!" << endl;
                print_goose();
                return true;
            }
                //right bottom corner
            else if (f.column == 7 && b[f.row - 1][f.column - 1] != 32) {
                cout << "The geese win!!" << endl;
                print_goose();
                return true;
            }
                //not in either corner
            else {
                if (b[f.row - 1][f.column - 1] != 32 && b[f.row + 1][f.column - 1] != 32) {
                    cout << "The geese win!!" << endl;
                    print_goose();
                    return true;
                }
            }
        }
        else if (f.column == 0 && b[f.row - 1][f.column + 1] != 32 && b[f.row + 1][f.column + 1] != 32){
            cout << "The geese win!!" << endl;
            print_goose();
            return true;
        }
        else if (f.column == 7 && b[f.row - 1][f.column - 1] != 32 && b[f.row + 1][f.column - 1] != 32){
            cout << "The geese win!!" << endl;
            print_goose();
            return true;
        }
        else if (b[f.row - 1][f.column - 1] != 32 && b[f.row + 1][f.column - 1] != 32 && b[f.row - 1][f.column + 1]
        != 32 && b[f.row + 1][f.column + 1] != 32){
            cout << "The geese win!!" << endl;
            print_goose();
            return true;
        }
    }
    return false;
}

int main() {
    char board[8][8];

    Fox fox(7, 4);

    Goose goose1(0, 1, 65), goose2(0, 3, 66), goose3(0, 5, 67), goose4(0, 7, 68);

    Goose geese[4] = {goose1, goose2, goose3, goose4};
    Fox foxes[1] = {fox};

    board_set(board, geese, foxes);

    bool game_over = false;

    while(!game_over){
        goose_move(board, geese);
        board_set(board, geese, foxes);
        game_over = check_game_over(board, foxes[0]);
        if(game_over){
            break;
        }
        fox_move(board, foxes);
        board_set(board, geese, foxes);
        game_over = check_game_over(board, foxes[0]);
    }

    return 0;
}
