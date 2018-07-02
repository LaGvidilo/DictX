/*
 *  terminaltable.cpp
 *  DictX
 *
 *  Created by Cyril Coelho on 26/06/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */
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

#include "terminaltable.h"
using namespace std;
void aff_table(map <int, string> data){
	map <int, string>::iterator it;
	cout << "|\tID\t|\t" <<  "|\tVALUE\t|"<< endl;
	for (it=data.begin(); it!=data.end(); ++it){
		cout << "|\t" << it->first << "\t|\t|\t" << it->second <<"\t|"<< endl;
	}
}

