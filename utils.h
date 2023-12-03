#ifndef UTILS_H
#define UTILS_H

#include <string>

#define GREEN_BG "\033[42;30m"
#define YELLOW_BG "\033[43;30m"
#define GRAY_BG "\033[47;30m"
#define RESET "\033[0m"

std::string green(char letter){
    std::string result = GREEN_BG;
    result += letter;
    result += RESET;

    return result;
}

std::string yellow(char letter){
    std::string result = YELLOW_BG;
    result += letter;
    result += RESET;

    return result;
}

std::string gray(char letter){
    std::string result = GRAY_BG;
    result += letter;
    result += RESET;

    return result;
}


int contains(std::string word, char letter){
    for (int i = 0; i < word.length(); i++){
        if (word[i] == letter){
            return i;
        }
    }
    return -1;
}

#endif