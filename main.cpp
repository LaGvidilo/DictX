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
	cout << "|       v1.4.0      |" << endl;
	cout << "|  By Rick Sanchez  |" << endl;
	cout << "|       D-634       |" << endl;
	cout << "*===================*" << endl;
	
	DictX DX;
	string nomf;
	if (argc==1){
		cout << "NOTE: usage is.: dictx <name_of_file>" << endl;
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
			//DX.load_database(nomf);
		}
		if (commande == "drop"){
			string table_name;
			cout << "\nTABLE NAME:";
			cin >> table_name;
			DX.drop_table(table_name);
		}
		if (commande == "delete"){
			string table_name;
			cout << "\nTABLE NAME:";
			cin >> table_name;
			int id_code;
			cout << "\nID:";
			cin >> id_code;
			DX.delete_id(table_name, id_code);
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
		if (commande == "update"){
			string table_name;
			string key_name;
			int ID;
			string value;
			cout << "\nTABLE NAME:";
			cin >> table_name;
			cout << "\nID:";
			cin >> ID;
			cout << "\nKEY NAME:";
			cin >> key_name;
			cout << "\nVALUE:";
			cin >> value;
			DX.update(ID, table_name, key_name, value);
		}
	}
			
    return 0;
}
