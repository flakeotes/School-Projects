#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

/*  Finnick Lakeotes, 5004855838, CS135-1004, Assignment 9
    To Replicate a bowling game scorecard
    Input: User input or input file
    Output: Accurate display of Bowling Score card

    Algorithm:  1. Display Menu
                2. Select from menu, if read from a file, display successful read
                message before processing
                3. inputs number, checks to see if strike, if not continues to
                second number. Turns on both bonus checks
                4. Inputs second number for round total. If both =10 then spare.
                If spare turns on one bonus check.
                5. Repeats 3 & 4 until no more data, if eof reached before a[20],
                then "game in progress" message shows. 
                6. Asks to save game to file, if no returns to beginning of main
                7. If yes, asks for output file name and writes pin data to file.
                After returns to main menu.
                
    cout << "________________________________________________________________" << endl
         << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |   10   |" << endl
         << "| X| X| X| X| X| X| X| X| X| X| X| X| X| X| X| X| X| X| X| X| X|" << endl
         << "|  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |    X   |" << endl
         << "''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''" << endl;
*/

void generateScoreText(int[], int, string&);
//generates scorecard if desired
bool readPlayerRolls(int[], int&, string filename);
//opens file and runs game
void getPlayerRolls(int[], int&);
//user inputs rolls

int main(){
ifstream inFile;
string filename = " ";
char selection = ' ';
int var = 0;
//initializes variables

do{
    selection = ' ';
    int bowls[21] = {0};
    //sets array
       
    cout << "**********************************" << endl
         << " Welcome to Bedrock Bowling Alley " << endl
         << "**********************************" << endl
         << "Menu Options" << endl
         << "R/r Read roll data from file" << endl
         << "M/m Manually enter data" << endl
         << "Q/q quit " << endl
         << "Selection: ";
    //displays menu at start
    
    cin >> selection;
    //user inputs choice
         
    switch(selection){
        
        case 'q':
        case 'Q':
            cout << "Exiting. . ." << endl;
            return 0;
            break;
            //leaves program
        case 'm':
        case 'M':
            getPlayerRolls(bowls, var);
            break;
            //user can input their own variables
        case 'r':
        case 'R':
            readPlayerRolls(bowls, var, filename);
            break;
            //user can use file for rolls
        default:
            cout << "Error - Please try again" << endl;
            break;
            //resets menu if other input detected
    }
}while(selection != 'q');
inFile.close();
}

