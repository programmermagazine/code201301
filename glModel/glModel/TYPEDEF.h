#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
//#pragma once
//#include <Windows.h>
#include <GL/glut.h>


#pragma pack(push)  //push pack狀態
#pragma pack(1)//設置pack 寬度 Byte
struct _ModelVertices{
	double x;
	double y;
	double z;
};
struct _ModelMesh{
	int numVerticesEachMesh;
	int *VerticesIndex;
};

struct MODELHEAD{
	int  numVertices; //點的數量
	int  numMeshes;   //面的數量
	bool isTrangle;   //是否為三角網格
};
struct MODELDATA{
	_ModelVertices *ModelVertices;
	_ModelMesh     *ModelMesh;
};
#pragma pack(pop)  //pop pack狀態

//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

#endif
