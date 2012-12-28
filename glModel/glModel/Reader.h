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
	virtual void ReadHead(MODELHEAD* head) = 0; //讀取標頭
	virtual void ReadData(MODELDATA* data) = 0; //讀取資料

	bool isfileInvalid;
protected:
	
	ifstream *fileStream;

};


#endif