void generateScoreText(int a[], int numofrolls, string &outiefile){
//to score the game for output file
//write as output, then change to file output
    int rnd10 = 0;
    int frames = 1; 
    int score = 0;
    double frame = 1;
    bool fail = false;
    ofstream oFile;
    //initializes variables

    do{

        if(fail == true){
            cout << "Enter output file name: ";
            cin >> outiefile;
            fail = false;
        }        
        //allows user to rename output file if first try failed

        oFile.open(outiefile);
        //tries to open file

        if (oFile.is_open() == false){
            cout <<"Error - Please try inputting file name again" << endl;
            oFile.clear();
            fail = true;
        }   
    }while(!oFile.is_open());
    //opens output file to write

    for(int i = 0; i < 21; i++){
        if(a[i] > 10 && a[i] < 0){
            a[i] = 0;
        }
    }
    //checks for any strange numbers


    oFile << "________________________________________________________________" << endl
         << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |   10   |" << endl
         << "|";
        //displays first part of menu

        for (int i = 0; i < numofrolls; i++){
            if (a[i] == 10){
                if( frame < 10){
                    oFile << " X|  |";
                    frame++;
                    //prints out strike
                }    
                else{
                    oFile << " X|";
                    frame++;
                    //prints out strike for 10th round
                }
            }
            else{
                
                oFile << setw(2) << a[i] << "|";
                //writes out non spare/strike roll
                frame += 0.5;
                if(a[i] + a[i+1] == 10 && a[i] !=0){
                    oFile << " /|";
                    frame++;
                    //prints out spare
                    i++;
                }
            }
        }
        oFile << endl << "|";
        // prints out middle of menu, start of score row


    //MENU SCORE BOTTOM ROW
    for(int i = 0; i < numofrolls && frames < 10; i++){
    //processes rolls frames 1-9        
        if(a[i] == 10){ //if a strike is rolled
            if (numofrolls - i > 2){
                score += a[i] + a[i+1] + a[i+2];
            }
            //if there are rolls ahead of the strike
            else if (numofrolls - i > 1){
                score += a[i] + a[i+1];
            }
            //if there is just one roll ahead
            else if (numofrolls - i == 0){
                score += a[i];
            }
            //if the strike is the final roll
            oFile << setw(5) << score << "|";
            //to display score
        }

        else{
            
            if(numofrolls - i <= 1){
                score += a[i];
                oFile << setw(5) << score << "|";
                //displays score
            }           
            //if there is no rolls ahead
 
            if (a[i] + a[i+1] == 10){
            // if a spare is rolled
                if (numofrolls - i > 1){
                    score += 10 + a[i+2];
                }
                // calculates score if rolls ahead
                else if (numofrolls - i >= 0){
                    score += 10;
                }
                //calculates score if no rolls ahead
                oFile << setw(5) << score << "|";
                //writes to file score
                i++;
                //increments roll count
            }
            else if (i + 1 < numofrolls){
            // if not spare or strike
                if(a[i+1] < numofrolls){
                // writes score
                    score += a[i] + a[i+1];
                }
                i++;
                //increments roll

                oFile << setw(5) << score << "|";
                //writes score
            }
            
        }
        rnd10 = i;
        //sets hold variable for frame 10 to i
        frames++;
        //increments frame count
    }

    if (frames >= 9 ){ 
        rnd10++;        
        //increments roll count to current roll

        if(a[rnd10] == 10){ //if strike
            if (numofrolls - 3 == rnd10){
                score += 10 + a[rnd10 + 1] + a[rnd10 + 2];
                //bonus points if game is complete/turkey
            }
            else if (numofrolls - 2 == rnd10){
                score += 10 + a[rnd10 + 1];
                //bonus points if one roll ahead
            }
            else if(numofrolls - 1 == rnd10){
                score += 10;
                //score if no rolls ahead
            }
        }
        //STRIKE
    
        if (numofrolls - 1 > rnd10){ 
            if(a[rnd10 + 1] == 10){
                //cout << "-Roll #2 Strike" << endl;
                //score += 10 + a[rnd10 + 2];
            }
        //STRIKE
            else{
                if(a[rnd10] + a[rnd10 + 1] == 10){
                  //  cout << "-Roll #2 Spare" << endl;
                    score += 10 + a[rnd10 + 2];
                }
        //SPARE
                else{
                    //cout << "-Roll #2 " << a[rnd10 + 1] << endl;
                    score += a[rnd10] + a[rnd10 + 1];
                }

            }
       //ROLL #2
            if(a[rnd10] == 10 || a[rnd10] + a[rnd10 + 1] == 10){       
                if(a[rnd10 + 2] == 10){
                    //cout << "-Roll #3 Strike" << endl;
                    //score += a[rnd10 + 2];
                }
                else{
                    if(a[rnd10 + 1] + a[rnd10 + 2] == 10){
                      //  cout << "-Roll #3 Spare" << endl;
                        score += a[rnd10 + 2];
                    }
                    else{
                        //cout << "-Roll #3 " << a[rnd10 + 2] << endl;
                        score += a[rnd10 + 2];
                    }
                }
            }
            oFile << setw(8) << score << "|" << endl;    
      //ROLL #3    
        }
    }

    oFile << "''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''" << endl;
    //writes bottom line of score box
    oFile.close();
    //closes output file
}

