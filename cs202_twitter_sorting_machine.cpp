#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/*  Finnick Lakeotes, 5004855838, Assignment 5
    To take in a file of tweet data, sort it, then process dynamically
    Input: tweet file
    Output: Sorted tweet data ready to be searched

    Used NASA Tweets

    struct Tweet: struct for tweet data
    constructors: tweet's source, text, creation date, retweet count,
    public functions: all
    static members: all as vector use is static
*/

struct Tweet{
    string fileName;
    int SIZE = 0;
    string ** tweetArr;
    ~Tweet();
};

void setSource(Tweet&);
string getSource(string);
void readTweets(string, Tweet&);
int countTweets(const Tweet&, const string);
int countRetweets(const Tweet&, const string);
void phrasePrinter(const Tweet&, const string);
void fprintAllTweets(const Tweet&);
void sortNprintByFavorite(Tweet&);
bool strFind(const string, const string);

/*
    setSource: changes all non-standard sources in tweets
    parameters: struct obj
    return value: none
*/
void setSource(Tweet &t){

    for(int q = 0; q < t.SIZE; q++){
    //cycles through all tweets
        //condense for easier use
        if(t.tweetArr[q][1] == "Twitter for iPhone")
           continue;
        else if(t.tweetArr[q][1] == "Twitter for Android")
            continue;
        else if(t.tweetArr[q][1] == "Twitter Web Client")
            continue;
        else if(t.tweetArr[q][1] == "Instagram")
            continue;
        else if(t.tweetArr[q][1] == "Twitter for BlackBerry")
            continue;
        else if(t.tweetArr[q][1] == "Facebook")
            continue;
        //if source is already standard, dont change
        else
            t.tweetArr[q][1] = "Other";    
        //if non-standard, like a link, change to other
    }

}


/*
    getSource: returns string (prof said to leave in even if not used?)
    parameters: source string
    return value: string of source
*/
string getSource(string sourceStr){
    
    return sourceStr;
}

/*
    countTweets: counts total of tweets w/ searched phrase
    parameters: struct obj and searched phrase string
    return value: int of # of contained tweets
*/
int countTweets(const Tweet &t, const string phrase){

    int amount = 0;

    for(int j = 1; j < t.SIZE; j++){
        if( strFind(t.tweetArr[j][2], phrase) ){
            amount++;
        }
    }
    //loops through all tweets, if true/found will increment one

    return amount;
}


/*
    readTweets: processes tweet data into vector
    parameters: struct obj
    return value: none
*/
void readTweets(Tweet &t){

    string input = "";
    string tempString = "";
    int hold = 0;
    int look = 0;
    ifstream iFile;
    
    iFile.open(t.fileName);
     if(iFile.is_open() == false){
        cout << "Error - Invalid file name" << endl;
        exit(0);
        //if file name
    }
    //checks and opens input file  
    else{
        do{
            getline(iFile, input);
            if(iFile.eof() == false){
            //counts how many lines in input
                t.SIZE++;
            }
        }while(iFile.eof() == false);
    }
    iFile.close();    

    t.tweetArr = new string*;
    t.tweetArr = new string*[t.SIZE];
  
    for(int i = 0; i < t.SIZE; i++){
        t.tweetArr[i] = new string[8];
        //[0] is the num, rest is string pieces 
    } 
    //declares tweetsArr

    for(int i = 0; i < t.SIZE; i++){
        t.tweetArr[i][0] = to_string(i);
    }
    //fills array with tweet nums
    
    t.SIZE = 0;
    //resets input num


    iFile.open(t.fileName);
    do{
        getline(iFile, input);
        if(iFile.eof() == false){ 
            look = input.find(",");
            t.tweetArr[t.SIZE][1] = input.substr(0, look);
            //looks for first comma, assigns everything behind as source
                
            hold = look;
            hold++;
            look = input.find(",", hold);
            tempString = input.substr(hold, look-hold);
            if(tempString == "text")
                tempString = "None";
            t.tweetArr[t.SIZE][2] = tempString;
            //looks for and assigns tweet text

            hold = look;
            hold++;
            look = input.find(",", hold);
            t.tweetArr[t.SIZE][3] = input.substr(hold, look-hold);
            //looks for and assigns creation date

            hold = look;
            hold++;
            look = input.find(",", hold);
            tempString = input.substr(hold, look-hold); 
            if( tempString == "retweet_count")
                tempString = "0";
            t.tweetArr[t.SIZE][4] = tempString;
            //looks for and assigns retweet count

            hold = look;
            hold++;
            look = input.find(",", hold);
            tempString = input.substr(hold, look-hold);
            if( tempString == "favorite_count")
                tempString = "0";
            t.tweetArr[t.SIZE][5] = tempString;
            //looks for and assigns favorite count

            hold = look;
            hold++;
            look = input.find(",", hold);
            tempString = input.substr(hold, look-hold);
            t.tweetArr[t.SIZE][6] = tempString;
            //looks for and assigns if its a retweet
        
            hold = look;
            hold++;
            t.tweetArr[t.SIZE][7] = input.substr(hold);
            //looks for and assigns tweet id

            t.SIZE++;
            //increments at each tweet entry
        }
    }while(iFile.eof() == false);//end do while when file is empty

    cout << t.SIZE << " tweets read from " << t.fileName << endl;
    //outputs how many tweets were read in from file
 
}//end of function call


