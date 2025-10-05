#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> out;
  std::string current;

  rawWords.push_back(' ');

  for(size_t i =0; i < rawWords.size() ; i++){
    char c = rawWords[i];
    
    if(c >= 'A' && c <= 'Z'){
      c = char(c - 'A' + 'a');
    }

    bool isLetter = (c >= 'a' && c <= 'z');
    bool isDigit = (c >= '0' && c <= '9');

    if(isLetter || isDigit ){
      current.push_back(c);
    }
    else{
      if(current.size() >=2){
        out.insert(current);
      }
      current.clear();
    }
   
  }
  if(current.size() >=2){
        out.insert(current);
      }
 return out;






}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
