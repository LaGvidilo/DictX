#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <list>
#include "dictx.h"
#include <fstream>
#define _POSIX_SOURCE
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <sstream>

#include "md5.h"
#include "base64.h"
using namespace std;



//LeftSelect
void LRstr(char input_dict[],int distanceL,char x_in[100000],int distanceR,char y_out[100000])
{
	long LEN_IN = strlen(input_dict);
	long Z = 0;
	long i = 0;
	for (i = 0 ; i < distanceL % LEN_IN ; i++)
	{
		char caractere = input_dict[i];
		x_in[Z] = caractere;
		Z++;
	} 
	
	int Zp = 0;
	char z_out[1024];
	for (i = Z ; i > Z-distanceR ; i--)
	{
		char caractere = x_in[i-1];
		//printf("CARACTERE: %c\n",caractere);
		z_out[Zp] = caractere;
		Zp++;	
	}
	
	for (i=0; i<Z-2; i++)
	{
		if (z_out!=0)
		{
			//printf("z=%c\n",z_out[i]);
			y_out[i] = z_out[(Z-2) - 1 - i];
		}
	}
	
}

/* LRstr usage 

	//char x_in[1024];
	//char y_out[1024];
	//LRstr(input_dict,6,x_in,4,y_out);
	//printf("LEFT: %s\n",x_in);
	//printf("RL: %s\n",y_out);
*/

void decoupe(char input_dict[], char input_dict2[],int lentmp)
{
	memcpy(input_dict, input_dict2+lentmp, strlen(input_dict2)-lentmp);
	input_dict[strlen(input_dict2)-lentmp] = 0;
}

int counting(string delim)
{
	int compteur=0;
	char nextChar;
	for (int i=0; i<int(delim.length()); i++)
	{
		nextChar = delim.at(i); // Recuperer car par car
		if (delim[i]==44){
			compteur++;
		}
	}
	return compteur;
}

void affiche_tab(map<int, string> outtab){
	map <int, string>::iterator it;
	for (it=outtab.begin(); it!=outtab.end(); ++it){
		cout << "---ID:" << it->first << " ; VALUE:" << it->second << endl;
	}

}

const unsigned long hash(const char *str){
	unsigned long hash = 5381;
	int c;
	
	while ((c=*str++))
		hash = ((hash<<5)+hash)+c;
	return hash;
}

class Table
{
	public:
 	string name;
	map <int, map<string, string> > mapData;
	map <string, string> mapRel;
	
	void create_relation(string name, string rel){
		mapRel[name] = rel;
	}
	
	void delete_relation(string name){
		mapRel.erase(name);
	}
	
	int ID;
	void insert(int id_cur, string cle, string value){
		cout << "INSERT: ID(" << id_cur << ") KEY(" << cle << ") VALUE(" << value << ")" <<endl;
		mapData[id_cur][cle] = value;
		ID = id_cur;
	}	
	
	//void create(string table_name){
	//	cout << "CREATE TABLE: "<< table_name <<endl;
	//	mapData[mapData.end()->first+1].name = table_name;
	//	ID = 0;
	//}
	
	void delete_from_id(int id){
		cout << "ERASE FROM ID: " << id << endl;
		mapData.erase(id);
	}
		
	int get_current_id(){
		return mapData.end()->first+1;
	}
	
	int get_last_id(){
		return mapData.end()->first;
	}
	
	map <int, string> search(string cle){
		map <int, string> tableau;
		map <int, map<string, string> >::iterator it;
		for (it=mapData.begin(); it!=mapData.end(); ++it){
			map<string, string> mapit2 = it->second;
			for (map<string, string>::const_iterator it2 = mapit2.begin();  it2 != mapit2.end(); ++it2){
				 if ((*it2).first==cle){
					tableau.insert(pair<int,string> (it->first, (*it2).second));
				 }
			}
		} 
		return tableau;
	}
	
	void update(int ID, string cle, string value){
		map <int, map<string, string> >::iterator it;
		for (it=mapData.begin(); it!=mapData.end(); ++it){
			map<string, string> mapit2 = it->second;
			for (map<string, string>::const_iterator it2 = mapit2.begin();  it2 != mapit2.end(); ++it2){
				 if ((*it2).first==cle){
					mapData[ID][cle] = value; 
				 }
			}
		} 
	}


	void set_name(string nom){
		name=nom;
		ID=0;		
	}
	
	string get_name(){
		return name;
	}
	

};



Table TABLE[512];

void DictX::delete_rel(string origin_table, string name){
	int j=0;
	while (j<512)
	{
		if (TABLE[j].name==origin_table){
			TABLE[j].delete_relation(name);
			cout << "DELETE RELATION(" << name << ")" << endl;
			break;
		}
		j++;
	}
}

void DictX::create_rel(string origin_table, string name, string rel){
	int j=0;
	while (j<512)
	{
		if (TABLE[j].name==origin_table){
			TABLE[j].create_relation(name, rel);
			cout << "CREATE RELATION(" << name << "): " << rel << endl;
			break;
		}
		j++;
	}
}