/*
    countRetweets: searches for phrase and if true, adds to a total of rts
    parameters: struct obj and searched phrase
    return value: int of total retweets
*/
int countRetweets(Tweet &t, const string uPhrase){

    unsigned int totalRetweets = 0;   

    for(int j = 1; j < t.SIZE; j++){
        if( strFind(t.tweetArr[j][2], uPhrase) ){
            totalRetweets += stoi(t.tweetArr[j][4]);
        }
    }
    //checks for every tweet to contain phrase, if true adds retweets

    return totalRetweets;
    //sends retweet counts

}


/*
    phrasePrinter: prints out a tweet in a nicer format
    parameters: struct obj and searched phrase
    return value: none
*/
void phrasePrinter(const Tweet &t, const string enterPhrase){

    for(int q = 1; q < t.SIZE; q++){
    //cycles through all tweets
        if( strFind(t.tweetArr[q][2], enterPhrase) ){
        //if phrase is found, will print tweet

            cout << "Tweet source: " << t.tweetArr[q][1] << endl
            << "Text: " << t.tweetArr[q][2] << endl 
            << "Created at: " << t.tweetArr[q][3] << endl
            << "Retweet count: " << t.tweetArr[q][4] << endl 
            << "Favorite count: " << t.tweetArr[q][5] << endl; 
         
            if (t.tweetArr[q][6] == "true")
                cout << "Is a retweet" << endl;
            else
                cout << "Not a retweet" << endl;

            cout << "ID STR: " << t.tweetArr[q][7] << endl;
            //prints out tweet data in nice format
        }
    }
}

/*
    fprintAllTweets: prints all tweets to file
    parameters: struct obj
    return value: none
*/
void fprintAllTweets(Tweet &t){

    string enteredPhrase = ""; 
    cout << "Enter name of file to save all tweets to:";
    cin >> enteredPhrase;

    ofstream outFile;
    outFile.open(enteredPhrase);
    //opens output file to write to

    for(int q = 0; q < t.SIZE; q++){
    //cycles through all tweets
        if( strFind(t.tweetArr[q][2], enteredPhrase) ){
        //if phrase is found, will print tweet

            outFile << "Tweet source: " << t.tweetArr[q][1] << endl
            << "Text: " << t.tweetArr[q][2] << endl 
            << "Created at: " << t.tweetArr[q][3] << endl
            << "Retweet count: " << t.tweetArr[q][4] << endl 
            << "Favorite count: " << t.tweetArr[q][5] << endl; 
         
            if (t.tweetArr[q][6] == "true")
                outFile << "Is a retweet" << endl;
            else
                outFile << "Not a retweet" << endl;

            outFile << "ID STR: " << t.tweetArr[q][7] << endl;
            //tweet data organized in nicer format
        }
    }

    outFile.close();
    //closes writing to file
}

