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
	DX.aff_search("test","code");
			
    return 0;
}
