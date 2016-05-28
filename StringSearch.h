#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

vector<string> getWords(string s);

void pre_kmp(string pattern, vector<int> & prefix);
int kmp(string text, string pattern);

//APROX
//int editDistance(string pattern, string text);
unsigned int edit_distance(const string& word, const string& toSearch);

float numApproximateStringMatching(string filename, string toSearch);

//EXACT SEARCH
//int* prefix_function(string& P);

 /*
  * Retorna o numero de matches na string T
  */
//int KMP_matcher(string& T, string& P);
