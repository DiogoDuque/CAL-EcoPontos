#include "StringSearch.h"

vector<string> getWords(string s){
	vector<string> tmp;
	istringstream iss(s);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tmp));

	return tmp;
}

/*int editDistance(string pattern, string text)
{
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}*/

//APROX
unsigned int edit_distance(const string& word, const string& toSearch)
{
	unsigned int p = word.length();
	unsigned int t = toSearch.length();

	vector<vector<unsigned int> > d(p + 1, vector<unsigned int>(t + 1));

	d[0][0] = 0;
	for (unsigned int i = 1; i <= p; i++) {
		d[i][0]=i;
	}

	for (unsigned int j = 1; j <= t; j++) {
		d[0][j]=j;
	}

	for (unsigned int i = 1; i <= p; i++) {
		for (unsigned int j = 1; j <= t; j++) {
			int cell;
			if (word[i-1] == toSearch[j-1]) {
				cell = d[i-1][j-1];
			}
			else {
				cell = 1 + min(d[i-1][j-1], min(d[i][j-1], d[i-1][j]));
			}

			d[i][j] = cell;
		}
	}
	return d[p][t];
}

float numApproximateStringMatching(string text, string toSearch){
	int sum = 0;
	int num = 0;
	float mean;

	int low = 0;
	while (text[low] == ' ')
		low++;

	for(unsigned int index = low; index < text.size(); index++){
		unsigned int lowerBound = index;
		unsigned int upperBound;
		bool last_word = false;			// for last word
		string word;
		int res;

		while((text[index] != ' ') && (text[index] != '\n'))
		{
			index++;
		}

		if(index >= text.size()){
			last_word = true;				// reached last word
		}

		upperBound = index;
		word = text.substr(lowerBound, upperBound-lowerBound);

		if (word != ""){
			res = edit_distance(word, toSearch);

			sum = sum + res;
			num++;

			if (last_word)
				break;
		}

	}

	mean = (float)sum/(float)num;
	return mean;
}


void pre_kmp(string pattern, vector<int> & prefix)
{
	int m=pattern.length();
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
}

int kmp(string text, string pattern)
{
	int num=0;
	int m=pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			num++;
			q=prefix[q];
		}
	}
	return num;
}

/*
// EXACT SEARCH
int* prefix_function(string& P) {
	int m = P.length();

	int *Pi = new int[m];
	if (!Pi)
		cout << "Error";

	int k = -1;
	Pi[0] = k;

	for (int i = 1; i < m; i++){
		while(k > -1 && P[k+1] != P[i])
			k = Pi[k];
		if (P[k+1] == P[i])
			k++;
		Pi[i]=k;
	}
	return Pi;
}

// Retorna o numero de matches na string T

/*int KMP_matcher(string& T, string& P) {
	int res = 0;

	int n = T.length();
	int m = P.length();

	int k = -1;

	int *Pi = prefix_function(P);
	if (!Pi){
		cout << "Error2";
		return -1;
	}

	for (int i = 0; i < n; i++){
		while(k > -1 && P.at(k+1) !=T[i])
			k = Pi[k];
		if (P.at(k+1) == T[i])
			k++;
		if(k == m-1){
			res++;
			k = Pi[k];
		}
	}
    delete [] Pi;
	return res;
}*/