bool readPlayerRolls(int a[], int &roll, string filename){ ///////////
//when user wants a file to input rolls
    ifstream inFile;
    int numofrolls = 0;
    int score = 0; 
    int frames = 1;
    int rnd10 = 0;
    char saveans = ' ';
    string outFileName = " ";
    //initializes variables

    cout << "Enter filename to read: ";
    cin >> filename;
    //prompts user for filename   

    inFile.open(filename);
    //opens input file

    if(inFile.is_open() == false){
         cout << "Error finding file, please try again" << endl;
         inFile.close();
         return false;
    }
    //executes if filename cant be found    

    do{
        if(inFile.eof() == false){
            inFile >> roll;
            //inputs data to variable
            a[numofrolls] = roll;
            //puts variable into array
            numofrolls++;
            //increments counter for how many inputs
        }
    }while(inFile.eof() == false);
    //loop finishes when eof is reached

    numofrolls--;
    //decrements because of null write in array

    cout << "Successfully read file \"" << filename << "\" "
         << "Roll Count: " << numofrolls << endl << endl;
    //displays successful open and roll count    


    for(int i = 0; i < numofrolls && frames < 10; i++){
    //rolls for frames 1-9        
        cout << "Frame #" << frames << endl;
        //displays current frame

        if(a[i] == 10){
            cout << "-Roll #1 Strike" << endl;
            if (numofrolls - i > 2){
                score += a[i] + a[i+1] + a[i+2];
            }
            else if (numofrolls - i > 1){
                score += a[i] + a[i+1];
            }
            else if (numofrolls - i == 0){
                score += a[i];
            }
            cout << "-Score " << score << endl << endl;
        }
        //if a strike is rolled

        else{
            
            cout << "-Roll #1 " << a[i] << endl;
            if(numofrolls - i <= 1){
                score += a[i];
                cout << "-Score " << score << endl << endl;
            }           
            //if roll isnt strike/spare
 
            if (a[i] + a[i+1] == 10){
                cout << "-Roll #2 Spare" << endl;
                if (numofrolls - i > 1){
                    score += 10 + a[i+2];
                }
                else if (numofrolls - i >= 0){
                    score += 10;
                }
                cout << "-Score " << score << endl << endl;
                i++;
                //if roll is spare
            }
            else if (i + 1 < numofrolls){
                cout << "-Roll #2 " << a[i+1] << endl;
                if(a[i+1] < numofrolls){
                    score += a[i] + a[i+1];
                }
                //if roll is spare
                i++;

                cout << "-Score " << score << endl << endl;
            }
            
        }
        rnd10 = i;
        //writes i to hold variable for frame 10
        frames++;
        //increments frame count
    }
    if(frames < 10){
        cout << "-Game in Progress-" << endl;
    }
    //displays that game is not complete


    if (frames >= 9 ){ 
        cout << "Frame #10" << endl;
        rnd10++;        
        //increments roll count to current roll

    //cout << rnd10 << "rnd10   numofrolls=" << numofrolls << endl; //DEBUG

        if(a[rnd10] == 10){
            cout << "-Roll #1 Strike" << endl;
            if (numofrolls - 3 == rnd10){
                score += 10 + a[rnd10 + 1] + a[rnd10 + 2];
                //if game is complete, turkey
            }
            else if (numofrolls - 2 == rnd10){
                score += 10 + a[rnd10 + 1];
                //if two bonus rolls only
            }
            else if(numofrolls - 1 == rnd10){
                score += 10;
                //score for incomplete game
            }
        }
        //STRIKE
        else{
            cout << "-Roll #1 " << a[rnd10] << endl;
        }
        //ROLL #1
    
        if (numofrolls - 1 > rnd10){ /////////////////////////////
            if(a[rnd10 + 1] == 10){
                cout << "-Roll #2 Strike" << endl;
                //score += 10 + a[rnd10 + 2];
            }
        //STRIKE
            else{
                if(a[rnd10] + a[rnd10 + 1] == 10){
                    cout << "-Roll #2 Spare" << endl;
                    score += 10 + a[rnd10 + 2];
                }
        //SPARE
                else{
                    cout << "-Roll #2 " << a[rnd10 + 1] << endl;
                    score += a[rnd10] + a[rnd10 + 1];
                }

            }
       //ROLL #2
            if(a[rnd10] == 10 || a[rnd10] + a[rnd10 + 1] == 10){       
                if(a[rnd10 + 2] == 10){
                    cout << "-Roll #3 Strike" << endl;
                    //score += a[rnd10 + 2];
                }
                else{
                    if(a[rnd10 + 1] + a[rnd10 + 2] == 10){
                        cout << "-Roll #3 Spare" << endl;
                        score += a[rnd10 + 2];
                    }
                    else{
                        cout << "-Roll #3 " << a[rnd10 + 2] << endl;
                        score += a[rnd10 + 2];
                    }
                }
            }
            cout << "-Score " << score << endl << endl;    
      //ROLL #3    
        }
        else{
            cout << "-Score " << score << endl << endl;
            cout << "-Game in Progress-" << endl;
        }

    }
    //special code to execute for 10th frame


    cout << "Save game to file (y/n)? ";
    cin >> saveans;
    //asks if user wants to write their scores to an output file

    switch(saveans){

        case 'y':
        case 'Y':
            cout << "Filename: ";
            cin >> outFileName;
            generateScoreText(a, numofrolls, outFileName);
            //calls output file function
            break;
        case 'n':
        case 'N':
        default:
            cout << endl << endl;
            //leaves if not
            break;
    }


    inFile.close();
    //closes input file
    return true;
}

