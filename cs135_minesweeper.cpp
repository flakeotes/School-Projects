#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

/*  Finnick Lakeotes, 5004855838, CS135-1004, Assignment 11
    To update our simulation of minesweeper
    Input: Player inputs coordinates
    Output: Game of Minesweeper

    Algorithm:  1. Write mine locations
                2. Display Board
                3. Ask user for x y 
                4. Checks x y for mine 
                    -if yes ends game and displays mines
                5. If no, sets xy to 0 and calculates value
                6. Next passes to displayBoard
                   displayBoard checks for mine prox and updates board
                7. hasPlayerWon runs after board update
                    -if no, returns to 2.
                    -if yes, displays final board and exits
*/

const int BOARD_HEIGHT = 9;
const int BOARD_WIDTH = 12;
//declares global const


struct tile{
    char letter;
    bool hasMine;
};

struct minesweeper{
    tile board[BOARD_HEIGHT][BOARD_WIDTH];
    int width;
    int height;
    int mineCount;
    int flagCount;
    int unrevealCount;
    int moves;
};

/*  displayBoard: writes out current board to display
    parameters: board array and x y coordinates
    return value: no return value  */
void displayBoard(minesweeper);

/*  displayMines: displays the mine locations if user loses 
    parameters: mines location array, height and width
    return value: no return value  */
void displayMines(minesweeper);

/*  hasPlayerWon: checks to see if player has won
    parameters: board array, mines array, and x y coordinates 
    return value: true if win, false if game is to continue  */
bool hasPlayerWon(minesweeper);

