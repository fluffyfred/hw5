#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void wordle_helper(std::string in, std::string& floating, unsigned int cindex, std::set<std::string>& words, const std::set<std::string>& dictionary);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> output;
    std::string in_copy = in;
    std::string floating_copy = floating;
    wordle_helper(in_copy, floating_copy, 0, output, dict);
    return output;
}

// Define any helper functions here
void wordle_helper(std::string in, std::string& floating, unsigned int cindex, std::set<std::string>& words, const std::set<std::string>& dictionary)
{
  if(cindex == in.size()) {
    if(floating.size() == 0 && dictionary.find(in) != dictionary.end()) {
      words.insert(in);
      return;
    }
  }//--------------------------------------------------
  else if(in[cindex] == '-') {
    int count = 0;
    //----------
    for(unsigned int i = cindex + 1; i < in.size(); i++) {
      if(in[i] != '-') {count++;}
    }
    //----------
    unsigned int left = in.size() - cindex;
    std::set<char> used;
    //----------
    for(unsigned int i = 0; i < floating.size(); i++) {
      if(used.find(floating[i]) != used.end()) {continue;}
      in[cindex] = floating[i];
      std::string temp = floating;
      temp.erase(i, 1);
      wordle_helper(in, temp, cindex + 1, words, dictionary);
      used.insert(floating[i]);
      in[cindex] = '-';
    }
    //----------
    if(left > floating.size() + count) {
      for(char letter = 'a'; letter <= 'z'; letter++) {
        if(used.find(letter) != used.end()) {continue;}
        in[cindex] = letter;
        wordle_helper(in, floating, cindex + 1, words, dictionary);
        in[cindex] = '-';
      }
    }
  }//---------------------------------------------
  else {
    wordle_helper(in, floating, cindex + 1, words, dictionary);
  }
}


// !