void getPlayerRolls(int a[], int&){ //////////////////////////////////
//when the user wants to manually input rolls
    int frames = 1;
    int score = 0;
    int input = 0;
    int rnd10 = 0;
    int numofrolls = 0;
    char saveans = ' ';
    string outFileName = " ";
    //initializes variables

    for (int i = 0; i < 21 && frames < 11; i++){
        cout << endl << "Frame #" << frames << endl;
        cout << "Roll #1 ";
        cin >> input;
        
        if (input == -1){
            break;
        }    
        
        a[i] = input;
        numofrolls++;
        //assigns input
        
        if (a[i] == 10 && frames < 10){
            frames ++;
            continue;
        }
        //checks for strikes
        else{
            cout << "Roll #2 ";
            cin >> input;

            if (input == -1){
                break;
            }

            a[i+1] = input;
            i++;
            frames++;
            numofrolls++;
            //changes frame count

            if(frames == 11){ 
                if(a[i] == 10 || a[i] + a[i+1] == 10){
                    cout << "Roll #3 ";
                    cin >> input;
                    if(input == -1){
                        break;
                    }
                    a[i+1] = input;
                    numofrolls++;
                }
            }
            //Bonus roll for frame 10
        }
    }
    //inputs data by user

    cout << endl;
    frames = 1;
    //resets frames
    //START OF ROLLS
    for(int i = 0; i < numofrolls && frames < 10; i++){
        
        cout << "Frame #" << frames << endl;
        //displays current frame

        if(a[i] == 10){
            cout << "-Roll #1 Strike" << endl;
            if (numofrolls - i > 2){
                score += a[i] + a[i+1] + a[i+2];
            }
            else if (numofrolls - i > 1){
                score += a[i] + a[i+1];
            }
            else if (numofrolls - i == 0){
                score += a[i];
            }
            cout << "-Score " << score << endl << endl;
        }
        //if a strike is rolled

        else{
            
            cout << "-Roll #1 " << a[i] << endl;
            if(numofrolls - i <= 1){
                score += a[i];
                cout << "-Score " << score << endl << endl;
            }           

 
            if (a[i] + a[i+1] == 10){
                cout << "-Roll #2 Spare" << endl;
                if (numofrolls - i > 1){
                    score += 10 + a[i+2];
                    //spare scoring 
                }
                else if (numofrolls - i >= 0){
                    score += 10;
                    //spare scoring if no roll ahead
                }
                cout << "-Score " << score << endl << endl;
                i++;
                //displays score at end of frame
            }
            else if (i + 1 < numofrolls){
                cout << "-Roll #2 " << a[i+1] << endl;
                if(a[i+1] < numofrolls){
                    score += a[i] + a[i+1];
                }
                i++;

                cout << "-Score " << score << endl << endl;
                //displays score at end of frame
            }
            
        }
        rnd10 = i;
        frames++;
        //increments frame count
    }
    if(frames < 10){
        cout << "-Game in Progress-" << endl;
    }
    //displays that game is not complete


    if (frames >= 9 ){ 
        cout << "Frame #10" << endl;
        rnd10++;        
        //increments roll count to current roll

   // cout << rnd10 << "rnd10   numofrolls=" << numofrolls << endl; //DEBUG

        if(a[rnd10] == 10){
            cout << "-Roll #1 Strike" << endl;
            if (numofrolls - 3 == rnd10){
                score += 10 + a[rnd10 + 1] + a[rnd10 + 2];
            }
            else if (numofrolls - 2 == rnd10){
                score += 10 + a[rnd10 + 1];
            }
            else if(numofrolls - 1 == rnd10){
                score += 10;
            }
        }
        //STRIKE
        else{
            cout << "-Roll #1 " << a[rnd10] << endl;
        }
        //ROLL #1
    
        if (numofrolls - 1 > rnd10){ /////////////////////////////
            if(a[rnd10 + 1] == 10){
                cout << "-Roll #2 Strike" << endl;
                //score += 10 + a[rnd10 + 2];
            }
        //STRIKE
            else{
                if(a[rnd10] + a[rnd10 + 1] == 10){
                    cout << "-Roll #2 Spare" << endl;
                    score += 10 + a[rnd10 + 2];
                }
        //SPARE
                else{
                    cout << "-Roll #2 " << a[rnd10 + 1] << endl;
                    score += a[rnd10] + a[rnd10 + 1];
                }

            }
       //ROLL #2
            if(a[rnd10] == 10 || a[rnd10] + a[rnd10 + 1] == 10){       
                if(a[rnd10 + 2] == 10){
                    cout << "-Roll #3 Strike" << endl;
                    //score += a[rnd10 + 2];
                }
                else{
                    if(a[rnd10 + 1] + a[rnd10 + 2] == 10){
                        cout << "-Roll #3 Spare" << endl;
                        score += a[rnd10 + 2];
                    }
                    else{
                        cout << "-Roll #3 " << a[rnd10 + 2] << endl;
                        score += a[rnd10 + 2];
                    }
                }
            }
            cout << "-Score " << score << endl << endl;    
      //ROLL #3    
        }
        else{
            cout << "-Score " << score << endl << endl;
            cout << "-Game in Progress-" << endl;
        }

    }
    //special code to execute for 10th frame




    cout << "Save game to file (y/n)? ";
    cin >> saveans;
    //asks if user wants to save file

    switch(saveans){

        case 'y':
        case 'Y':
            cout << "Filename: " << outFileName;
            cin >> outFileName;
            generateScoreText(a, numofrolls, outFileName);
            //calls function for scorecard
            break;
        case 'n':
        case 'N':
        default:
            cout << endl << endl;
            break;
    }
}