int main(int argc, char* argv[]){
    
    minesweeper game;
    game.height = BOARD_HEIGHT;
    game.width = BOARD_WIDTH;
    game.moves = 1;
    game.mineCount = 10;
    game.flagCount = 0;
    //sets up game.

    for (int i = 0; i < BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            game.board[i][j].hasMine = false;
            game.board[i][j].letter = '?';
        }
    }
    //sets struct board to default state 
    srand(time(NULL)); 
    int rowhold = 0, colhold = 0;
    int xdig = 0, ydig = 0;
    bool end = false;
    bool questcheck = false;
    char action = ' ';
    //declares local variables
   

     if(argc > 1){
        srand(0);
        //changes seed for debug map
    }
    
    for (int h = 0; h < game.mineCount; h++){
        rowhold = rand() % game.height;
        colhold = rand() % game.width;
        //generates mine location
        while (game.board[rowhold][colhold].hasMine == true){
            rowhold = rand() % game.height;
            colhold = rand() % game.width;
            //rerolls if already a mine at location
        }                         
        game.board[rowhold][colhold].hasMine = true;
        //writes mine location to array after doubles check
    } 
        do{
            displayBoard(game);
            //calls for board to display to user            

                cout << "Move #" << game.moves << endl
                     << "[D]ig up tile" << endl
                     << "[F]lag/Unflag Tile. " << game.flagCount 
                     << " flag(s) placed." << endl
                     << "[Q]uit " << endl
                     << "Choose an action: ";
                cin >> action;
                //displays menu to user

                while(action != 'd' && action != 'D' && action != 'f' && action != 'F' && action != 'q' && action != 'Q'){
                    cout << "Invalid entry, please try again:";
                    cin >> action;
                }

                switch(action){

                    case 'd':
                    case 'D':
                        game.moves++;      

                        do{
                            questcheck = false;                
                            //resets ? check
                            cout << "Dig at X:";
                            cin >> xdig;
                            //prompts user for x dig site
                            while(xdig > BOARD_WIDTH || xdig <= 0){
                                cout << "Error with X value, please try again" << endl;
                                cin.clear();
                                cin.ignore(80, '\n');
                                cout << "Dig at X: ";
                                cin >> xdig;
                                //clears x and reprompts user
                            }
                            //checks that x is in bounds, loops again if not

                            cout << "Dig at Y:";
                            cin >> ydig;
                            //prompts user for y dig site
                            while(ydig > BOARD_HEIGHT || ydig <= 0){
                                cout << "Error with Y value, please try again" << endl;
                                cin.clear();
                                cin.ignore(80, '\n');
                                cout << "Dig at Y:";
                                cin >> ydig;
                                //clears y and reprompts user
                            }
                            //checks that y is in bounds, loops again if not
             
                            ydig--;
                            xdig--;
                            //decrements user input to match array indexes

                            if(game.board[ydig][xdig].letter != '?'){
                            questcheck = true;
                            cout << "Can't dig at a site that has already been dug!" 
                                 << endl;
                            //cant dig at non ? squares makes user re-select
                            }
                        }while(questcheck); 
                        //loops if user can't dig at specified site

                        if(game.board[ydig][xdig].hasMine == true){
                            displayMines(game);
                            return 0;
                        }
                        //if dig site is on mine ends game

                        else{
                            game.board[ydig][xdig].letter = '0';
                            //starts at '0'

                            if (ydig-1 < BOARD_HEIGHT && ydig - 1 >= 0){ 
                            //if top row exists
                                if( game.board[ydig-1][xdig].hasMine == true){ 
                                    game.board[ydig][xdig].letter += 1;
                                }
                                //checks top middle for mine prox
                                if(xdig-1 < BOARD_WIDTH && xdig - 1>=0){
                                 //if top row exists, see if top left exist
                                    if( game.board[ydig-1][xdig-1].hasMine == true){
                                        game.board[ydig][xdig].letter += 1;
                                    }
                                    //checks top left for mine prox
                                }
                                if(xdig+1 < BOARD_WIDTH){
                                //if top row exists, see if top right exist
                                if( game.board[ydig-1][xdig+1].hasMine == true){
                                    game.board[ydig][xdig].letter += 1;
                                }
                                //checks top right for mine prox
                                }
                            }   
                            //TOP ROW CHECKER

                            if(xdig - 1 < BOARD_WIDTH && xdig - 1 >=0){
                            //checks to see if left side exists
                                if(game.board[ydig][xdig-1].hasMine == true){
                                    game.board[ydig][xdig].letter += 1;
                                }
                                //checks for mine prox to left
                            }
                            //LEFT SIDE CHECKER

                        if(xdig + 1 < BOARD_WIDTH && xdig + 1 >=0){
                        //checks to see if right side exists
                            if(game.board[ydig][xdig+1].hasMine == true){
                                game.board[ydig][xdig].letter += 1;
                            }
                            //checks for mine prox to right
                        }
                        //RIGHT SIDE CHECKER    


                        if (ydig+1 < BOARD_HEIGHT && ydig+1 >= 0){ 
                        //if bottom row exists
                            if( game.board[ydig+1][xdig].hasMine == true){
                                game.board[ydig][xdig].letter += 1;
                            }
                            //checks bottom middle for mine prox
                            if(xdig-1 < BOARD_WIDTH && xdig - 1 >=0){
                            //if bottom row exists, see if bottom left exists
                                if( game.board[ydig+1][xdig-1].hasMine == true){
                                    game.board[ydig][xdig].letter += 1;
                                }
                                //checks bottom left for mine prox
                            }
                            if(xdig + 1 < BOARD_WIDTH && xdig + 1 >=0){
                            //if bottom row exists, see if bottom right exists
                                if(game.board[ydig+1][xdig+1].hasMine == true){
                                    game.board[ydig][xdig].letter += 1;
                                }
                                //checks bottom right for mine prox
                            }
                        }
                        //BOTTOM ROW CHECKER
    
                        if(game.board[ydig][xdig].letter == '0'){
                        //if square has no prox to mines after checking, balloon outwards 
                            game.width = xdig;
    
                            int y = ydig;
                            int x  = xdig;
                            bool checkagain = false;
                            //initializes variables for clearing
 
                            if (y-1 < BOARD_HEIGHT && y - 1 >= 0){ 
                            //if top row exists
                                if(game.board[y-1][x].letter == '?'){
                                    game.board[y-1][x].letter = '0'; 
                                    //cout << game.board[y-1][x].letter << endl;
                                }                   
                                //changes top middle to '0'
                                if(x-1 < BOARD_WIDTH && x - 1 >= 0){
                                //if top row exists, see if top left exist
                                    if(game.board[y-1][x-1].letter == '?')
                                        game.board[y-1][x-1].letter = '0';
                                        //changes top left to '0'
                                    }
                                    if(x+1 < BOARD_WIDTH){
                                    //if top row exists, see if top right exist
                                    if(game.board[y-1][x+1].letter == '?')
                                        game.board[y-1][x+1].letter = '0';
                                        //changes top right to '0'
                                    }
                            }
                            //TOP ROW CHECKER
            
                            if(x - 1 < BOARD_WIDTH && x - 1 >= 0){
                            //checks to see if left side exists
                                if(game.board[y][x-1].letter == '?')
                                    game.board[y][x-1].letter = '0';
                            }
                            //LEFT SIDE CHECKER

                            if(x + 1 < BOARD_WIDTH && x + 1 >= 0){
                            //checks to see if right side exists
                            if(game.board[y][x+1].letter == '?')
                                game.board[y][x+1].letter = '0';
                            }
                            //RIGHT SIDE CHECKER    

                            if (y+1 < BOARD_HEIGHT && y+1 >= 0){ 
                            //if bottom row exists
                                if(game.board[y+1][x].letter == '?')
                                    game.board[y+1][x].letter = '0';
                                    //changes bottom middle to '0'

                                if(x-1 < BOARD_WIDTH && x-1 >=0){
                                //if bottom row exists, see if bottom left exists
                                    if(game.board[y+1][x-1].letter == '?')
                                        game.board[y+1][x-1].letter = '0';
                                        //changes bottom left to '0'
                                }
                                if(x+1 < BOARD_WIDTH && x+1 >=0){
                                //if bottom row exists, see if bottom right exists
                                    if(game.board[y+1][x+1].letter == '?')
                                        game.board[y+1][x+1].letter = '0';                
                                        //changes bottom right to '0'
                                }
                            }
                            //BOTTOM ROW CHECK
                //sets surrounding points to '0'
                            do{
                                checkagain = false;
                                //resets check again

                                for(int i = 0; i < BOARD_HEIGHT; i++){
                                    for(int j = 0; j < BOARD_WIDTH; j++){

                                        if(game.board[i][j].letter == '0'){
                                            if (i-1 < BOARD_HEIGHT && i - 1 >= 0){ 
                                            //if top row exists
                                                if( game.board[i-1][j].hasMine == true){
                                                    game.board[i][j].letter += 1;
                                                    checkagain = true;
                                                }
                                                //checks top middle for mine prox
                                                if(j-1 < BOARD_WIDTH && j - 1>=0){
                                                //if top row exists, see if top left exist
                                                    if( game.board[i-1][j-1].hasMine == true){                    
                                                        game.board[i][j].letter += 1;
                                                        checkagain = true;
                                                    }
                                                    //checks top left for mine prox
                                                }
                                                if(j+1 < BOARD_WIDTH){
                                                //if top row exists, see if top right exist
                                                    if( game.board[i-1][j+1].hasMine == true){                    
                                                        game.board[i][j].letter += 1;
                                                        checkagain = true;
                                                    }
                                                    //checks top right for mine prox
                                                }
                                            }
                                            //TOP ROW CHECKER

                                            if(j - 1 < BOARD_WIDTH && j - 1 >=0){
                                            //checks to see if left side exists
                                                if(game.board[i][j-1].hasMine == true){
                                                    game.board[i][j].letter += 1;
                                                    checkagain = true;
                                                }
                                                //checks for mine prox to left
                                            }
                                            //LEFT SIDE CHECKER

                                            if(j + 1 < BOARD_WIDTH && j + 1 >=0){
                                            //checks to see if right side exists
                                                if(game.board[i][j+1].hasMine == true){
                                                    game.board[i][j].letter += 1;
                                                    checkagain = true;
                                                }
                                                //checks for mine prox to right
                                            }
                                            //RIGHT SIDE CHECKER    

                                            if (i+1 < BOARD_HEIGHT && i+1 >= 0){ 
                                            //if bottom row exists
                                                if(game.board[i+1][j].hasMine == true){
                                                    game.board[i][j].letter += 1;
                                                    checkagain = true;
                                                }
                                                //checks bottom middle for mine prox
                                                if(j-1 < BOARD_WIDTH && j-1 >=0){
                                                //if bottom row exists, see if bottom left exists
                                                    if( game.board[i+1][j-1].hasMine == true){
                                                        game.board[i][j].letter += 1;
                                                        checkagain = true;
                                                    }
                                                    //checks bottom left for mine prox
                                                }
                                                if(j + 1 < BOARD_WIDTH && j + 1 >=0){
                                                //if bottom row exists, see if bottom right exists
                                                    if(game.board[i+1][j+1].hasMine == true){
                                                        game.board[i][j].letter += 1;
                                                        checkagain = true;
                                                    }
                                                    //checks bottom right for mine prox
                                                }
                                            }
                                            //BOTTOM ROW CHECKER

                                            if(game.board[i][j].letter == '0'){
                                                x = j;
                                                y = i;
                                                if (y-1 < BOARD_HEIGHT && y - 1 >= 0){ 
                                                //if top row exists
                                                    if(game.board[y-1][x].letter == '?')
                                                        game.board[y-1][x].letter = '0';
                                                        //changes top middle to '0'
                                                    if(x-1 < BOARD_WIDTH && x-1>=0){
                                                   //if top row exists, see if top left exist
                                                        if(game.board[y-1][x-1].letter == '?')
                                                            game.board[y-1][x-1].letter = '0';
                                                            //changes top left to '0'
                                                    }
                                                    if(x+1 < BOARD_WIDTH){
                                                    //if top row exists, see if top right exist
                                                        if(game.board[y-1][x+1].letter == '?')
                                                            game.board[y-1][x+1].letter = '0';
                                                            //changes top right to '0'
                                                    }
                                                }
                                                //TOP ROW CHECKER
            
                                                if(x - 1 < BOARD_WIDTH && x - 1 >=0){
                                                //checks to see if left side exists
                                                    if(game.board[y][x-1].letter == '?')
                                                        game.board[y][x-1].letter = '0';
                                                }
                                                //LEFT SIDE CHECKER

                                                if(x + 1 < BOARD_WIDTH && x + 1 >=0){
                                                //checks to see if right side exists
                                                    if(game.board[y][x+1].letter == '?')
                                                        game.board[y][x+1].letter = '0';
                                                }
                                                //RIGHT SIDE CHECKER    

                                                if (y+1 < BOARD_HEIGHT && y+1 >= 0){ 
                                                //if bottom row exists
                                                    if(game.board[y+1][x].letter == '?')
                                                        game.board[y+1][x].letter = '0';
                                                        //changes bottom middle to '0'

                                                    if(x-1 < BOARD_WIDTH && x-1 >=0){
                                                    //if bottom row exists, see if bottom left exists
                                                        if(game.board[y+1][x-1].letter == '?')
                                                            game.board[y+1][x-1].letter = '0';
                                                            //changes bottom left to '0'
                                                    }
                                                    if(x+1 < BOARD_WIDTH && x+1 >=0){
                                                    //if bottom row exists, see if bottom right exists
                                                        if(game.board[y+1][x+1].letter == '?')
                                                            game.board[y+1][x+1].letter = '0';
                                                            //changes bottom right to '0'
                                                    }
                                                }
                                                //BOTTOM ROW CHECK
                                                //sets surrounding points to '0'

                                            }//if(board[i][j] == '0' */
                                        }//if =='0'
                                    }//for j
                                }//for i
                            }while(checkagain);
                            //continues loop until all blanks found and locations solved
                        }
                        end = hasPlayerWon(game);
                    }
                    //if dig site isn't on mine
                        break;

                    case 'f':
                    case 'F':
                    //to place flag

                        do{
                            questcheck = false;                
                            //resets ? check
                            cout << "Flag at X:";
                            cin >> xdig;
                            //prompts user for x dig site
                            while(xdig > BOARD_WIDTH || xdig <= 0){
                                cout << "Error with X value, please try again" << endl;
                                cin.clear();
                                cin.ignore(80,'\n');
                                cout << "Dig at X: ";
                                cin >> xdig;
                            }
                            //checks that x is in bounds, loops again if not

                            cout << "Flag at Y:";
                            cin >> ydig;
                            //prompts user for y dig site
                            while(ydig > BOARD_HEIGHT || ydig <= 0){
                                cout << "Error with Y value, please try again" << endl;
                                cin.clear();
                                cin.ignore(80,'\n');
                                cout << "Dig at Y:";
                                cin >> ydig;
                            }
                            //checks that y is in bounds, loops again if not
             
                            ydig--;
                            xdig--;
                            //decrements user input to match array indexes

                            if(game.board[ydig][xdig].letter != '?' && game.board[ydig][xdig].letter != 'P'){
                                questcheck = true;
                                cout << "Can't dig at a site that has already been dug!" 
                                     << endl;
                            //cant dig at non ? squares makes user re-select
                            }
                            else if(game.board[ydig][xdig].letter == 'P'){
                                game.board[ydig][xdig].letter = '?';
                            }
                            else{
                                game.board[ydig][xdig].letter = 'P';   
                            }
                        }while(questcheck); 
                        //loops if user can't place flag at specified site
                        break;            

                    case 'q':
                    case 'Q':
                        cout << "Quitting..." << endl;
                        return 0;

                    default:
                        cout << "Error - Please try again" << endl;
                        break;
                }
        }while(end == false);
    
    displayBoard(game);
    //calls board to display final time
    cout << "You won in " << game.moves << " moves!" << endl;
    //congratulates user for win, contines to program exit
    return 0;
}