/*
    sortNprintByFavorite:finds top 10 favorites and least fav and prints
    parameters: struct obj
    return value: none
*/
void sortNprintByFavorite(Tweet &t){

    string t_indice = "";   //0
    string t_source = "";   //1
    string t_text = "";     //2
    string t_created_at = ""; //3
    string t_retweet_count = ""; //4
    string t_favorite_count = ""; //5
    string t_is_retweet = "false"; //6
    string t_id_str = ""; //7
    //hold variables
    int i = 0;
    //selection sort var

    for(int q = 0; q < t.SIZE-1; q++){
        i = q;
        for(int j = q+1; j < t.SIZE; j++){    
            if(stoi(t.tweetArr[j][5]) > stoi(t.tweetArr[i][5])){
                i = j;
            }
            t_source = t.tweetArr[i][1];
            t_text = t.tweetArr[i][2];
            t_created_at = t.tweetArr[i][3];
            t_retweet_count = t.tweetArr[i][4];
            t_favorite_count = t.tweetArr[i][5];
            t_is_retweet = t.tweetArr[i][6];
            t_id_str = t.tweetArr[i][7];    
            //transfers to hold variables
            t.tweetArr[i][1] = t.tweetArr[q][1];
            t.tweetArr[i][2] = t.tweetArr[q][2];
            t.tweetArr[i][3] = t.tweetArr[q][3];
            t.tweetArr[i][4] = t.tweetArr[q][4];
            t.tweetArr[i][5] = t.tweetArr[q][5];
            t.tweetArr[i][6] = t.tweetArr[q][6];
            t.tweetArr[i][7] = t.tweetArr[q][7];
            //performs swap 
            t.tweetArr[q][1] = t_source;
            t.tweetArr[q][2] = t_text;
            t.tweetArr[q][3] = t_created_at;
            t.tweetArr[q][4] = t_retweet_count;
            t.tweetArr[q][5] = t_favorite_count;
            t.tweetArr[q][6] = t_is_retweet;
            t.tweetArr[q][7] = t_id_str;    
            //assigns back
        }
    }
    //goes through all data, sorting by most favorites first

    for(int j = 1; j < 10; j++){
    //cycles through top 10
       cout << "Tweet source: " << t.tweetArr[j][1] << endl
            << "Text: " << t.tweetArr[j][2] << endl 
            << "Created at: " << t.tweetArr[j][3] << endl
            << "Retweet count: " << t.tweetArr[j][4] << endl 
            << "Favorite count: " << t.tweetArr[j][5] << endl; 
         
        if (t.tweetArr[j][6] == "true")
            cout << "Is a retweet" << endl;
        else
            cout << "Not a retweet" << endl;

        cout << "ID STR: " << t.tweetArr[j][7] << endl;
        //prints out tweet data in nice format    
    }

    cout << endl << "Least Favorited Tweet:" << endl << endl
         << "Tweet source: " << t.tweetArr[t.SIZE - 1][1] << endl
         << "Text: " << t.tweetArr[t.SIZE - 1][2] << endl 
         << "Created at: " << t.tweetArr[t.SIZE - 1][3] << endl
         << "Retweet count: " << t.tweetArr[t.SIZE - 1][4] << endl 
         << "Favorite count: " << t.tweetArr[t.SIZE - 1][5] << endl; 
     
    if (t.tweetArr[t.SIZE - 1][6] == "true")
        cout << "Is a retweet" << endl;
    else
        cout << "Not a retweet" << endl;

    cout << "ID STR: " << t.tweetArr[t.SIZE - 1][7] << endl 
         << endl << endl;
    //prints least fav tweet(last in array)
}

/*
    strFind: to see if a tweet contains a phrase
    parameters: tweet and searched phrase
    return value: bool for if found
*/
bool strFind(const string tweetStr, const string userStr){

    int letters = 0;
    int m = 0;   
    
    //if(userStr.length() <= tweetStr.length()){
    //will throw out if string is longer than tweet
        for (int j = 0; j < tweetStr.length()-userStr.length(); j++){
        //runs through tweet-string to prevent seg fault 
           if(tweetStr[j] == userStr[0]){  
                m = j;
                //creates new var to push through string w/o changing loop

                for (int k = 1; k < userStr.length(); k++){
                    m++;
                    //push through loop 
                    if(tweetStr[m] == userStr[k]){
                        letters++;      
                        //if letter match increment           
                    }
                    else{
                        letters = 0;
                        break;
                   }
                }
                if (letters == (userStr.length()-1)){
                //if all letters matched, then word is found
                    return true;
                }
            }
        }
    //}
    
    return false;
    //if not found, returns false
}

/*
    ~Tweet: Destructor
    parameters: none
    output: none
*/
Tweet::~Tweet(){

    for(int i = 0; i < SIZE; i++){
        delete [] tweetArr[i];
    } 
    delete [] tweetArr;

}

/*
    main: calls functions and prompts user for inputs
    parameters: argc and argv for file read
    return value: none
*/
int main(int argc, char *argv[]){

    string userEntry = "";
    Tweet a;

        a.fileName = argv[1];
        cout << a.fileName << endl;
        readTweets(a);
        //processes tweet data
        cout << "Enter a phrase to count how many tweets contain it: ";
        getline(cin, userEntry);
        //tells user about how many tweets processed and prompts for search

        cout << userEntry << " found in " << countTweets(a, userEntry) 
             << " tweets! :o" << endl << "Enter phrase to add all retweets "
             << "of a tweet that contains the given phrase: ";
        
        getline(cin, userEntry);
        //tells user about searched phrase and promps for another

        cout << "There were " << countRetweets(a, userEntry) 
             << " retweets of tweets containing the term '" << userEntry
             << "'!" << endl;
        //tells user about # of retweets containing searched phrase

        cout << "Enter a phrase to search for and print all tweets that"
             << " contain it:";
        cin >> userEntry;
        cout << endl << "Tweets with term '" << userEntry << "':" 
             << endl << endl;
        
        setSource(a);           
        //changes sources of non-standards
        phrasePrinter(a, userEntry);
        //asks user for phrase to print tweets containing
        
        fprintAllTweets(a);             
        //writes to file all tweets in new format    
      
        cout << endl << "Top 10 Favorited Tweets:" << endl << endl;
        sortNprintByFavorite(a);
        //calls top 10/bottom 1

        cout << "Total Tweets Read: " << a.SIZE << endl
             << endl << "Thanks for Playing!" << endl;
        //ending message
}
