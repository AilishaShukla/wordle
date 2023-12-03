// #include <igloo/igloo.h>
// #include <cstdlib>
// #include <iostream>
// #include "utils.h"
// #include <vector>
// #include <string>
// #include <fstream>

// using namespace igloo;
// using namespace std;

// std::string exec(std::string command) {
//     char buffer[128];
//     std::string result = "";

//     // Open pipe to file
//     FILE* pipe = popen((command + " 2>&1").c_str(), "r");
//     if (!pipe) {
//         return "popen failed!";
//         }

//     // read till end of process:
// while (!feof(pipe)) {

//     // use buffer to read and add to result
//     if (fgets(buffer, 128, pipe) != NULL)
//         result += buffer;
//         }

//     pclose(pipe);
//     result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
//     return result;
// }

// Context(ExerciseTwoTests){
//     static void SetUpContext(){
//     exec("g++ main.cpp -o temp");
//     }
//     static void TearDownContext() {
//     system("rm -rf temp");
//     }

//     Spec(test_1){
//     std::string result = exec("echo STATE| ./temp");
//     std::string expected = "";
//     expected += green('S') + ' ';
//     expected += gray('T') + ' ';
//     expected += green('A') + ' ';
//     expected += green('T') + ' ';
//     expected += green('E');
//     Assert::That(result, Equals(expected));
//     }

//     Spec(test_2){
//     std::string result = exec("echo TEAMS| ./temp");
//     std::string expected = "";
//     expected += yellow('T') + ' ';
//     expected += yellow('E') + ' ';
//     expected += green('A') + ' ';
//     expected += gray('M') + ' ';
//     expected += yellow('S');
//     Assert::That(result, Equals(expected));
//     }
// };

// string getSolution(const string& filename) {
//     // ifstream file(filename);
//     ifstream file(filename);
//     vector<string> words;
//     string word;
//     string result;

//     while (getline(file, word)) 
//     {
//         words.push_back(word);
//     }
//     srand(time(NULL));
//         int randIndex = rand() % words.size();
//         result = words[randIndex];
//         return result;
//     return word;
// }

// int main(int argc, const char* argv[]){
//     string word = getSolution("words.txt");
//     cout << word << endl;
//     // TestRunner::RunAllTests(argc, argv);
// }

#include <igloo/igloo.h>
#include <cstdlib>
#include <iostream>
#include "utils.h"
using namespace igloo;

std::string exec(std::string command) {
   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen((command + " 2>&1").c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
   return result;
}

Context(ExerciseTwoTests){
    static void SetUpContext(){
        exec("g++ main.cpp -o temp");
    }
    static void TearDownContext() {
        system("rm -rf temp");
    }

    Spec(test_1){
        std::string result = exec("echo STATE| ./temp");
        std::string expected = "";
        expected += green('S') + ' ';
        expected += gray('T') + ' ';
        expected += green('A') + ' ';
        expected += green('T') + ' ';
        expected += green('E');
        Assert::That(result, Equals(expected));
    }
    Spec(test_2){
        std::string result = exec("echo TEAMS| ./temp");
        std::string expected = "";
        expected += yellow('T') + ' ';
        expected += yellow('E') + ' ';
        expected += green('A') + ' ';
        expected += gray('M') + ' ';
        expected += yellow('S');
        Assert::That(result, Equals(expected));
        }

};

int main(int argc, const char* argv[]){
    TestRunner::RunAllTests(argc, argv);
}
