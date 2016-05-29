#include "StringSearch.h"

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

string searchName(string name, vector<string> names){
	vector<string> tmp = names;

	cout << "NOME A PROCURAR: " << name << endl;

	for (size_t i = 0; i < name.length(); i++)
		name[i] = toupper(name[i]);

	int max = INT_MIN;
	int index;

	for(unsigned int i = 0; i < tmp.size(); i++){
		int res;

		for (size_t j = 0; j < tmp[i].length(); j++)
			tmp[i][j] = toupper(tmp[i][j]);

		//if (tmp[i].size() < name_road.size())
		res = kmp(tmp[i], name);
		//else res = kmp(name_road, tmp[i]);

		if (max < res){
			max = res;
			index = i;
		}
	}

	if (max == 0){
		int min = INT_MAX;

		for(unsigned int i = 0; i < tmp.size(); i++){
			int res = edit_distance(tmp[i], name);

			if (res < min){
				min = res;
				index = i;
			}
		}
	}
	cout << "NOME ENCONTRADO: " << names[index] << endl;

	return names[index];
}

