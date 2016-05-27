#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//APROX
unsigned int edit_distance(const string& word, const string& toSearch);

float numApproximateStringMatching(string filename, string toSearch);

//EXACT SEARCH
int* prefix_function(string& P);

 /*
  * Retorna o numero de matches na string T
  */
int KMP_matcher(string& T, string& P);