void DictX::create_table(const string table_name){
	int j=0;
	map <int, string> outtab;
	while (j<512)
	{
		bool NOMORE = true;
		for (int i=0; i<512; i++){
			if (TABLE[i].name == table_name){NOMORE=false;} 
		}
		if (TABLE[j].name=="" && NOMORE){
			cout << "\nCREATE TABLE: "<< table_name <<endl;
			TABLE[j].name = table_name;
			break;
		}
		j++;
	}
}


void DictX::update(const int ID, const string table_name, string key,string value){
	int j=0;
	map <int, string> outtab;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			//UPDATE CODE
			cout << "UPDATE FOR ID(" << ID << ") KEY(" << key << ") VALUE(" << value <<")" << endl;
			TABLE[j].update(ID, key, value);
		}
		j++;
	}
}

map <int, string> DictX::search(const string table_name, string key){
	int j=0;
	map <int, string> outtab;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			outtab = TABLE[j].search(key);
			break;
		}
		j++;
	}
	return outtab;
}

void DictX::aff_search(const string table_name, string key){
	int j=0;
	map <int, string> outtab;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			outtab = TABLE[j].search(key);
			affiche_tab(outtab);
			break;
		}
		j++;
	}
}
				
void DictX::delete_id(const string table_name, int ID){
	int j=0;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			TABLE[j].delete_from_id(ID);
		}
		j++;
	}
}

void DictX::drop_table(const string table_name){
	int j=0;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			map <int, map<string, string> > mapData;
			TABLE[j].mapData = mapData;
			TABLE[j].name = "";
		}
		j++;
	}
}

int findocc(map <int, map<string, string> > mapdata, string key)
{
	map <int, map<string, string> >::iterator it2;
	for (it2=mapdata.begin(); it2!=mapdata.end(); ++it2){
		map <string,string>::iterator it3;
		for (it3=it2->second.begin(); it3!=it2->second.end(); ++it3){
			if (it3->first == key){
				return it2->first;
			}
		}
	}
	return -1;
}

string finddta(map <int, map<string, string> > mapdata, string key, int number)
{
	int numj=0;
	map <int, map<string, string> >::iterator it2;
	for (it2=mapdata.begin(); it2!=mapdata.end(); ++it2){
		map <string,string>::iterator it3;
		for (it3=it2->second.begin(); it3!=it2->second.end(); ++it3){
			if (it3->first == key){
				if (numj>=number){
					return it3->second;
				}
				numj++;
			}
		}
	}
	return "";
}

void apply_rules(){
	int j=0;
	
	while(j<512){
		map<string,string> tmp=TABLE[j].mapRel;
		
		for (map<string,string>::iterator it = TABLE[j].mapRel.begin(); it!=TABLE[j].mapRel.end(); ++it){ 
			string namerel = it->first;
			string tableorigin = it->second.substr(0,it->second.find("$"));
			it->second = it->second.substr(it->second.find("$")+1);
			string keyorigin = it->second.substr(0,it->second.find("$"));
			it->second = it->second.substr(it->second.find("$")+1);
			string tabletarget = it->second.substr(0,it->second.find("$"));
			it->second = it->second.substr(it->second.find("$")+1);
			string keytarget = it->second.substr(0,it->second.find("$"));
			it->second = it->second.substr(it->second.find("$")+1);
			//finddta(TABLE[j].mapData, keyorigin, ynum);

			
			int h=0;
			while (h<512){
				int occtargetA = findocc(TABLE[h].mapData, keytarget);
				int occtargetB = TABLE[h].get_current_id();
				int ynum=0;
				if (TABLE[h].name==tabletarget){
					for (int occtarget=occtargetA; occtarget<occtargetB-1; ++occtarget){
						string dataorigin = TABLE[j].mapData[ynum][keyorigin];
						ynum++;
						TABLE[h].update(occtarget, keytarget, dataorigin);
						cout << "RULE: NAME("<<tabletarget<<") ID(" << occtarget << ") KEY("<<keytarget<<") DATA("<<dataorigin<<")"<<endl;
					}
				}
				h++;
			}
			TABLE[j].mapRel = tmp;
			
		}
		j++;		
	}
}

void DictX::insert_from(string table_name, string key, string value){
	int j=0;
	//map <int, string> outtab;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			TABLE[j].insert(TABLE[j].get_current_id(),key,value);
			break;
		}
		j++;
	}
	apply_rules();
	
}

void DictX::insert_from_new(string table_name, string key, string value){
	int j=0;
	map <int, string> outtab;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			TABLE[j].insert(TABLE[j].get_current_id()+1,key,value);
			break;
		}
		j++;
	}
	apply_rules();
}

void DictX::insert_from_by_id(string table_name, string key, string value, int id_code){
	int j=0;
	map <int, string> outtab;
	while (j<512)
	{
		if (TABLE[j].name==table_name){
			TABLE[j].insert(id_code,key,value);
			break;
		}
		j++;
	}
	apply_rules();
}



