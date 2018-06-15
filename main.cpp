#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <sqlite3.h>
#include <map>
#include <list>
#include "dictx.h"

using namespace std;


int main (int argc, const char * argv[]) {	
	
	cout << "*===================*" << endl;
	cout << "|   DictX Terminal  |" << endl;
	cout << "|       v1.2.0      |" << endl;
	cout << "|  By Rick Sanchez  |" << endl;
	cout << "|       D-634       |" << endl;
	cout << "*===================*" << endl;
	
	DictX DX;
	string nomf;
	if (argc==1){
		cout << "\nNom du fichier DictX:";
		cin >> nomf;
	}
	else {
		nomf=argv[1];
	}
	DX.load_database(nomf);
	
	string commande="";	
	while (commande!="exit"){
		cout << "\nDictX(" << nomf << ")>";
		cin >> commande;
	
		if (commande == "search"){
			string table_name;
			string key_name;
			cout << "\nTABLE NAME:";
			cin >> table_name;
			cout << "\nKEY NAME:";
			cin >> key_name;
			DX.aff_search(table_name,key_name);
		}
		if (commande == "exit"){
			break;
		}
		if (commande == "commit"){
			DX.save_database(nomf);
			DX.load_database(nomf);
		}
		if (commande == "insert"){
				string table_name;
				string key_name;
				string value;
				cout << "\nTABLE NAME:";
				cin >> table_name;
				string recur="START";
				while (recur!="no" || recur=="yes"){
					cout << "\nKEY NAME:";
					cin >> key_name;
					cout << "\nVALUE:";
					cin >> value;
					if (recur=="START"){
						DX.insert_from_new(table_name,key_name,value);
					}
					else {
						DX.insert_from(table_name,key_name,value);
					}
					cout << "\nCONTINUE?(yes/no):";
					cin >> recur;
				}
		}
	}
			
    return 0;
}
