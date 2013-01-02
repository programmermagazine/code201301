#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
//#pragma once
//#include <Windows.h>
#include <GL/glut.h>


#pragma pack(push)  //push pack���A
#pragma pack(1)//�]�mpack �e�� Byte
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
	int  numVertices; //�I���ƶq
	int  numMeshes;   //�����ƶq
	bool isTrangle;   //�O�_���T������
};
struct MODELDATA{
	_ModelVertices *ModelVertices;
	_ModelMesh     *ModelMesh;
};
#pragma pack(pop)  //pop pack���A

//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

#endif
