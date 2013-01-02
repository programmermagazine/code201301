#include <cstdlib>
#include <iostream>



#include "glModel.h"


using namespace std;



int main (){



	glModel test;
	test.setReader("obj");
	test.LoadModel("cube.obj");



	test.dumpInfo();


	//system("PAUSE");
}
