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
		//驗證檔案 是否 有效
		if(this->fileStream->fail()){
			this->isfileInvalid=true;
		}else{
			this->isfileInvalid=false;
		}
		//檢查是否要關閉檔案
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
			//將資料放置過去
			head->numVertices=numV;
			head->numMeshes=numM;
			//this->fileStream->close();//close !!!
		}//end for if
	}; //讀取標頭

	void ReadData(MODELDATA* data){
		if(!this->isfileInvalid){
			//配置第一階段記憶體
			data->ModelVertices= new _ModelVertices[numV];
			data->ModelMesh= new _ModelMesh[numM];
			//清空numV,numM 
			numV=0,numM=0;


			this->fileStream->clear();  //清除 狀態錯誤
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
					//準備分析Face 的寬度
					for(int i=0,j=0;i<strlen(LineBuffer);i++){		


						//分析一個Face 有幾個點~ 即幾段?
						if( LineBuffer[i] == ' '  && LineBuffer[i+1] != ' ' && LineBuffer[i+1] != '\0' ){
							j++;
							//更新最大的Face,用來判斷是否為三角網格
							if(MaxFaces<j){
								MaxFaces=j;					
							}
						}
						//已確認目前的資料,準備配置記憶體空間;						
						data->ModelMesh[faceCounter].numVerticesEachMesh=j;
						data->ModelMesh[faceCounter].VerticesIndex=new int [j];
					}					
					faceCounter++;
					break;			
				}//end for switch
#endif
			}//end for while 

			


			//第三次啟動!!!!
			faceCounter=0;	

			this->fileStream->clear();  //清除 狀態錯誤
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
								switch(j){ //藉由分析 第幾個字元來 確認 x y z 
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
					//準備分析Face 的寬度
					for(int i=0,j=0;i<strlen(LineBuffer);i++){	
						//分析一個Face 有幾個點~ 即幾段?
						if( LineBuffer[i] == ' '  && LineBuffer[i+1] != ' ' && LineBuffer[i+1] != '\0' ){
							data->ModelMesh[faceCounter].VerticesIndex[j]=(atof(LineBuffer+i+1)-1);  //-1用來矯正  obj index from 1
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
	}; //讀取資料

	void CheckAndCloseFileStream(void)
	{
		if(this->fileStream->is_open()){
			this->fileStream->close();
		}
	}
};



#endif
