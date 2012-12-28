#ifndef _READER_FACTORY_H_
#define _READER_FACTORY_H_
#pragma once
#include "Reader.h"
//include all reader here !!!!!
#include "objReader.h"
#include <string>

class ReaderFactory
{
public:	
	Reader* GetReaderPtr(string type){
		if ( type == "obj" ) return new objReader();
		//if ( type == "ply" ) return new plyReader();
		return NULL;
	}	
};


#endif


