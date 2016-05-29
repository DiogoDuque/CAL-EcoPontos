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

/**
 * Prepara o vector prefix para ser usado no algoritmo de Knuth–Morris–Pratt
 *
 *@param prefix - vector onde se guarda a "Failure Function"
 *@param pattern - string que vai ser procurada
 */
void pre_kmp(string pattern, vector<int> & prefix);


/**
 * Retorna o numero de vezes que pattern se repete em text
 *
 * Aplica o algoritmo de Knuth–Morris–Pratt e conta o numero de vezes que pattern se repete em text.
 *
 *@param text - string onde vai ser procurado pattern
 *@param pattern - string que vai ser procurada em text
 *
 *@return - o numero de vezes que pattern se repete em text
 */
int kmp(string text, string pattern);

//APROX

/*
 * Conta o número de alterações necessárias para transformar word em toSearch.
 *
 * @param word - string que se vai tentar transformar em word
 * @param toSearch - string que vai ser comparada a word
 *
 *@return - o número de alterações necessárias para transformar word em toSearch.
 */
unsigned int edit_distance(const string& word, const string& toSearch);



/**
 * Search a string on vector of strings
 *
 *@param name - name to be sought
 *@param names - vector of names that cointais the desired name
 *@param most similar string to name
 */
string searchName(string name, vector<string> names);


