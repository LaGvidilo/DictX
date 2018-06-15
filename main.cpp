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
	/*long exp;
	exp = 0;
	printf("EXP:");
	scanf("%ld",&exp);
	exp++;
	printf("%ld",exp);*/
	DictX DX;
	DX.load_database("database.dictx");
	DX.insert_from_new("test", "name", "Klauss");
	DX.insert_from("test", "code", "5588");
	DX.insert_from_new("test", "name", "Kevin");
	DX.insert_from("test", "code", "774589");
	DX.insert_from_new("test", "name", "Germain");
	DX.insert_from("test", "code", "412304");
	DX.aff_search("test","name");
	DX.aff_search("test","code");
	DX.aff_search("test","name");
	DX.save_database("database.dictx");

			
    return 0;
}
