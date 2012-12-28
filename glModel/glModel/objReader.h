#ifndef _OBJ_READER_H_
#define _OBJ_READER_H_

#pragma once
#include "reader.h"
#include <iostream>;
#include <cstdlib>;
using namespace std;

class objReader : public Reader
{
private:
	char LineBuffer[2048];
	int numV;
	int numM;
	int faceCounter;		
	int verticesCounter;	
	int MaxFaces;

public:	
	objReader(void){
		this->fileStream= new ifstream();
		 numV=0;
		 numM=0;
		 faceCounter=0;		
		 verticesCounter=0;	
		 MaxFaces=0;
	}


	void CheckFile(char* filename){
		cout<<"Trying to open File :"<<filename<<endl;
		this->fileStream->open(filename,ios::in);
		//�����ɮ� �O�_ ����
		if(this->fileStream->fail()){
			this->isfileInvalid=true;
		}else{
			this->isfileInvalid=false;
		}
		//�ˬd�O�_�n�����ɮ�
		//if(this->fileStream->is_open()){
		//	this->fileStream->close();
		//}
	}//end for CheckFile

	void ReadHead(MODELHEAD* head){
		if(!this->isfileInvalid){

			//this->fileStream->open(filename,ios::in);
			this->fileStream->seekg(0, std::ios_base::beg);
			while(this->fileStream->peek()!=EOF){
				this->fileStream->getline(LineBuffer,2048,'\n');
#if 1
				switch(LineBuffer[0]){
				case '#':
					break;
				case 'v':
					switch(LineBuffer[1]){
					case ' ':
						numV++;
						break;					
					}
					break;
				case 'f':
					numM++;
					break;			
				}//end for switch
#endif
			}//end for while 
			//�N��Ʃ�m�L�h
			head->numVertices=numV;
			head->numMeshes=numM;
			//this->fileStream->close();//close !!!
		}//end for if
	}; //Ū�����Y

	void ReadData(MODELDATA* data){
		if(!this->isfileInvalid){
			//�t�m�Ĥ@���q�O����
			data->ModelVertices= new _ModelVertices[numV];
			data->ModelMesh= new _ModelMesh[numM];
			//�M��numV,numM 
			numV=0,numM=0;


			this->fileStream->clear();  //�M�� ���A���~
			this->fileStream->seekg(0, std::ios_base::beg);
			while(this->fileStream->peek()!=EOF){
				this->fileStream->getline(LineBuffer,2048,'\n');
#if 1
				switch(LineBuffer[0]){
				case '#':
					break;
				case 'v':
					switch(LineBuffer[1]){
					case ' ':
						numV++;
						break;					
					}
					break;
				case 'f':
					//�ǳƤ��RFace ���e��
					for(int i=0,j=0;i<strlen(LineBuffer);i++){		


						//���R�@��Face ���X���I~ �Y�X�q?
						if( LineBuffer[i] == ' '  && LineBuffer[i+1] != ' ' && LineBuffer[i+1] != '\0' ){
							j++;
							//��s�̤j��Face,�ΨӧP�_�O�_���T������
							if(MaxFaces<j){
								MaxFaces=j;					
							}
						}
						//�w�T�{�ثe�����,�ǳưt�m�O����Ŷ�;						
						data->ModelMesh[faceCounter].numVerticesEachMesh=j;
						data->ModelMesh[faceCounter].VerticesIndex=new int [j];
					}					
					faceCounter++;
					break;			
				}//end for switch
#endif
			}//end for while 

			


			//�ĤT���Ұ�!!!!
			faceCounter=0;	

			this->fileStream->clear();  //�M�� ���A���~
			this->fileStream->seekg(0, std::ios_base::beg);
			while(this->fileStream->peek()!=EOF){		
				this->fileStream->getline(LineBuffer,2048,'\n');
#if 1
				switch(LineBuffer[0]){
				case '#':
					break;
				case 'v':		
					switch(LineBuffer[1]){
					case ' ':
#if 1
						for(int i=0,j=0;i<strlen(LineBuffer);i++){
							if( LineBuffer[i] == ' '  && LineBuffer[i+1] != ' ' && LineBuffer[i+1] != '\0' ){
								switch(j){ //�ǥѤ��R �ĴX�Ӧr���� �T�{ x y z 
								case 0:
									
									data->ModelVertices[verticesCounter].x=atof(LineBuffer+i+1);
									j++;
									break;
								case 1:
									data->ModelVertices[verticesCounter].y=atof(LineBuffer+i+1);
									j++;
									break;
								case 2:
									data->ModelVertices[verticesCounter].z=atof(LineBuffer+i+1);
									j++;
									break;;
								}//end for switch 
							}//end for if
						}//end for for

#endif
						verticesCounter++;
						break;
					case 'n':
						break;
					case 't':
						break;					
					}//end for switch , v test!
					break;
				case 'f':
					//�ǳƤ��RFace ���e��
					for(int i=0,j=0;i<strlen(LineBuffer);i++){	
						//���R�@��Face ���X���I~ �Y�X�q?
						if( LineBuffer[i] == ' '  && LineBuffer[i+1] != ' ' && LineBuffer[i+1] != '\0' ){
							data->ModelMesh[faceCounter].VerticesIndex[j]=(atof(LineBuffer+i+1)-1);  //-1�Ψ��B��  obj index from 1
							j++;					
						}				
					}
					faceCounter++;
					break;			
				}//end for switch
#endif
			}//end for while;



			this->fileStream->close();//close !!!
		}//end for if
	}; //Ū�����

	void CheckAndCloseFileStream(void)
	{
		if(this->fileStream->is_open()){
			this->fileStream->close();
		}
	}
};



#endif
