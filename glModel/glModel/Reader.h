#ifndef _READER_H_
#define _READER_H_
#pragma once
#include "TYPEDEF.h"
#include <iostream>
#include <fstream>
using namespace std;


class Reader
{
public:
	virtual void CheckFile(char* filename) = 0;
	virtual void ReadHead(MODELHEAD* head) = 0; //Ū�����Y
	virtual void ReadData(MODELDATA* data) = 0; //Ū�����

	bool isfileInvalid;
protected:
	
	ifstream *fileStream;

};


#endif
