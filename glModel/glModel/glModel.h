#ifndef _GLMODEL_H_
#define _GLMODEL_H_
#pragma once
//for debug 
#define _DEBUG_DUMP_DETAIL 0
#define _DEBUG_DUMP_VERTICES 0;
#define _DEBUG_DUMP_MESH 0;

#if _DEBUG_DUMP_DETAIL==1
#define _DEBUG_DUMP_VERTICES 1;
#define _DEBUG_DUMP_MESH 1;
#endif





#include "TYPEDEF.h"
#include "Reader.h"
#include "ReaderFactory.h"

#include <GL/glut.h>
class glModel
{
public:
	MODELHEAD *modelHead;
	MODELDATA *modelData;
	glModel(void);
	~glModel(void);


	bool setReader(char* type);
	void LoadModel(char* filename);
	void glRenderingModel();
	void dumpInfo();

private:
	Reader *m_pReader;
	ReaderFactory *m_pReaderFactory;
	bool mallocMemory(void);	// ∞t∏m∞Oæ–≈È


};

#endif