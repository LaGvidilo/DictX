/*
DictX 1.0
Invented By Rick Sanchez
In 2018
On a iMac G3 500Mhz with 256Mb of RAM
*/

/*
Release notes:
Version		Comment
  1.0		  First version
  1.1		  Load/Write a file (dictx)

*/
#ifndef DICTX_H
#define DICTX_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <sqlite3.h>
#include <map>
#include <list>
#include <fstream>
using namespace std;
void LRstr(char input_dict[],int distanceL,char x_in[1024],int distanceR,char y_out[1024]);
void decoupe(char input_dict[], char input_dict2[],int lentmp);
int counting(string delim);
void affiche_tab(map<int, string> outtab);
class DictX{
	public:
	map <int, string> search(const string table_name, string key);
	void aff_search(const string table_name, string key);
	void load_database(string namefile);
	void delete_id(const string table_name, int ID);
	void insert_from(string table_name, string key, string value);
	void insert_from_by_id(string table_name, string key, string value, int id_code);
	void insert_from_new(string table_name, string key, string value);
};
#endif