void displayBoard(minesweeper game){

        cout << "    1   2   3   4   5   6   7   8   9  10  11  12";
        //displays column numbers   
 
        for(int i = 0; i < BOARD_HEIGHT; i++){ 
            cout << endl << "  +---+---+---+---+---+---+---+---+---+---+---+---+"
            << endl << i+1 << " |";
            for(int j = 0; j < BOARD_WIDTH; j++){
                if (game.board[i][j].letter == '0'){
                    cout << "   |";
                }
                else{
                    cout << " " << game.board[i][j].letter << " |";      
                }
            }
        }
        //displays middle section of game
        cout << endl
        << "  +---+---+---+---+---+---+---+---+---+---+---+---+" << endl
        << endl;
        //displays bottom row of game

}

void displayMines(minesweeper game){

    cout << "    1   2   3   4   5   6   7   8   9  10  11  12";
    //displays column numbers   
 
    for(int i = 0; i < BOARD_HEIGHT; i++){ 
        cout << endl << "  +---+---+---+---+---+---+---+---+---+---+---+---+"
        << endl << i+1 << " |";
        for(int j = 0; j < BOARD_WIDTH; j++){
            if(game.board[i][j].hasMine == true){
                cout << " * |";
                //displays marker if mine
            }
            else{
                cout << "   |";
                //displays as blank if no mine
            }
        }
    }
    //displays middle section of game
    cout << endl
    << "  +---+---+---+---+---+---+---+---+---+---+---+---+" << endl
    << endl << "You hit a mine! Game over." << endl;
    //displays bottom row of game

}


bool hasPlayerWon(minesweeper game){

    int questCount = 0;
    int flags = 0;
    //initializes counter for '?'

    for (int i = 0; i < BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            if(game.board[i][j].letter == '?'){
                questCount++;   
            }
        }
    }
    //'?' counter

    for (int i = 0; i < BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            if(game.board[i][j].letter == 'P'){
                flags++;   
            }
        }
    }
    // 'P' counter

    //counts for all '?'

    if(questCount + flags <= game.mineCount){
        return true;
        //if there is only the mines left, player has won
    }
    return false;
    //if there is more spaces left to go, return false to continue game
}
