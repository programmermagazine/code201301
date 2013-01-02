#include "glModel.h"
//#include <windows.h>


glModel::glModel(void)
{
	m_pReaderFactory = new ReaderFactory();
//	m_pReader=m_pReaderFactory->GetReaderPtr("obj");
	//m_pReader=nullptr;
    m_pReader = NULL;
	modelHead=new MODELHEAD();
	modelData=new MODELDATA();

}


glModel::~glModel(void)
{
}



void glModel::LoadModel(char* filename)
{
	//if(m_pReader==nullptr){		
	if(m_pReader==NULL){		
		cout<<"[Warning]: YOU MUST SET READER TYPE FIRST !!!"<<endl;	
	}else{
		m_pReader->CheckFile(filename);		
		if(m_pReader->isfileInvalid){
			cout<<"[Warning]:Invalid File !"<<endl;	
		}{
			//sniffer here !! 
			//copy data into HEADER
			m_pReader->ReadHead(this->modelHead);
			m_pReader->ReadData(this->modelData);
		}
	}

}

bool glModel::setReader(char* type)
{
	m_pReader=m_pReaderFactory->GetReaderPtr(type);
	return true;
}
void glModel::dumpInfo(void)
{
	cout<<"=========================================="<<endl;
	cout<<"Num of V:"<<this->modelHead->numVertices<<endl;
	cout<<"num of M:"<<this->modelHead->numMeshes<<endl;
	cout<<"=========================================="<<endl;	


#ifdef _DEBUG_DUMP_VERTICES

	for(int i=0;i<this->modelHead->numVertices;i++){
		cout<<"v["<<i<<"]=\t"<<this->modelData->ModelVertices[i].x<<"\t"
			<<this->modelData->ModelVertices[i].y<<"\t"
			<<this->modelData->ModelVertices[i].z<<"\n";

	}
#endif
#ifdef _DEBUG_DUMP_MESH

	for(int i=0;i<this->modelHead->numMeshes;i++){
		cout<<"F["<<i<<"]:"<<this->modelData->ModelMesh[i].numVerticesEachMesh<<" | ";
		for(int j=0;j<this->modelData->ModelMesh[i].numVerticesEachMesh;j++){
			cout<<"\t"<<this->modelData->ModelMesh[i].VerticesIndex[j];
		}
		cout<<"\n";

	}
#endif


}


void glModel::glRenderingModel(void){
	GLubyte testcolor[4];
	testcolor[0]=255;
	testcolor[1]=255;
	testcolor[2]=0;
	testcolor[3]=10;

	//glColor3ub(0,127,127);
	glColor4ubv(testcolor);
	for(int i=0;i<this->modelHead->numMeshes;i++){
		glBegin(GL_LINE_STRIP);
		for(int j=0;j<this->modelData->ModelMesh[i].numVerticesEachMesh;j++){	

			glVertex3d(this->modelData->ModelVertices[(this->modelData->ModelMesh[i].VerticesIndex[j])].x,
				this->modelData->ModelVertices[(this->modelData->ModelMesh[i].VerticesIndex[j])].y,
				this->modelData->ModelVertices[(this->modelData->ModelMesh[i].VerticesIndex[j])].z );
		}//end for			
		glEnd();
	}

}


