#include "reseau.h"

using std::string;
using std::copy;

char* reseau::stringToChar(string envoi) {
	int length = envoi.size();
	char *texte = new char[length + 1];
	copy(envoi.begin(), envoi.end(), texte);
	texte[length] = '\0';
	return texte;
}

string reseau::charToString(char* envoi) {
	string recep = envoi;
	return recep;
}