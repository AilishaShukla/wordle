#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "utils.h"
#include<sstream>

using namespace std;


bool contains(vector<int> numbers, int value){
    for(int i = 0; i < numbers.size(); i++){
        if(numbers[i] == value){
            return true;
        }
    }
    return false;
}

//Generates a random word
std::string GenerateRandomWord(){
    std::vector <std::string> words = {"apple", "banana", "cherry", "grape", "lemon"};
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

//Check the guess word
bool IsValidGuess(const std::string& guess){
    if(guess.length() != 5){
        cout << "Invalid guess. Please enter a valid 5-letter lowercase word." << endl;
        return false;

    }
    for(char c: guess){
        if(!isalpha(c) || !islower(c)){
            cout << "Invalid guess. Please enter a valid 5-letter lowercase word." << endl;
            return false;
        }
    }
    return true;
}

//Calculate the score
int calculateScore(const std::string& target, const std::string& guess){
    int score = 0;
    for (int i = 0; i < target.length(); i++){
        if(target[i] == guess[i]){
            score++;
        }
    }
    return score;   
}


// Main Menu
void greet(){
    cout << "============================" << endl;
    cout << "   WELCOME TO THE WORDLE   " << endl;
    cout << "============================" << endl;
    cout << endl;
    cout << endl;
    cout << "1. Play Wordle" << endl;
    cout << "2. How to Play" << endl;
    cout << "3. Statistics Summary" << endl;
    cout << "4. Reset Statistics" << endl;
    cout << "5. Exit" << endl;


}

//Display Instructions
void howToPlay(){
    cout << "============================" << endl;
    cout << "   HOW TO PLAY   " << endl;
    cout << "============================" << endl;
    cout << "   Guess the wordle in 6 tries   " << endl;
    cout << endl;
    cout << endl;
    cout << "How to Play:" << endl;
    cout << "- Each guess must be a valid 5 letter word." << endl;
    cout << "- The color of the tiles will change to show you how close your guess was to the word." << endl;
    cout << " ---  ---  ---  ---  ---  " << endl;
    cout << "\033[32m| W |\033[0m" << "| E || A || R || Y |" << endl;
    cout << " ---  ---  ---  ---  ---  " << endl;
    cout << "W is in the word and in the correct spot." << endl;
    cout << endl;
    cout << " ---  ---  ---  ---  ---  " << endl;
    cout << "| P |" << "\033[33m| r |\033[33m" << "| L || L || S |" << endl;
    cout << " ---  ---  ---  ---  ---  " << endl;
    cout << endl;
    cout << " ---  ---  ---  ---  ---  " << endl;
    cout << "| V || A |" << "| G |" << "\033[90m| U |\033[0m" << "| E |" << endl;
    cout << " ---  ---  ---  ---  ---  " << endl;
}



int statistics(){
    return 0;

}

void statisticsSummary(){        
    int number_of_lines = 0;
    int number_of_attempts = 0;
    int number_of_wins = 0;
    vector<string> allResults;
    std::ifstream infile("stats.txt");
    std::string line;

    while (std::getline(infile, line))
    {
        stringstream ss( line.c_str() );
        vector<string> result;

        while( ss.good() )
        {
            string substr;
            getline( ss, substr, ',' );
            result.push_back( substr );
        }
        number_of_attempts = number_of_attempts + stoi(result[1]);
        if (stoi(result[2]) == 0) {
            number_of_wins = number_of_wins + 1;
        }
        // put calculation for longest streak
        // put calculation for current streak
        // result.empty();
        allResults.push_back(result[0]);
        allResults.push_back(result[1]);
        allResults.push_back(result[2]);
        ++number_of_lines;
    }
    int avg_attempts = 0;
    int win_percent = 0;
    if (number_of_lines == 0){
        avg_attempts = 0;
        win_percent = 0;
    
    }
    else {
        avg_attempts = (number_of_attempts/number_of_lines);
        win_percent = (number_of_wins*100/number_of_lines);
    }



    cout << "============================" << endl;
    cout << "     STATISTICS SUMMARY     " << endl;
    cout << "============================" << endl;
    cout << "Times Played: " << number_of_lines << endl;
    cout << "Average Attempts: " << avg_attempts << endl;
    cout << "Win Percentage: " << win_percent << endl;
    cout << "Current Streak: " << endl;
    cout << "Longest Streak: " << endl;
    cout << endl;
    cout << endl;
    cout << "----------------------------" << endl;
    cout << "WORD     ATTEMPTS        WIN" << endl;
    cout << "----------------------------" << endl;
    
    int cnt = 0;
    if (number_of_lines > 0){
        for (int i=0; i <= (allResults.size()/3); i+=1) {
            if( cnt <= allResults.size()-1){
                string word = allResults[cnt];
                char att = allResults[cnt+1][0];
                string win = "WIN";
                if(allResults[cnt+2][0] == '1'){
                    win = "LOSS";
                }

                cout << word << "     " << att << "             " << win << endl;
                cnt = cnt + 3;
            }
            else{
                break;
            }
            }
    }
}


string checkAttempt(string solution, string attempt){

    string result = "";

    vector<int> greenPos;
    vector<int> yellowPos;

    for (int i = 0; i < attempt.length(); i++){
        if (attempt[i] == solution[i]){
            solution[i] = '-';
            // cout << green(attempt[i]) << " ";
            greenPos.push_back(i);
        }
    }

    for (int i = 0; i < attempt.length(); i++){
        int pos = contains(solution, attempt[i]);
        if (pos != -1){
            yellowPos.push_back(i);
        }
    }

    for (int i = 0; i < attempt.length(); i++){
        if (contains(greenPos, i)){
            result += green(attempt[i]);
        }
        else if (contains(yellowPos, i)){
            result += yellow(attempt[i]);
        }
        else{
            result += gray(attempt[i]);
        }
        if (i < attempt.length() - 1){
            result += " ";
        }
    }
    return result;
}

void writeResults(string solution, bool result, int attempt ){
    ofstream file;
    file.open("stats.txt", ios::app);
    if (file.is_open()){
        file << solution << "," << attempt << "," << result << endl;
        file.close();
    }
    else{
        cout << "Could not open file" << endl;
    }
}

void resetStatistics(){
    std::ofstream ofs;
    ofs.open("stats.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void playgame(){
    greet();
    int userChoice;
    cout << "Select an Option: ";
    cin >> userChoice;
    // cout << userChoice;

    if(userChoice == 2){
        howToPlay();
        cout << "Press hit the ENTER key to exit";
        cin.get();
        if (cin.get() == '\n') {
            playgame();
        }
        else {
            cout << "Please [Enter] to continue" << endl;
        }
    }

    else if(userChoice == 3){
        statisticsSummary();
        cout << "Please [Enter] to continue" << endl;
        cin.get();
        if (cin.get() == '\n') {
            playgame();
        }
        else {
            cout << "Please [Enter] to continue" << endl;
        }
    } 
    
    else if (userChoice == 4){
        resetStatistics();
    }
    
    else if(userChoice == 1){
         int out = userChoice;

    string solution = "slate";
    string originalSolution = solution;

    int c = 0;
    bool won = false;
    while (c <= 5){
        string attempt;
        cin >> attempt;

        
        if(IsValidGuess(attempt)){
            cout << checkAttempt(solution, attempt) << endl;
            if (attempt == solution){
                won = true;
                cout << "You win...." << endl;
                writeResults(solution, 1, c+1);
                break;
            }
            c++;
            cout << "Attempt: " << c << endl;
            }

    }


    if (!won){
        writeResults(solution, 0, 6);
        cout << "Sorry, better luck next time" << endl;
        cout << "The correct answer is: " << solution << endl;

    }
  
   }

}





int main(){
    playgame();
}


    





