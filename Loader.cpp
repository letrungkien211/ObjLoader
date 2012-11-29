/*
 * Loader.cpp
 *
 *  Created on: Aug 13, 2012
 *      Author: letrungkien7
 */

#include "Loader.h"
#include<iostream>
#include<cstdio>

using namespace std;

void Loader::Load(char* filename){
	char line[100];
	char mark[5];
	float x,y,z;
	char *pch;
	vector<int> faceIndex;
	int index;

	FILE* fp = fopen(filename, "r");
	V.push_back(Point(0,0,0));

	if(!fp){
		cout<< "Couldn't open the file!"<<endl;
		exit(1);
	}

	while(fgets(line, 100, fp)){
		switch(line[0]){
		case 'v':
			sscanf(line, "%s %f %f %f", mark, &x, &y, &z);
			V.push_back(Point(x,y,z));
			break;
		case 'f':
			pch = strtok (line," ");
			pch = strtok (NULL, " ");
			while (pch != NULL)
			{
				sscanf(pch, "%d", &index);
				faceIndex.push_back(index);
				pch = strtok (NULL, " ");
			}
			F.push_back(faceIndex);
			faceIndex.clear();
			break;
		default:
			break;
		}
	}
}

void Loader::Draw(){
	glColor3d(0,1,0);
	glBegin(GL_LINES);
	for(int i=0, num = F.size(); i<num; ++i){
		for(int j=0, n = F[i].size(); j<n; ++j){
			glVertex3dv(V[F[i][j]].data());
			glVertex3dv(V[F[i][(j+1)%n]].data());
		}
	}
	glEnd();
}