void DictX::load_database(string namefile){
	char input_dict[100000];
	char input_dict2[100000];
	string line;
	string RELATIONS;
	char nom_fichier[512];
	if (getcwd(nom_fichier, sizeof(nom_fichier)) == NULL){
		cout << "ERROR FILE PATH" << endl;
	}
	else{
		strcat(nom_fichier,"/");
		strcat(nom_fichier,namefile.c_str());
		printf("FICHIER SE TROUVE: %s\n",nom_fichier);
		ifstream fichier(nom_fichier);
		char noinp[] ="$END$\0";
		if (fichier.is_open()){
			while (getline(fichier,line)){
				size_t foundrel = line.find("#RELD#");
				if (foundrel!=string::npos){
					cout << "RELD IS HERE: " << line.substr(line.find("#RELD#")+6,line.find("#ENDREL#")-6) << endl;
					RELATIONS = line.substr(line.find("#RELD#")+6,line.find("#ENDREL#")-6);
				}
				else
				{
					strcat(input_dict,line.c_str());	
				}
			}
			strcpy(input_dict2,input_dict);
			fichier.close();
		}
		else{
			strcpy(input_dict,noinp);
			strcpy(input_dict2,noinp);
			cout << "Unable to open file\n";
		}		
	}
	int lentmp=0;
	//int h=0;
	int j=0;
	int i=0;
	string delim;
	string key;
	string value;
	int n;
	cout << "LOAD THE DB..." << endl;
	map <int, string> outtab;
	while (j<512)
	{
		lentmp += strlen(strtok(input_dict,"$"))+2;
		if (strlen(input_dict)==4){break;}
		//printf("DELIM: %s\n", strtok(input_dict,"$"));
		TABLE[j].set_name(strtok(input_dict,"$"));
		//cout << "\nNAME OF TABLE CREATED: " << TABLE[j].name << endl;
		decoupe(input_dict,input_dict2,lentmp);
		//printf("AFTER DECOUPE: %s\n\n", input_dict);
	
		lentmp += strlen(strtok(input_dict,"$"));
		//printf("--DELIM: %s\n", strtok(input_dict,"$"));
	
		delim = input_dict;
		n = counting(delim);
		int id_code;
		for (i=0; i<n+1; i++){
			
			key = delim.substr(0,delim.find(":"));
			sscanf(key.substr(key.find("%")+1).c_str(),"%d",&id_code);
			key = delim.substr(0,key.find("%"));
			value = delim.substr(delim.find(":")+1);
			value = value.substr(0,value.find(","));
		
			if (key!="") {
			
				TABLE[j].insert(id_code,key,value);
				//cout << "---+KEY: " << key << endl;
				//cout << "---+VALUE: " << value << endl;
				
			}
			
			delim = delim.substr(delim.find(",")+1);
		}
	
		decoupe(input_dict,input_dict2,lentmp);
		//printf("--AFTER DECOUPE: %s\n\n", input_dict);
		j++;
	}
	while (RELATIONS.find(";")<RELATIONS.length()){
		size_t foundrel = RELATIONS.find(":");
		if (foundrel!=string::npos){
			string namerel = RELATIONS.substr(0,RELATIONS.find(":"));
			string datarel = RELATIONS.substr(RELATIONS.find(":")+1,RELATIONS.find(";")-2);
			if (datarel.find(";")!=string::npos){
				datarel = datarel.substr(0,datarel.find(";"));
			}
			cout << "namerel: " << namerel << endl << "datarel: " << datarel << endl;
			RELATIONS = RELATIONS.substr(RELATIONS.find(";")+1);
			
			string origin_table = datarel.substr(0,datarel.find("$"));
			
			int j=0;
			while (j<512)
			{
				if (TABLE[j].name==origin_table){
					TABLE[j].create_relation(namerel, datarel);
					cout << "CREATE RELATION(" << namerel << "): " << datarel << endl;
					break;
				}
				j++;
			}			
			
		}
	}
		
	apply_rules();
	cout << "--DATABASE LOADED--" << endl;	
}

void DictX::save_database(const string nom_fichier){
	ofstream fichier;
	fichier.open(nom_fichier.c_str());
	int j=0;
	string ss1;
	while (j<512)
	{
		if (TABLE[j].name!=""){
			fichier << "$" << TABLE[j].name << "$";
			map <int, map<string, string> >::iterator it;
			
			for (map<string,string>::iterator itrel=TABLE[j].mapRel.begin(); itrel!=TABLE[j].mapRel.end(); ++itrel){
				ss1 = ss1 + (*itrel).first + ":" + (*itrel).second + ";";
				cout << "REL:: " << (*itrel).first << ":" << (*itrel).second << endl;
			} 
			
			int key = 0;
			for (it = TABLE[j].mapData.begin(); it != TABLE[j].mapData.end(); ++it){
				map<string, string> mapit2 = it->second;
				for (map<string, string>::const_iterator it2 = mapit2.begin();  it2 != mapit2.end(); ++it2){
					fichier << (*it2).first << "%" << key << ":" << (*it2).second << ",";
				}
				key++;
			}
		}
		j++;
	}
	fichier << "$END$";
	fichier << "\n#RELD#";
	fichier << ss1;
	fichier << "#ENDREL#";
	fichier.close();
}
