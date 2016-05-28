#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits.h>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

//EXACT SEARCH
void pre_kmp(string pattern, vector<int> & prefix);
/*
 * Retorna o numero de matches na string T
 */
int kmp(string text, string pattern);

//APROX
unsigned int edit_distance(const string& word, const string& toSearch);
float numApproximateStringMatching(string filename, string toSearch);

/**
 * Search a string on vector of strings
 *
 *@param name - name to be sought
 *@param names - vector of names that cointais the desired name
 *@param most similar string to name
 */
string searchName(string name, vector<string> names);


//int editDistance(string pattern, string text);

//int* prefix_function(string& P);

//vector<string> getWords(string s);

//int KMP_matcher(string& T, string& P);
